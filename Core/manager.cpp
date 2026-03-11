#include "manager.h"

Manager::Manager(QObject* parent )
	: QObject(parent)
{
	init();
}

Manager::~Manager()
{

}

void Manager::init()
{
	m_clientThread = new QThread(this);
	m_clientWorker = new clientWorker();
	m_clientWorker->moveToThread(m_clientThread);
	connect(m_clientThread, &QThread::started, m_clientWorker, &clientWorker::init);
	connect(m_clientThread, &QThread::finished, m_clientWorker, &QObject::deleteLater);

	m_serverThread = new QThread(this);
	m_serverWorker = new ServerWorker();
	m_serverWorker->moveToThread(m_serverThread);
	connect(m_serverThread, &QThread::started, m_serverWorker, &ServerWorker::init);

	// --- 關鍵：將 Client 讀到的資料「橋接」給 Server ---
	// 當 Client 讀到資料發出 m_5000data 訊號時，自動呼叫 Server 的更新函數
	connect(m_clientWorker, &clientWorker::m_5000Coil, this, [this](const QVector<quint16>& data) {
		emit Coil(data);
		});
	connect(m_clientWorker, &clientWorker::m_5000Coil, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateHoldingRegisters(0, data);
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, this, [this](const QVector<quint16>& data) {
		emit HodingRegister(data);
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateHoldingRegisters(0, data);
		});


	// 假設 Adam6022 資料放在 Server 的位址 50~59
	connect(m_clientWorker, &clientWorker::m_6022HodingRegister, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateHoldingRegisters(50, data);
		});

	m_clientThread->start();
	m_serverThread->start();
}

void Manager::set_mode(bool v)
{
		//0 : Free mode -- no PID control , ADAM -- 6022 will be a pure I / O module
		//1 : PID mode -- enable PID loop function
		//2 : Manual mode -- manual control analog output
	if (v) // mode 
	{
		QMetaObject::invokeMethod(
			m_clientWorker, [this] { m_clientWorker->writeSV(999, 1); },
			Qt::QueuedConnection
		);
	}
	if (!v) //mode 
	{
		QMetaObject::invokeMethod(
			m_clientWorker, [this] { m_clientWorker->writeSV(999, 2);  },
			Qt::QueuedConnection
		);
	}
}
void Manager::set_sv(int v)
{
	
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->writeSV(1019, v); },
		Qt::QueuedConnection
	);
}
void Manager::set_p1(int v)
{
	qDebug() << "set PID P = " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1061, v);  },
		Qt::QueuedConnection
	);
}
void Manager::set_i1(int v)

{
	qDebug() << "set PID I = " << v;

	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1063, v); },
		Qt::QueuedConnection
	);
}
void Manager::set_d1(int v)
{
	qDebug() << "set PID D = " << v;

	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1065, v);  },
		Qt::QueuedConnection
	);
}

void Manager::set_p2(int v)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1317, v); },
		Qt::QueuedConnection
	);
}
void Manager::set_i2(int v)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1319, v); },
		Qt::QueuedConnection
	);
}
void Manager::set_d2(int v)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->writeSV(1321, v); },
		Qt::QueuedConnection
	);
}

void Manager::motorFrequency(double v)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan1TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 30, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan2TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 31, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan3TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 32, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan4TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan5TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan6TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan7TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan8TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan9TargetRpm(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}
void Manager::returnValveOpening(double v) 
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 29, v); },
		Qt::QueuedConnection
	);
}