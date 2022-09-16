/*

*/
#include "htu2x_sensor.h"

//************************************************************************
//Constructor: Wire Lib öffnen

HTU2X::HTU2X() {
}

void HTU2X::begin() {
    Wire.begin();
    delay(20);
    reset();
    delay(50);
    setResolution(1);
}

void HTU2X::reset() {
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_RESET);
    Wire.endTransmission();
    delay(15);
}

void HTU2X::startSingleMeasure() {
    uint8_t dummy;
    haveTemp = false;
    /* Measure temperature */
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_MEASUR_TEMP);
    Wire.endTransmission(true);
    delay(tempDelayTime);
    Wire.requestFrom((uint8_t)HTU2X_I2C_ADDR, (uint8_t)3);
    temp_raw = 0;
    temp_raw = (Wire.read() << 8);
    temp_raw |= Wire.read();
    dummy = Wire.read();
    /* Measure humidity */
    Wire.beginTransmission(HTU2X_I2C_ADDR);
    Wire.write(HTU2X_MEASUR_HUMI);
    Wire.endTransmission(true);
    delay(humiDelayTime);
    Wire.requestFrom((uint8_t)HTU2X_I2C_ADDR, (uint8_t)3);
    humi_raw = 0;
    humi_raw = (Wire.read() << 8);
    humi_raw |= Wire.read();
    dummy = Wire.read();
}

float HTU2X::getTemperature(void) {
    temp = -46.85 + (175.72 * (float)temp_raw / 65535.0);
    haveTemp = true;
    return temp;
}

float HTU2X::getHumidity(void) {
    if ( ! haveTemp ) getTemperature();
    humi = -6.0 + (125.0 * (float)humi_raw / 65535.0);
    if ( temp > 0.0 ) humi += HTU2X_TEMPCOEFF * (25.0 - temp);
    humi = constrain(humi, 0, 100);
    return humi;
}

void HTU2X::setResolution(uint8_t resolution) {
    userReg = getStatusReg();
    switch(resolution) {
        case 1:  {
            userReg |= HTU2X_RESOLUTION1;
            tempDelayTime = HTU2X_MEASUR_TEMP_DELAY1;
            humiDelayTime = HTU2X_MEASUR_HUMI_DELAY1;
        }
        case 2:  {
            userReg |= HTU2X_RESOLUTION2;
            tempDelayTime = HTU2X_MEASUR_TEMP_DELAY2;
            humiDelayTime = HTU2X_MEASUR_HUMI_DELAY2;
        }
        case 3:  {
            userReg |= HTU2X_RESOLUTION3;
            tempDelayTime = HTU2X_MEASUR_TEMP_DELAY3;
            humiDelayTime = HTU2X_MEASUR_HUMI_DELAY3;
        }
        case 4:  {
            userReg |= HTU2X_RESOLUTION4;
            tempDelayTime = HTU2X_MEASUR_TEMP_DELAY4;
            humiDelayTime = HTU2X_MEASUR_HUMI_DELAY4;
        }
    }
    setStatusReg(userReg);
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
