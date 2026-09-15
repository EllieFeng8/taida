#include "manager.h"

Manager::Manager(QObject* parent )
	: QObject(parent)
{
	init();
}

Manager::~Manager()
{
	// 安全停止 Server 執行緒
	if (m_ms300Thread) {
		m_ms300Thread->quit();
		m_ms300Thread->wait();
	}

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

bool Manager::readServerHoldingRegister(int address, quint16 *value) const
{
	if (!m_serverWorker || !value) {
		return false;
	}

	if (QThread::currentThread() == m_serverWorker->thread()) {
		return m_serverWorker->readHoldingRegister(address, value);
	}

	bool wasRead = false;
	ServerWorker *worker = m_serverWorker;
	const bool invoked = QMetaObject::invokeMethod(worker, [worker, address, value, &wasRead] {
		wasRead = worker->readHoldingRegister(address, value);
	}, Qt::BlockingQueuedConnection);
	return invoked && wasRead;
}

void Manager::init()
{
	m_ms300Thread = new QThread(this);
	m_ms300 = new MS300();
	m_ms300->moveToThread(m_ms300Thread);
	connect(m_ms300Thread, &QThread::started, m_ms300, &MS300::initPort);
	connect(m_ms300Thread, &QThread::finished, m_ms300, &QObject::deleteLater);

	connect(m_ms300, &MS300::dataUpdated, this, [this](int v) 
		{
			if (server_OK) {
				emit requestServerInputRegister(29, static_cast<quint16>(v));
			}
		}
		);

	m_clientThread = new QThread(this);
	m_clientWorker = new clientWorker();
	m_clientWorker->moveToThread(m_clientThread);
	connect(m_clientThread, &QThread::started, m_clientWorker, &clientWorker::init);
	connect(m_clientThread, &QThread::finished, m_clientWorker, &QObject::deleteLater);

	m_serverThread = new QThread(this);
	m_serverWorker = new ServerWorker();
	m_serverWorker->moveToThread(m_serverThread);
	connect(this, &Manager::requestServerHoldingRegister,
		m_serverWorker, &ServerWorker::updateHoldingRegister, Qt::QueuedConnection);
	connect(this, &Manager::requestServerHoldingRegisters,
		m_serverWorker, &ServerWorker::updateHoldingRegisters, Qt::QueuedConnection);
	connect(this, &Manager::requestServerInputRegister,
		m_serverWorker, &ServerWorker::updateInputRegister, Qt::QueuedConnection);
	connect(this, &Manager::requestServerInputRegisters,
		m_serverWorker, &ServerWorker::updateInputRegisters, Qt::QueuedConnection);
	connect(this, &Manager::requestServerCoil,
		m_serverWorker, &ServerWorker::updateCoils, Qt::QueuedConnection);
	connect(m_serverThread, &QThread::started, this, [=]() {QMetaObject::invokeMethod(
		m_serverWorker, [this]{
			m_serverWorker->init(502,"127.0.0.1",version_num1,version_num2,version_num3,version_year,version_date);
		},Qt::QueuedConnection
			); });
	connect(m_serverWorker, &ServerWorker::modbusDataChanged, this, [this](QModbusDataUnit::RegisterType table, int address, quint16 value) {
		if (table == QModbusDataUnit::HoldingRegisters) {
			quint16 _value;

			switch (address) {
			case 31: //
				this->WriteHoldingRegister(true, 24,value); // 同步回 Client 寫入實體設備
				break;
			case 32:  
				this->WriteHoldingRegister(true, 25, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false); 
				//	}, Qt::QueuedConnection);
				break;
			case 33:  
				this->WriteHoldingRegister(true, 26, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 34:  
				this->WriteHoldingRegister(true, 27, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 39:  
				this->WriteHoldingRegister(true, 32, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 40:  
				this->WriteHoldingRegister(true, 33, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 41:  
				this->WriteHoldingRegister(true, 34, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 42:  
				this->WriteHoldingRegister(true, 35, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 47:  
				this->WriteHoldingRegister(true, 40, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 48: 
				this->WriteHoldingRegister(true, 41, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 49:
				emit updateToUi(11, value);
				this->WriteHoldingRegister(true, 42, value);
				break;
			case 50:
				emit updateToUi(12, value);
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
				//this->set_sv2(value/40.96); //目標出風溫 >> 出水閥 (第二組PID的SV)
				break;
			case 60:
				//this->set_sv(value/4.096);//壓差 >> 風扇 (第一組PID的SV)
				break;
			case 63:
				if(value==0)
				{
					emit update_switch(1, false);
					this->set_mode1(false);
				}
				else if (value == 1)
				{
					emit update_switch(1, true);
					this->set_mode1(true);
				}
				break;
			case 64:
				if (value == 0)
				{
					emit update_switch(2,false);
					this->set_mode2(false);
				}
				else if (value == 1)
				{
					emit update_switch(2, true);

					this->set_mode2(true);
				}
				break;
			case 71:
				if (value == 0)
				{
					emit update_switch(3, false);
					this->set_FanPower(false);
				}
				else if (value == 1)
				{
					emit update_switch(3, true);
					this->set_FanPower(true);
				}
				break;
			case 72:
				if (value == 0)
				{
					emit update_switch(4, false);
					this->set_Estop(false);
				}
				else if (value == 1)
				{
					emit update_switch(4, true);
					this->set_Estop(true);
				}
				break;

			case 73:
				if (value == 1)
				{
					emit update_switch(5, true);
					this->set_Reset(true);
				}
				break;

			default:
				break;
			}
		}
		if (table == QModbusDataUnit::Coils)
		{
			quint16 _value;
			if (address == 17)
			{
				if (value) {
					qDebug() << "dryyyyyy";
					// Drying must own the valve output.  Disable PID-2 first so its
					// automatic MV cannot write H11 again after AO1 is closed.
					set_mode2(false);
					emit update_switch(2, false);
					set_AO1(0);

					timer.restart();
					dry_Over = false;
					qDebug() << "dryyyyyy2";
					motorFrequency(0);
					fan1TargetRpm(dryValue);
					fan2TargetRpm(dryValue);
					fan3TargetRpm(dryValue);
					fan4TargetRpm(dryValue);
					fan5TargetRpm(dryValue);
					fan6TargetRpm(dryValue);
					fan7TargetRpm(dryValue);
					fan8TargetRpm(dryValue);
					fan9TargetRpm(dryValue);
					qDebug() << "dryyyyyy3";
					// Use the normal UI/Server/Client path so PID-1 state remains in sync.
					set_mode1(false);
					emit update_switch(1, false);
				}
				else {
					qDebug() << "close dry mode";
					set_AO1(0);
					motorFrequency(0);
					fan1TargetRpm(0);
					fan2TargetRpm(0);
					fan3TargetRpm(0);
					fan4TargetRpm(0);
					fan5TargetRpm(0);
					fan6TargetRpm(0);
					fan7TargetRpm(0);
					fan8TargetRpm(0);
					fan9TargetRpm(0);
					//timer.restart();
					dry_Over = true;
				}
				emit updateToUi(17, value);
			}
			if (value != 0) {
				switch (address) {
				case 1:
					if (readServerHoldingRegister(31, &_value))
					{
						emit updateToUi(1, _value);
						this->WriteHoldingRegister(true, 24, _value);
					}
					emit requestServerCoil(1, false);
					break;
				case 2:
					if (readServerHoldingRegister(32, &_value))
					{
						emit updateToUi(2, _value);
						this->WriteHoldingRegister(true, 25, _value );
					}
					emit requestServerCoil(2, false);

					break;
				case 3:
					if (readServerHoldingRegister(33, &_value))
					{
						emit updateToUi(3, _value);

						this->WriteHoldingRegister(true, 26, _value);
					}
					emit requestServerCoil(3, false);

					break;
				case 4:
					if (readServerHoldingRegister(34, &_value))
					{
						emit updateToUi(4, _value);
						this->WriteHoldingRegister(true, 27, _value );
					}
					emit requestServerCoil(4, false);
					break;
				case 5:
					if (readServerHoldingRegister(39, &_value))
					{
						emit updateToUi(5, _value);
						this->WriteHoldingRegister(true, 32, _value);
					}
					emit requestServerCoil(5, false);

					break;
				case 6:
					if (readServerHoldingRegister(40, &_value))
					{
						emit updateToUi(6, _value);
						this->WriteHoldingRegister(true, 33, _value );
					}
					emit requestServerCoil(6, false);

					break;
				case 7:
					if (readServerHoldingRegister(41, &_value))
					{
						emit updateToUi(7, _value);
						this->WriteHoldingRegister(true, 34, _value );
					}
					emit requestServerCoil(7, false);

					break;
				case 8:
					if (readServerHoldingRegister(42, &_value))
					{
						emit updateToUi(8, _value);
						this->WriteHoldingRegister(true, 35, _value );
					}
					emit requestServerCoil(8, false);

					break;
				case 9:
					if (readServerHoldingRegister(47, &_value))
					{
						emit updateToUi(9, _value);
						this->WriteHoldingRegister(true, 40, _value );
					}
					emit requestServerCoil(9, false);
					break;
				case 10:
					if (readServerHoldingRegister(48, &_value))
					{
						emit updateToUi(10, _value);
						this->WriteHoldingRegister(true, 41, _value );
					}
					emit requestServerCoil(10, false);
					break;
				case 11:
					if (readServerHoldingRegister(49, &_value))
					{
						emit updateToUi(11, _value);
						this->WriteHoldingRegister(true, 42, _value );
					}
					emit requestServerCoil(11, false);
					break;
				case 12:
					if (readServerHoldingRegister(50, &_value))
					{
						emit updateToUi(12, _value);
						this->WriteHoldingRegister(false, 11, _value );

					}
					emit requestServerCoil(12, false);
					break;
				case 13:

					if (readServerHoldingRegister(51, &p1)
						&& readServerHoldingRegister(52, &i1)
						&& readServerHoldingRegister(53, &d1)) {
						this->set_PID(p1, i1, d1);
						emit update_PID(1, p1*1.0/1000, i1 * 1.0 /1000, d1 * 1.0/1000);
					}
					emit requestServerCoil(13, false);
					break;
				case 14:

					if (readServerHoldingRegister(54, &p2)
						&& readServerHoldingRegister(55, &i2)
						&& readServerHoldingRegister(56, &d2)) {
						emit update_PID(2, p2 * 1.0/1000, i2 * 1.0/1000, d2 * 1.0/1000);
						this->set_PID2(p2, i2, d2);
					}

					emit requestServerCoil(14, false);
					break;
				case 15:
					if (readServerHoldingRegister(58, &_value))
					{
						emit updateToUi(15, _value/100);
						this->set_sv2(_value);
					}
					emit requestServerCoil(15, false);
					break;
				case 16:
					if (readServerHoldingRegister(60, &_value))
					{
						if (!new_PD) {
							emit updateToUi(16, _value / 10);
						}
						else {
							emit updateToUi(16, (_value - 5000) / 4);
						}
						this->set_sv(_value);
					}
					emit requestServerCoil(16, false);
					break;
				default:
					break;
				}
			}
		}
		});
	// 將 Client 讀到的資料「接」給 Server
	// 當 Client 讀到資料發出 m_5000data 訊號時，自動呼叫 Server 的更新函數
		connect(m_clientWorker, &clientWorker::connected, this, [this]() { normal = true; });
		connect(m_clientWorker, &clientWorker::pidcontrolFan, this, [this](double MV1) {emit pidcontrolFan(MV1); });
		connect(m_clientWorker, &clientWorker::pidcontroloutvalue, this, [this](double MV2) {emit pidcontroloutvalue(MV2); });

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
		connect(m_clientWorker, &clientWorker::R_PV, this, [this](const QVector<quint16>& data) {
			if (server_OK) {
				emit requestServerInputRegister(27, data[3]);
				emit requestServerInputRegister(28, data[0]);
			}
			emit R_PV(data); });

		connect(m_serverWorker, &ServerWorker::server_stat, this, [=](bool v) {server_OK = v; emit server_on(); });
	connect(m_clientWorker, &clientWorker::m_5000Coil, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		if (server_OK) {
			m_serverWorker->updateInputRegisters(0, datainput); //將input的部分 傳入InputRegisters (從0開始)
			//m_serverWorker->updateHoldingRegisters(71, dataoutput);//將output的部分 傳入HoldingRegisters (從71開始)
		}});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, this, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		emit HodingRegister(data); //傳送給Core

		openValveP1 = data[13];
		openValveP2 = data[14];
		if (openValveP1 < (9830 + 65535 * 0.2) && openValveP2 < (9830 + 65535 * 0.2)) {
			this->motorFrequency(0); // 同步回 Client 寫入實體設備
		}

		auto ElapsedTimer = timer.elapsed() / 1000;
		qDebug() << "ElapsedTimer" << ElapsedTimer;
		auto t_str = dryTime - ElapsedTimer;
		if (t_str < 0) {
			t_str = 0;
		}
		else if (t_str > dryTime) {
			t_str = dryTime;
		}
		emit Elapsed(t_str);
		emit requestServerInputRegister(40, static_cast<quint16>(t_str));

		if (ElapsedTimer > dryTime && !dry_Over)
		{
			//set_allFan(0);
			fan1TargetRpm(0);
			fan2TargetRpm(0);
			fan3TargetRpm(0);
			fan4TargetRpm(0);
			fan5TargetRpm(0);
			fan6TargetRpm(0);
			fan7TargetRpm(0);
			fan8TargetRpm(0);
			fan9TargetRpm(0);
			emit requestServerCoil(17, false);
			emit updateToUi(17, false);
			dry_Over = true;
			qDebug() << "dry_Over";


		}
		});
	connect(m_clientWorker, &clientWorker::m_5000HodingRegister, m_serverWorker, [this](const QVector<quint16>& data, const QVector<quint16>& datainput, const QVector<quint16>& dataoutput) {
		if (server_OK) {

			emit update_input(datainput);
			emit update_savedata(m_serverWorker->SaveData);
			m_serverWorker->updateInputRegisters(11, datainput); //將input的部分 傳入InputRegisters (從11開始)
			m_serverWorker->updateHoldingRegisters(1, dataoutput);//將output的部分 傳入HoldingRegisters (從1開始)
		}
		});

	connect(m_clientWorker, &clientWorker::m_6022PID1, m_serverWorker, [this](const QVector<quint16>& data) {
		if (server_OK) {
			m_serverWorker->updateHoldingRegisters(21, data);
		}
		emit _PID1(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022PID2, m_serverWorker, [this](const QVector<quint16>& data) {
		if (server_OK) {
			m_serverWorker->updateHoldingRegisters(24, data);
		}
		emit _PID2(data);
		});
	//  Adam6022 資料放在 Server 的InputRegister 27,28
	connect(m_clientWorker, &clientWorker::m_6022PV1, m_serverWorker, [this](const QVector<quint16>& data) {
		if (server_OK) {
			//m_serverWorker->updateInputRegister(27, data[0]);
			m_serverWorker->updateHoldingRegister(59, data[0]);
		}
		emit _PV1(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022PV2, m_serverWorker, [this](const QVector<quint16>& data) {
		if (server_OK) {
			//m_serverWorker->updateInputRegister(28, data[0]);
			m_serverWorker->updateHoldingRegister(57, data[0]);
		}
		emit _PV2(data);
		});
	connect(m_clientWorker, &clientWorker::m_6022MV, m_serverWorker, [this](const QVector<quint16>& data) {
		emit _MV(data);
		PID_AO1 = data[0];
		PID_AO2 = data[1];
		if (server_OK) {
			m_serverWorker->updateInputRegister(26, PID_AO1);
			m_serverWorker->updateHoldingRegister(20, PID_AO2);
		}
		});

	m_ms300Thread->start();

	m_serverThread->start();

	m_clientThread->start();
}

void Manager::set_mode1(bool v)
{
	qDebug() << "set pid-1  mode : " << v;
	emit requestServerHoldingRegister(63, v);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Mode1(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_mode2(bool v)
{
	qDebug() << "set pid-2  mode : " << v;
	emit requestServerHoldingRegister(64, v);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Mode2(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv(int v)
{
	double value = v;
	emit requestServerHoldingRegister(60, static_cast<quint16>(value));
	qDebug() << value;
	//m_serverWorker->updateCoils(16,true);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV1( v*10); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv2(int v)
{

	emit requestServerHoldingRegister(58, static_cast<quint16>(v));
	//m_serverWorker->updateCoils(15, true);

	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV2(v*10); },
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
	emit requestServerHoldingRegisters(51, data);
	//m_serverWorker->updateCoils(13, true);
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
	emit requestServerHoldingRegisters(54, data);
	//m_serverWorker->updateCoils(14, true);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, p, i, d] { m_clientWorker->set_PID2(p, i, d); },
		Qt::QueuedConnection
	);
}
void Manager::set_AO1(double v)
{
	double percent = v; // 0~100

	const double minValue = 4096.0 * 0.20; // 819
	const double maxValue = 4096.0 * 0.95; // 3891

	quint16 modbusValue =
		minValue + (percent / 100.0) * (maxValue - minValue);

	quint16 value = v * 40.96;
	emit requestServerHoldingRegister(50, modbusValue);

	QMetaObject::invokeMethod(
		m_clientWorker, [this, modbusValue] { m_clientWorker->set_AO1(modbusValue); },
		Qt::QueuedConnection
	);
}
void Manager::motorFrequency(double v)
{
	double value = v * 40.96/0.6;

	/*QVector<quint16> data;
	data.resize(1);
	data[0] = v;*/
	if(_STO)
	{
		emit requestServerHoldingRegister(31, 0);
		qDebug() << "set motorFrequency =" << value<< " BUT! STO ON set 0" ;
		return;
	}
	emit requestServerHoldingRegister(31, static_cast<quint16>(value));
	//m_serverWorker->updateCoils(1, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, v] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 24, v); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan1TargetRpm(double v) 
{
	double value = v * 40.96;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if(_E_STOP)
	{
		qDebug() << "set fan1 but E_STOP ON";
		emit requestServerHoldingRegisters(32, QVector<quint16>{ 0 });
	}
	else {
		emit requestServerHoldingRegisters(32, data);
	}//m_serverWorker->updateCoils(2, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 25, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan2TargetRpm(double v)
{
	double value = v * 40.96;
	qDebug() << v;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(33, QVector<quint16>{ 0 });
		qDebug() << "set fan2 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(33, data);
	}
	//m_serverWorker->updateCoils(3, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 26, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan3TargetRpm(double v) 
{
	double value = v * 40.96;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(34, QVector<quint16>{ 0 });
		qDebug() << "set fan3 but E_STOP ON";
	}
	else {
		emit requestServerHoldingRegisters(34, data);
	}
	//m_serverWorker->updateCoils(4, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 27, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan4TargetRpm(double v) 
{
	double value = v * 40.96;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(39, QVector<quint16>{ 0 });
		qDebug() << "set fan4 but E_STOP ON";
	}
	else {
		emit requestServerHoldingRegisters(39, data);
	}
	//m_serverWorker->updateCoils(5, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 32, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan5TargetRpm(double v) 
{
	double value = v * 40.96;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(40, QVector<quint16>{ 0 });
		qDebug() << "set fan5 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(40, data);
	}
	//m_serverWorker->updateCoils(6, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 33, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan6TargetRpm(double v) 
{
	double value = v * 40.96;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(41, QVector<quint16>{ 0 });
		qDebug() << "set fan6 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(41, data);
	}
	//m_serverWorker->updateCoils(7, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 34, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan7TargetRpm(double v) 
{
	double value = v * 40.96;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(42, QVector<quint16>{ 0 });
		qDebug() << "set fan7 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(42, data);
	}
	//m_serverWorker->updateCoils(8, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 35, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan8TargetRpm(double v) 
{
	double value = v * 40.96;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP){
		emit requestServerHoldingRegisters(47, QVector<quint16>{ 0 });
		qDebug() << "set fan8 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(47, data);
	}
	//m_serverWorker->updateCoils(9, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 40, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::fan9TargetRpm(double v) 
{
	double value = v * 40.96;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_E_STOP)
	{
		emit requestServerHoldingRegisters(48, QVector<quint16>{ 0 });
		qDebug() << "set fan9 but E_STOP ON";

	}
	else {
		emit requestServerHoldingRegisters(48, data);
	}
	//m_serverWorker->updateCoils(10, true);
	//QMetaObject::invokeMethod(
	//	m_clientWorker, [this, value] { m_clientWorker->WriteSingleHoldingRegisters(true, 1, 41, value); },
	//	Qt::QueuedConnection
	//);
}
void Manager::returnValveOpening(double v) 
{
	double percent = v; // 0~100
	qDebug()<<"return openning= "<<v;
	const double minValue = 4096.0 * 0.20; // 819
	const double maxValue = 4096.0 * 0.95; // 3891

	quint16 modbusValue =
		minValue + (percent / 100.0) * (maxValue - minValue);

	QVector<quint16> data;
	data.resize(1);
	data[0] = modbusValue;
	// H49 is the single source of truth for the return-valve command. Its
	// dataWritten path maps the already-scaled value to ADAM-5000 H42.
	emit requestServerHoldingRegisters(49, data);
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
	_STO = v;
	qDebug() << "set E-stop: " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_STO2(v); },
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
	qDebug() << "set all Fan  ="<<v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this,v] { m_clientWorker->set_Fan(v); },
		Qt::QueuedConnection
	);
}

void Manager::set_server(int value)
{
	//if (value == 0) {
	//	QMetaObject::invokeMethod(
	//		m_serverWorker, [this]
	//		{
	//			m_serverWorker->init(502,ip); },
	//			Qt::QueuedConnection
	//			);
	//}
	//else if (value == 1)
	//	QMetaObject::invokeMethod(
	//		m_serverWorker, [this]
	//		{
	//			m_serverWorker->init(502,"127.0.0.1"); },
	//			Qt::QueuedConnection
	//			);
}
void Manager::set_motor(bool v)
{//水泵STO
	_STO = v;
	quint16 value = v ? 1 : 0;
	emit requestServerHoldingRegister(72, value);
	qDebug() << "set motor ";
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] 
		{

			m_clientWorker->set_STO2(v);
		
		},
		Qt::QueuedConnection
	);
}
void Manager::set_FanPower(bool v)
{
	_E_STOP = v;
	if (_E_STOP) {
		set_allFan(0);
	}
	quint16 value = v ? 0 : 1;	//緊急停止開啟 = 電源關閉
	//m_serverWorker->updateHoldingRegister(73, value);
	qDebug() << "set fan E_STOP " <<_E_STOP;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, value] { m_clientWorker->set_FanPower(value); },
		Qt::QueuedConnection
	);
}
void Manager::set_dry(bool v)
{
	emit requestServerCoil(17, v);
}
void Manager::set_dryTime(int v)
{
	dryTime = v;
}
void Manager::set_dryValue(int v)
{
	dryValue = v;
}
