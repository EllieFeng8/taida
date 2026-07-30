// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QFile>
#include <QFileInfo>
#include <QMutex>
#include <QMutexLocker>
#include <QRegularExpression>
#include <QTextStream>

#include <QLocalServer>
#include <QLocalSocket>
#include "autogen/environment.h"
#include "Core/TdProxy.h"
#include "Core/core.h"
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "Dbghelp.lib")

namespace {

QFile logFile;
QDate logFileDate;
QMutex logFileMutex;

constexpr int logRetentionDays = 7;
const QString logFilePrefix = QStringLiteral("app_log_");
const QString logFileSuffix = QStringLiteral(".txt");

QString dailyLogFileName(const QDate &date)
{
    return logFilePrefix + date.toString(QStringLiteral("yyyy-MM-dd")) + logFileSuffix;
}

void removeExpiredLogFiles(const QDate &today)
{
    const QDate oldestDateToKeep = today.addDays(-(logRetentionDays - 1));
    const QRegularExpression fileNamePattern(
        QStringLiteral("^app_log_(\\d{4}-\\d{2}-\\d{2})\\.txt$"));
    const QDir logDirectory = QDir::current();

    const QFileInfoList logFiles = logDirectory.entryInfoList(
        {QStringLiteral("app_log_*.txt")}, QDir::Files);
    for (const QFileInfo &fileInfo : logFiles) {
        const QRegularExpressionMatch match = fileNamePattern.match(fileInfo.fileName());
        const QDate fileDate = QDate::fromString(match.captured(1), QStringLiteral("yyyy-MM-dd"));
        if (!fileDate.isValid() || fileDate < oldestDateToKeep) {
            QFile::remove(fileInfo.absoluteFilePath());
        }
    }

    const QFileInfo legacyLogFile(logDirectory.filePath(QStringLiteral("app_log.txt")));
    if (legacyLogFile.exists() && legacyLogFile.lastModified().date() < oldestDateToKeep) {
        QFile::remove(legacyLogFile.absoluteFilePath());
    }
}

bool openDailyLogFile(const QDate &date)
{
    if (logFile.isOpen()) {
        logFile.close();
    }

    removeExpiredLogFiles(date);
    logFile.setFileName(QDir::current().filePath(dailyLogFileName(date)));
    logFileDate = date;
    return logFile.open(QIODevice::Append | QIODevice::Text);
}

} // namespace

void myMessageHandler(QtMsgType type,
    const QMessageLogContext& context,
    const QString& msg)
{
    QString level;

    switch (type) {
    case QtDebugMsg:
        level = "DEBUG";
        break;
    case QtInfoMsg:
        level = "INFO";
        break;
    case QtWarningMsg:
        level = "WARNING";
        break;
    case QtCriticalMsg:
        level = "CRITICAL";
        break;
    case QtFatalMsg:
        level = "FATAL";
        break;
    }

    const QDateTime timestamp = QDateTime::currentDateTime();
    const QString time = timestamp.toString("yyyy-MM-dd hh:mm:ss");

    QString logText = QString("[%1] [%2] %3")
        .arg(time)
        .arg(level)
        .arg(msg);

    // console
    fprintf(stdout, "%s\n", logText.toLocal8Bit().constData());

    QMutexLocker locker(&logFileMutex);
    if (logFileDate != timestamp.date()) {
        openDailyLogFile(timestamp.date());
    }

    if (logFile.isOpen()) {
        QTextStream stream(&logFile);
        stream << logText << Qt::endl;
        stream.flush();
    }

    if (type == QtFatalMsg)
        abort();
}

LONG WINAPI CrashHandler(EXCEPTION_POINTERS* pException)
{
    HANDLE hFile = CreateFile(
        L"crash.dmp",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION info;
        info.ThreadId = GetCurrentThreadId();
        info.ExceptionPointers = pException;
        info.ClientPointers = FALSE;
        MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hFile,
            MiniDumpNormal,
            &info,
            NULL,
            NULL);
        CloseHandle(hFile);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}

static QLocalServer* g_singleInstanceServer = nullptr;

static bool isAnotherInstanceRunning(const QString& serverName)
{
    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (socket.waitForConnected(300)) {
        return true;
    }

    QLocalServer::removeServer(serverName);

    g_singleInstanceServer = new QLocalServer(qApp);
    if (!g_singleInstanceServer->listen(serverName)) {
        delete g_singleInstanceServer;
        g_singleInstanceServer = nullptr;
        return true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    openDailyLogFile(QDate::currentDate());

    qInstallMessageHandler(myMessageHandler);
    SetUnhandledExceptionFilter(CrashHandler);
    //// 測試 crash
    //int* p = nullptr;
    //*p = 1;
    qDebug() << "程式啟動_V1.2.24_260730";
    set_qt_environment();


    QApplication app(argc, argv);
    const QString singleInstanceName = QStringLiteral("TaidaApp_single_instance_lock");

    if (isAnotherInstanceRunning(singleInstanceName)) {
        return 0;
    }
    
    Core& core = Core::instance();
    core.init();
    TdProxy *Td = core.m_proxy;
    qmlRegisterSingletonInstance<TdProxy>("Core", 1, 0, "Td", Td);


    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
                &engine, &QQmlApplicationEngine::objectCreated, &app,
                [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
