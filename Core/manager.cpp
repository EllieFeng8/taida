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
				m_serverWorker->updateInputRegister(29, v);
			}
		});


	m_clientThread = new QThread(this);
	m_clientWorker = new clientWorker();
	m_clientWorker->moveToThread(m_clientThread);
	connect(m_clientThread, &QThread::started, m_clientWorker, &clientWorker::init);
	connect(m_clientThread, &QThread::finished, m_clientWorker, &QObject::deleteLater);

	m_serverThread = new QThread(this);
	m_serverWorker = new ServerWorker();
	m_serverWorker->moveToThread(m_serverThread);
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
				this->WriteHoldingRegister_204(0, value); // 同步回 Client 寫入實體設備
				break;
			case 32:
				this->WriteHoldingRegister_204(1, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false); 
				//	}, Qt::QueuedConnection);
				break;
			case 33:
				this->WriteHoldingRegister_204(2, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 34:
				this->WriteHoldingRegister_204(3, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 39:
				this->WriteHoldingRegister_205(0, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 40:
				this->WriteHoldingRegister_205(1, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 41:
				this->WriteHoldingRegister_205(2, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 42:
				this->WriteHoldingRegister_205(3, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 47:
				this->WriteHoldingRegister_206(0, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 48:
				this->WriteHoldingRegister_206(1, value);
				//QMetaObject::invokeMethod(m_clientWorker, [this]() {
				//	m_clientWorker->set_Mode1(false);
				//	}, Qt::QueuedConnection);
				break;
			case 49:
				this->WriteHoldingRegister_206(2, value);
				break;
			case 50:
				this->WriteHoldingRegister_6022(11, value);// 6022 的AO1 (出水閥開度)
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
				if (value == 0)
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
					emit update_switch(2, false);
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
					this->set_FanEstop(false);
				}
				else if (value == 1)
				{
					emit update_switch(3, true);
					this->set_FanEstop(true);
				}
				break;
			case 72:
				if (value == 0)
				{
					emit update_switch(4, false);
					this->set_motorEstop(false);
				}
				else if (value == 1)
				{
					emit update_switch(4, true);
					this->set_motorEstop(true);
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
			if (value != 0) {
				switch (address) {
				case 1:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 31, &_value))
					{
						emit updateToUi(1, _value);
						this->WriteHoldingRegister_204(0, _value);
					}
					m_serverWorker->updateCoils(1, false);
					break;
				case 2:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 32, &_value))
					{
						emit updateToUi(2, _value);
						this->WriteHoldingRegister_204(1, _value);
					}
					m_serverWorker->updateCoils(2, false);

					break;
				case 3:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 33, &_value))
					{
						emit updateToUi(3, _value);

						this->WriteHoldingRegister_204(2, _value);
					}
					m_serverWorker->updateCoils(3, false);

					break;
				case 4:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 34, &_value))
					{
						emit updateToUi(4, _value);
						this->WriteHoldingRegister_204(3, _value);
					}
					m_serverWorker->updateCoils(4, false);
					break;
				case 5:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 39, &_value))
					{
						emit updateToUi(5, _value);
						this->WriteHoldingRegister_205(0, _value);
					}
					m_serverWorker->updateCoils(5, false);

					break;
				case 6:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 40, &_value))
					{
						emit updateToUi(6, _value);
						this->WriteHoldingRegister_205(1, _value);
					}
					m_serverWorker->updateCoils(6, false);

					break;
				case 7:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 41, &_value))
					{
						emit updateToUi(7, _value);
						this->WriteHoldingRegister_205(2, _value);
					}
					m_serverWorker->updateCoils(7, false);

					break;
				case 8:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 42, &_value))
					{
						emit updateToUi(8, _value);
						this->WriteHoldingRegister_205(3, _value);
					}
					m_serverWorker->updateCoils(8, false);

					break;
				case 9:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 47, &_value))
					{
						emit updateToUi(9, _value);
						this->WriteHoldingRegister_206(0, _value);
					}
					m_serverWorker->updateCoils(9, false);
					break;
				case 10:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 48, &_value))
					{
						emit updateToUi(10, _value);
						this->WriteHoldingRegister_206(1, _value);
					}
					m_serverWorker->updateCoils(10, false);
					break;
				case 11:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 49, &_value))
					{
						emit updateToUi(11, _value);
						this->WriteHoldingRegister_206(2, _value);
					}
					m_serverWorker->updateCoils(11, false);
					break;
				case 12:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 50, &_value))
					{
						emit updateToUi(12, _value);
						this->WriteHoldingRegister_6022(11, _value);

					}
					m_serverWorker->updateCoils(12, false);
					break;
				case 13:

					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 51, &p1);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 52, &i1);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 53, &d1);
					this->set_PID(p1, i1, d1);
					emit update_PID(1, p1 * 1.0 / 1000, i1 * 1.0 / 1000, d1 * 1.0 / 1000);
					m_serverWorker->updateCoils(13, false);
					break;
				case 14:

					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 54, &p2);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 55, &i2);
					m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 56, &d2);
					emit update_PID(2, p2 * 1.0 / 1000, i2 * 1.0 / 1000, d2 * 1.0 / 1000);
					this->set_PID2(p2, i2, d2);

					m_serverWorker->updateCoils(14, false);
					break;
				case 15:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 58, &_value))
					{
						emit updateToUi(15, _value / 100);
						this->set_sv2(_value);
					}
					m_serverWorker->updateCoils(15, false);
					break;
				case 16:
					if (m_serverWorker->m_server->data(QModbusDataUnit::HoldingRegisters, 60, &_value))
					{
						emit updateToUi(16, (_value-5000)/4);
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
	connect(m_clientWorker, &clientWorker::connected, this, [this]() { normal = true; emit client_on(); });
	connect(m_serverWorker, &ServerWorker::server_stat, this, [=](bool v) {server_OK = v; emit server_on(); });
	connect(m_clientWorker, &clientWorker::pidcontrolFan, this, [this](double MV1) {emit pidcontrolFan(MV1); });
	connect(m_clientWorker, &clientWorker::pidcontroloutvalue, this, [this](double MV2) {emit pidcontroloutvalue(MV2); });

	connect(m_clientWorker, &clientWorker::R_PV, this, [this](const QVector<quint16>& data) {
		if (server_OK) {
			m_serverWorker->updateInputRegister(27, data[3]  );
			m_serverWorker->updateInputRegister(28, data[0] );
		}
		emit R_PV(data); });
	// TODO :
// 以下connect要替換成adam6000版本 讀取DI後 將讀值寫入對應server的正確位置 

	connect(m_clientWorker, &clientWorker::input_DATA, this, [this](readInput_Data data)
		{
			if(data.AI_202.isEmpty())
			if (data.DI_201[0] = 0 && normal)//判斷欠逆相檢出 
			{
				QMetaObject::invokeMethod(
					m_clientWorker, [this] { m_clientWorker->set_FanPower(false); m_clientWorker->set_MotorRun(false); }, //關閉風扇及馬達電源
					Qt::QueuedConnection
				);
				normal = false;
			}
			else if (data.DI_201[0] = 1 && !normal)
			{
				QMetaObject::invokeMethod(
					m_clientWorker, [this] { m_clientWorker->set_FanPower(true); m_clientWorker->set_MotorRun(true); }, //開啟風扇及馬達電源
					Qt::QueuedConnection
				);
				normal = true;
			}	
			
			//將讀取到的數值更新到server
			if (server_OK) {
				m_serverWorker->updateHoldingRegisters(1,data.AO_204);
				m_serverWorker->updateHoldingRegisters(9, data.AO_205);
				m_serverWorker->updateHoldingRegisters(17, data.AO_206);
				m_serverWorker->updateInputRegister(0, data.DI_201[0]);//相位檢出
				m_serverWorker->updateInputRegister(1, data.DI_201[1]);//風扇1異常
				m_serverWorker->updateInputRegister(2, data.DI_201[2]);//風扇2異常
				m_serverWorker->updateInputRegister(3, data.DI_201[3]);//風扇3異常
				m_serverWorker->updateInputRegister(4, data.DI_201[4]);//風扇4異常
				m_serverWorker->updateInputRegister(5, data.DI_201[5]);//風扇5異常
				m_serverWorker->updateInputRegister(6, data.DI_201[6]);//風扇6異常
				m_serverWorker->updateInputRegister(7, data.DI_201[7]);//風扇7異常
				m_serverWorker->updateInputRegister(8, data.DI_204[0]);//風扇8異常
				m_serverWorker->updateInputRegister(9, data.DI_204[1]);//風扇9異常
				m_serverWorker->updateInputRegister(10, data.DI_204[2]);//水泵異常
				m_serverWorker->updateInputRegisters(11, data.AI_202);
				m_serverWorker->updateInputRegisters(19, data.AI_203);
				emit senserData(data, m_serverWorker->SaveData);
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
	m_serverWorker->updateHoldingRegister(63, v);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Mode1(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_mode2(bool v)
{
	qDebug() << "set pid-2  mode : " << v;
	m_serverWorker->updateHoldingRegister(64, v);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_Mode2(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv(int v)
{
	double value = v;
	m_serverWorker->updateHoldingRegister(60, value);
	//m_serverWorker->updateCoils(16,true);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_SV1( v*10); },
		Qt::QueuedConnection
	);
}
void Manager::set_sv2(int v)
{

	m_serverWorker->updateHoldingRegister(58, v);
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
	m_serverWorker->updateHoldingRegisters(51, data);
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
	m_serverWorker->updateHoldingRegisters(54, data);
	//m_serverWorker->updateCoils(14, true);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, p, i, d] { m_clientWorker->set_PID2(p, i, d); },
		Qt::QueuedConnection
	);
}
void Manager::set_AO1(double v)
{
	quint16 modbusValue = v;
	qDebug() << "set Out Open SV"<<modbusValue;
	m_serverWorker->updateHoldingRegister(50, modbusValue);
	QMetaObject::invokeMethod(
		m_clientWorker, [this, modbusValue] { m_clientWorker->set_AO1(modbusValue); },
		Qt::QueuedConnection
	);
}
void Manager::motorFrequency(double v)
{
	double value = v * 40.95/0.6;

	if(_motor_STO)
	{
		m_serverWorker->updateHoldingRegister(31, 0);
		qDebug() << "set motorFrequency =" << value<< " BUT! STO ON set 0" ;
	}
	m_serverWorker->updateHoldingRegister(31,value);
}
void Manager::fan1TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if(_FAN_STOP)
	{
		qDebug() << "set fan1 but E_STOP ON";
		m_serverWorker->updateHoldingRegisters(32, { 0 });
	}
	else {
		m_serverWorker->updateHoldingRegisters(32, data);
	}
}
void Manager::fan2TargetRpm(double v)
{
	double value = v * 40.95;
	qDebug() << v;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(33, { 0 });
		qDebug() << "set fan2 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(33, data);
	}
}
void Manager::fan3TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(34 ,{ 0 });
		qDebug() << "set fan3 but E_STOP ON";
	}
	else {
		m_serverWorker->updateHoldingRegisters(34, data);
	}
}
void Manager::fan4TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(39, { 0 });
		qDebug() << "set fan4 but E_STOP ON";
	}
	else {
		m_serverWorker->updateHoldingRegisters(39, data);
	}
}
void Manager::fan5TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(40, { 0 });
		qDebug() << "set fan5 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(40, data);
	}
}
void Manager::fan6TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(41, { 0 });
		qDebug() << "set fan6 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(41, data);
	}
}
void Manager::fan7TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(42, { 0 });
		qDebug() << "set fan7 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(42, data);
	}
}
void Manager::fan8TargetRpm(double v) 
{
	double value = v * 40.95;

	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP){
		m_serverWorker->updateHoldingRegisters(47 ,{ 0 });
		qDebug() << "set fan8 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(47, data);
	}
}
void Manager::fan9TargetRpm(double v) 
{
	double value = v * 40.95;
	QVector<quint16> data;
	data.resize(1);
	data[0] = value;
	if (_FAN_STOP)
	{
		m_serverWorker->updateHoldingRegisters(48, { 0 });
		qDebug() << "set fan9 but E_STOP ON";

	}
	else {
		m_serverWorker->updateHoldingRegisters(48, data);
	}
}
void Manager::returnValveOpening(double v) 
{
	quint16 modbusValue = v;
	qDebug() << "set Mix Open SV" << modbusValue;

	QVector<quint16> data;
	data.resize(1);
	data[0] = modbusValue;
	m_serverWorker->updateHoldingRegisters(49, data);
}

