#include "manager.h"

Manager::Manager(QObject* parent )
	: QObject(parent)
{
	init();
}

Manager::~Manager()
{
	// 安全停止 Client 執行緒
	if (m_clientThread) {
		m_clientThread->quit();
		m_clientThread->wait(); // 等待執行緒完全結束
	}

	// 安全停止 Server 執行緒
	if (m_serverThread) {
		m_serverThread->quit();
		m_serverThread->wait();
	}
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
	connect(m_serverWorker, &ServerWorker::modbusDataChanged, this, [this](QModbusDataUnit::RegisterType table, int address, quint16 value) {
		if (table == QModbusDataUnit::HoldingRegisters) {
			quint16 _value;

			switch (address) {
			case 31: //
				this->WriteHoldingRegister(true, 24,value*40.95); // 同步回 Client 寫入實體設備
				break;
			case 32:  
				this->WriteHoldingRegister(true, 25, value*40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false); 
					}, Qt::QueuedConnection);
				break;
			case 33:  
				this->WriteHoldingRegister(true, 26, value*40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 34:  
				this->WriteHoldingRegister(true, 27, value*40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 39:  
				this->WriteHoldingRegister(true, 32, value*40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 40:  
				this->WriteHoldingRegister(true, 33, value * 40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 41:  
				this->WriteHoldingRegister(true, 34, value * 40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 42:  
				this->WriteHoldingRegister(true, 35, value * 40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 47:  
				this->WriteHoldingRegister(true, 40, value * 40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 48: 
				this->WriteHoldingRegister(true, 41, value * 40.95);
				QMetaObject::invokeMethod(m_clientWorker, [this]() {
					m_clientWorker->set_Mode1(false);
					}, Qt::QueuedConnection);
				break;
			case 49:
				this->WriteHoldingRegister(true, 42, value * 40.95);
				break;
			case 50:
				this->WriteHoldingRegister(false, 11, value);// 6022 的AO1 (出水閥開度)
				break;
			case 51:
				qDebug() << value;
				p1 = value;
				//第一組PID--P
				break;
			case 52:
				i1 = value;
				//第一組PID--I
				break;
			case 53:
				d1 = value;
				//第一組PID--D
				break;
			case 54:
				p2 = value;
				//第二組PID--P
				break;
			case 55:
				i2 = value;
				//第二組PID--I
				break;
			case 56:
				d2 = value;
				//第二組PID--D
				break;
			case 58:
				this->set_sv2(value); //目標出風溫 >> 出水閥 (第二組PID的SV)
				break;
			case 60:
				this->set_sv(value);//壓差 >> 風扇 (第一組PID的SV)
				break;
			default:
				break;
			}
		}
		if (table == QModbusDataUnit::Coils)
		{
			quint16 _value;
			if (value == 1) {
				switch (address) {
				case 1:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 31, &_value))
					{
						this->WriteHoldingRegister(true, 24, _value * 40.95);
					}
					m_serverWorker->updateCoils(1, false);
					break;
				case 2:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 32, &_value))
					{
						this->WriteHoldingRegister(true, 25, _value * 40.95);
					}
					m_serverWorker->updateCoils(2, false);

					break;
				case 3:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 33, &_value))
					{
						this->WriteHoldingRegister(true, 26, _value * 40.95);
					}
					m_serverWorker->updateCoils(3, false);

					break;
				case 4:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 34, &_value))
					{
						this->WriteHoldingRegister(true, 27, _value * 40.95);
					}
					m_serverWorker->updateCoils(4, false);
					break;
				case 5:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 39, &_value))
					{
						this->WriteHoldingRegister(true, 32, _value * 40.95);
					}
					m_serverWorker->updateCoils(5, false);

					break;
				case 6:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 40, &_value))
					{
						this->WriteHoldingRegister(true, 33, _value * 40.95);
					}
					m_serverWorker->updateCoils(6, false);

					break;
				case 7:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 41, &_value))
					{
						this->WriteHoldingRegister(true, 34, _value * 40.95);
					}
					m_serverWorker->updateCoils(7, false);

					break;
				case 8:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 42, &_value))
					{
						this->WriteHoldingRegister(true, 35, _value * 40.95);
					}
					m_serverWorker->updateCoils(8, false);

					break;
				case 9:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 47, &_value))
					{
						this->WriteHoldingRegister(true, 40, _value * 40.95);
					}
					m_serverWorker->updateCoils(9, false);
					break;
				case 10:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 48, &_value))
					{
						this->WriteHoldingRegister(true, 41, _value * 40.95);
					}
					m_serverWorker->updateCoils(10, false);
					break;
				case 11:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 49, &_value))
					{
						this->WriteHoldingRegister(true, 42, _value * 40.95);
					}
					m_serverWorker->updateCoils(11, false);
					break;
				case 12:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 50, &_value))
					{
						this->WriteHoldingRegister(false, 11, _value * 40.95);

					}
					m_serverWorker->updateCoils(12, false);
					break;
				case 13:

					//m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 51, &p1);
					//m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 52, &i1);
					//m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 53, &d1);
					this->set_PID(p1, i1, d1);

					m_serverWorker->updateCoils(13, false);
					break;
				case 14:

					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 54, &p2);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 55, &i2);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 56, &d2);
					this->set_PID2(p2, i2, d2);

					m_serverWorker->updateCoils(14, false);
					break;
				case 15:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 58, &_value))
					{
						this->set_sv2(_value);
					}
					m_serverWorker->updateCoils(15, false);
					break;
				case 16:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 60, &_value))
					{
						this->set_sv(_value);
					}
					m_serverWorker->updateCoils(16, false);
					break;
				default:
					break;
				}
			}
		}
		});
	// 將 Client 讀到的資料「接」給 Server 
	// 當 Client 讀到資料發出 m_5000data 訊號時，自動呼叫 Server 的更新函數
	connect(m_clientWorker, &clientWorker::m_5000Coil, this, [this](const QVector<quint16>& data,const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		emit Coil(data);//傳送給Core 
		
		if(data[0]==1&& normal)
		{
			QMetaObject::invokeMethod(
				m_clientWorker, [this] { m_clientWorker->set_FanPower(false); },
				Qt::QueuedConnection
			);
			normal = false;
		}
		else if(data[0]==0 && !normal)
		{
			QMetaObject::invokeMethod(
				m_clientWorker, [this] { m_clientWorker->set_FanPower(true); },
				Qt::QueuedConnection
			);
			normal = true;
		}
		});
	connect(m_clientWorker, &clientWorker::m_5000Coil, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		m_serverWorker->updateInputRegisters(0, datainput); //將input的部分 傳入InputRegisters (從0開始)
		m_serverWorker->updateHoldingRegisters(71, dataoutput);//將output的部分 傳入HoldingRegisters (從71開始)
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, this, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		emit HodingRegister(data); //傳送給Core
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		m_serverWorker->updateInputRegisters(11, datainput); //將input的部分 傳入InputRegisters (從11開始)
		m_serverWorker->updateHoldingRegisters(1, dataoutput);//將output的部分 傳入HoldingRegisters (從1開始)

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
		m_clientWorker, [this, v] { m_clientWorker->set_Mode1(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_mode2(bool v)
{
	qDebug() << "set pid-2  mode : " << v;

	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Mode2(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv(int v)
{
	m_serverWorker->updateHoldingRegister(60, v);
	m_serverWorker->updateCoils(16,true);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV1( v); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv2(int v)
{
	m_serverWorker->updateHoldingRegister(58,v);
	m_serverWorker->updateCoils(15, true);

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
	m_serverWorker->updateCoils(13, true);
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
	m_serverWorker->updateCoils(14, true);
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
	m_serverWorker->updateCoils(1, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 24, v); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan1TargetRpm(double v) 
{
	double value = v * 40.95;

	//QVector<quint16> test;
	//test.resize(34);
	//test.fill(173);
	//emit HodingRegister(test);
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(32, data);
	m_serverWorker->updateCoils(2, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 25, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan2TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(33, data);
	m_serverWorker->updateCoils(3, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 26, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan3TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(34, data);
	m_serverWorker->updateCoils(4, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 27, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan4TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(39, data);
	m_serverWorker->updateCoils(5, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 32, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan5TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(40, data);
	m_serverWorker->updateCoils(6, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 33, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan6TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(41, data);
	m_serverWorker->updateCoils(7, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 34, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan7TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(42, data);
	m_serverWorker->updateCoils(8, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 35, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan8TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(47, data);
	m_serverWorker->updateCoils(9, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 40, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan9TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(48, data);
	m_serverWorker->updateCoils(10, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 41, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::returnValveOpening(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = v;
	m_serverWorker->updateHoldingRegisters(49, data);
	m_serverWorker->updateCoils(11, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 42, value); },
	//	Qt::QueuedConnection
	//);
}

void Manager::WriteHoldingRegister(bool t,int addr, double value)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this,t,addr,value] { m_clientWorker->set_5000HoldingRegister(t ,addr, value); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan1Open(bool v)
{
	qDebug() << "set Fan1  " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan1Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan2Open(bool v)
{
	qDebug() << "set Fan2 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan2Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan3Open(bool v)
{
	qDebug() << "set Fan3 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan3Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan4Open(bool v)
{
	qDebug() << "set Fan4 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan4Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan5Open(bool v)
{
	qDebug() << "set Fan5 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan5Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan6Open(bool v)
{
	qDebug() << "set Fan6 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan6Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan7Open(bool v)
{
	qDebug() << "set Fan7 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan7Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan8Open(bool v)
{
	qDebug() << "set Fan8 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan8Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Fan9Open(bool v)
{
	qDebug() << "set Fan9 " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Fan9Open(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Estop(bool v)
{
	qDebug() << "set E-stop: " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_STO(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_Reset(bool v)
{
	qDebug() << "set Reset  ";
	QMetaObject::invokeMethod(
		m_clientWorker, [this] { m_clientWorker->set_Reset(); },
		Qt::QueuedConnection
	);
}
void Manager::set_allFan(double v)
{
	qDebug() << "set all Fan  ";
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->set_Fan(v); },
		Qt::QueuedConnection
	);
}