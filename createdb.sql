DROP DATABASE netlib;
DROP ROLE netlibuser;

CREATE DATABASE netlib;
CREATE USER netlibuser WITH password '123';
GRANT ALL privileges ON DATABASE netlib TO netlibuser;
