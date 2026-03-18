CREATE TABLE IF NOT EXISTS sensor_data (
    timestamp INTEGER NOT NULL,
    s1 REAL,
    s2 REAL,
    s3 REAL,
    s4 REAL,
    s5 REAL,
    s6 REAL,
    s7 REAL,
    s8 REAL,
    s9 REAL,
    s10 REAL,
    s11 REAL,
    s12 REAL,
    s13 REAL,
    s14 REAL,
    s15 REAL,
    s16 REAL,
    s17 REAL,
    s18 REAL,
    s19 REAL,
    s20 REAL
);

CREATE INDEX IF NOT EXISTS idx_sensor_data_ts ON sensor_data(timestamp);
