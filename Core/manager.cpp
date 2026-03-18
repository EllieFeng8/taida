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

	// 將 Client 讀到的資料「接」給 Server 
	// 當 Client 讀到資料發出 m_5000data 訊號時，自動呼叫 Server 的更新函數
	connect(m_clientWorker, &clientWorker::m_5000Coil, this, [this](const QVector<quint16>& data,const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		emit Coil(data);//傳送給Core 
		});
	connect(m_clientWorker, &clientWorker::m_5000Coil, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		m_serverWorker->updateInputRegisters(0, datainput); //將input的部分 傳入InputRegisters (從0開始)
		m_serverWorker->updateHoldingRegisters(58, dataoutput);//將output的部分 傳入HoldingRegisters (從41開始)
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, this, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		emit HodingRegister(datainput); //傳送給Core
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		m_serverWorker->updateInputRegisters(11, datainput); //將input的部分 傳入InputRegisters (從11開始)
		m_serverWorker->updateHoldingRegisters(0, dataoutput);//將output的部分 傳入HoldingRegisters (從0開始)

		});

	connect(m_clientWorker, &clientWorker::m_6022PID1, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateHoldingRegisters(21, data);
		emit _PID1(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022PID2, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateHoldingRegisters(24, data);
		emit _PID2(data);
		});
	//  Adam6022 資料放在 Server 的InputRegister 27,28
	connect(m_clientWorker, &clientWorker::m_6022PV1, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateInputRegister(27, data[0]);
		m_serverWorker->updateHoldingRegister(59, data[1]);

		emit _PV1(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022PV2, m_serverWorker, [this](const QVector<quint16>& data) {
		m_serverWorker->updateInputRegister(28, data[0]);
		m_serverWorker->updateHoldingRegister(57, data[1]);

		emit _PV2(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022MV, m_serverWorker, [this](const QVector<quint16>& data) {
		emit _MV(data);
		PID_AO1 = data[0];
		PID_AO2 = data[1];
		m_serverWorker->updateHoldingRegister(20, PID_AO1);
		m_serverWorker->updateHoldingRegister(50, PID_AO2);

		});


	m_clientThread->start();
	m_serverThread->start();


}

void Manager::set_mode1(bool v)
{
	qDebug() << "set pid-1  mode : " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->m_mode1 = v; },
		Qt::QueuedConnection
	);
}
void Manager::set_mode2(bool v)
{
	qDebug() << "set pid-2  mode : " << v;

	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->m_mode2 = v; },
		Qt::QueuedConnection
	);
}
void Manager::set_sv(int v)
{
	m_serverWorker->updateHoldingRegister(60, v);

	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV1( v); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv2(int v)
{
	m_serverWorker->updateHoldingRegister(58,v);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV2(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_PID(double p, double i, double d)
{
	QVector<quint16> data;
	data.resize(3);
	data[0] = p;
	data[1] = i;
	data[2] = d;
	m_serverWorker->updateHoldingRegisters(51, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, p,i,d] { m_clientWorker->set_PID1(p,i,d); },
		Qt::QueuedConnection
	);
}
void Manager::set_PID2(double p, double i, double d)
{
	QVector<quint16> data;
	data.resize(3);
	data[0] = p;
	data[1] = i;
	data[2] = d;
	m_serverWorker->updateHoldingRegisters(54, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, p, i, d] { m_clientWorker->set_PID2(p, i, d); },
		Qt::QueuedConnection
	);
}
void Manager::motorFrequency(double v)
{
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(31,data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 24, v); },
		Qt::QueuedConnection
	);
}
void Manager::fan1TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> test;
	test.resize(34);
	test.fill(173);
	emit HodingRegister(test);
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(32, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 25, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan2TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(33, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 26, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan3TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(34, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 27, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan4TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(39, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 32, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan5TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(40, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 33, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan6TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(41, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 34, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan7TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(42, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 35, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan8TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(47, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 40, value); },
		Qt::QueuedConnection
	);
}
void Manager::fan9TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(48, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 41, value); },
		Qt::QueuedConnection
	);
}
void Manager::returnValveOpening(double v) 
{
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(49, data);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 42, v); },
		Qt::QueuedConnection
	);
}