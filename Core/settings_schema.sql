CREATE TABLE IF NOT EXISTS sensor_config (
    sensor_key TEXT PRIMARY KEY,
    sensor_name TEXT
);

CREATE TABLE IF NOT EXISTS app_settings (
    key TEXT PRIMARY KEY,
    value TEXT
);

INSERT OR IGNORE INTO app_settings (key, value) VALUES ('read_frequency', '1000');

INSERT OR IGNORE INTO sensor_config (sensor_key, sensor_name) VALUES
('s1', 'InletWaterTemp'),
('s2', 'InletWaterPressure'),
('s3', 'OutletWaterTemp'),
('s4', 'OutletWaterPressure'),
('s5', 'InletPumpTemp'),
('s6', 'InletPumpPressure'),
('s7', 'InletLeftCoilTemp'),
('s8', 'OutletLeftCoilTemp'),
('s9', 'InletRightCoilTemp'),
('s10', 'OutletRightCoilTemp'),
('s11', 'InletAirTemp'),
('s12', 'InletAirHumidity'),
('s13', 'FlowRate'),
('s14', 'OutletWaterSV'),
('s15', 'OutletWaterPV'),
('s16', 'MixWaterSV'),
('s17', 'MixWaterPV'),
('s18', 'FanSV'),
('s19', 'FanPV'),
('s20', 'OutletAirTemp'),
('s21', 'DifferentialPressureSV'),
('s22', 'DifferentialPressurePV'),
('s23', 'HeatLoad'),
('s24', 'AutoFanControl'),
('s25', 'AutoTempControl'),
('s26', 'PumpSV'),
('s27', 'PumpPV');
