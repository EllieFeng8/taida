// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QApplication>
#include <QQmlApplicationEngine>

#include "autogen/environment.h"
#include "Core/TdProxy.h"
#include "Core/core.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QApplication app(argc, argv);
    
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
