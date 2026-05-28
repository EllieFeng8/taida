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
('s1', 'inletWaterTemp'),
('s2', 'inletWaterPressure'),
('s3', 'returnWaterTemp'),
('s4', 'returnWaterPressure'),
('s5', 'outletWaterTemp'),
('s6', 'outletWaterPressure'),
('s7', 'coolingL1'),
('s8', 'coolingL2'),
('s9', 'coolingR1'),
('s10', 'coolingR2'),
('s11', 'inletAirTemp'),
('s12', 'inletAirHumidity'),
('s13', 'flowRate'),
('s14', 'outletWaterPV'),
('s15', 'returnWaterPV'),
('s16', 'fanAutoSpeed'),
('s17', 'outletAirTemp'),
('s18', 'pressureDifference'),
('s19', 'TBD'),
('s20', 'heatExchange');
