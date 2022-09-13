/*

*/
#include "htu2x_sensor.h"

//************************************************************************
//Constructor: Wire Lib öffnen

HTU2X::HTU2X() {
    Wire.begin();
    delay(20);
    reset();
}

void HTU2X::begin() {
    userReg = getStatusReg();
    userReg |= HTU2X_RESOLUTION;
    setStatusReg(userReg);
}

void HTU2X::reset() {
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_RESET);
    Wire.endTransmission();
    delay(15);
}

void HTU2X::startSingleMeasure() {
    uint8_t dummy;
    /* Measure temperature */
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_MEASUR_TEMP);
    Wire.endTransmission(true);
    delay(HTU2X_MEASUR_TEMP_DELAY);
    Wire.requestFrom((uint8_t)HTU2X_I2C_ADDR, (uint8_t)3);
    temp_raw = 0;
    temp_raw = (Wire.read() << 8);
    temp_raw |= Wire.read();
    dummy = Wire.read();
    temp = -46.85 + (175.72 * (float)temp_raw / 65535.0);
    /* Measure humidity */
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_MEASUR_HUMI);
    Wire.endTransmission(true);
    delay(HTU2X_MEASUR_HUMI_DELAY);
    Wire.requestFrom((uint8_t)HTU2X_I2C_ADDR, (uint8_t)3);
    humi_raw = 0;
    humi_raw = (Wire.read() << 8);
    humi_raw |= Wire.read();
    dummy = Wire.read();
    humi = -6.0 + (125.0 * (float)humi_raw / 65535.0);
    if ( temp > 0.0 ) humi += HTU2X_TEMPCOEFF * (25.0 - temp);
    humi = constrain(humi, 0, 100);
}

float HTU2X::getTemperature(void) {
    return temp;
}

float HTU2X::getHumidity(void) {
    return humi;
}

uint8_t HTU2X::getStatusReg() {
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_READ_USER_REG);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)HTU2X_I2C_ADDR, (uint8_t)1);
    return (uint8_t)Wire.read();
}

void HTU2X::setStatusReg(uint8_t reg) {
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_WRITE_USER_REG);
    Wire.write(reg);
    Wire.endTransmission();
}