void Manager::WriteHoldingRegister_204(int addr, double value)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, addr, value] { m_clientWorker->set_204HoldingRegister(addr, value); },
		Qt::QueuedConnection
	);
}
void Manager::WriteHoldingRegister_205(int addr, double value)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, addr, value] { m_clientWorker->set_205HoldingRegister(addr, value); },
		Qt::QueuedConnection
	);
}
void Manager::WriteHoldingRegister_206(int addr, double value)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, addr, value] { m_clientWorker->set_206HoldingRegister(addr, value); },
		Qt::QueuedConnection
	);
}
void Manager::WriteHoldingRegister_6022(int addr, double value)
{
	QMetaObject::invokeMethod(
		m_clientWorker, [this, addr, value] { m_clientWorker->set_6022HoldingRegister(addr, value); },
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
void Manager::set_motorEstop(bool v)
{
	_motor_STO = v;
	qDebug() << "set motor E-stop: " << v;
	QMetaObject::invokeMethod(
		m_clientWorker, [this, v] { m_clientWorker->set_STO(v); },
		Qt::QueuedConnection
	);
}
void Manager::set_FanEstop(bool v)
{
	_FAN_STOP = v;
	qDebug() << "set FAN E-stop: " << v;
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
}
void Manager::set_motor(bool v)
{//水泵STO
	_motor_STO = v;
	quint16 value = v ? 1 : 0;
	m_serverWorker->updateHoldingRegister(72, value);
	qDebug() << "set motor ";
}
void Manager::set_FanPower(bool v)
{
	_FAN_STOP = v;
	if (_FAN_STOP) {
		set_allFan(0);
	}
	quint16 value = v ? 1 : 0;	//緊急停止開啟 = 馬達電源關閉
	m_serverWorker->updateHoldingRegister(71, value);
	qDebug() << "set fan E_STOP " <<_FAN_STOP;
}