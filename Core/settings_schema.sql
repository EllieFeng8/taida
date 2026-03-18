CREATE TABLE IF NOT EXISTS sensor_config (
    sensor_key TEXT PRIMARY KEY,
    sensor_name TEXT
);

CREATE TABLE IF NOT EXISTS app_settings (
    key TEXT PRIMARY KEY,
    value TEXT
);

INSERT OR IGNORE INTO app_settings (key, value) VALUES ('read_frequency', '1000');
