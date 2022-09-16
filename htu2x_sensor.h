/*
A Arduino library for the AHT20 sensor

I made this library for my nodes. It has only fixed settings.
The settings can be changed in the header  file (this file)
*/
#ifndef __HTU2X_SENSOR_H__
#define __HTU2X_SENSOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Wire.h>

#define HTU2X_I2C_ADDR                          0x40
#define HTU2X_RESET                                0xFE
#define HTU2X_MEASUR_TEMP                   0xF3
#define HTU2X_MEASUR_HUMI                   0xF5
#define HTU2X_WRITE_USER_REG              0xE6
#define HTU2X_READ_USER_REG               0xE7
// Resolution: Humidity 11bit; Temperature 11bit; Delaytime (T=7ms H=8ms) => 20ms is safe for both
#define HTU2X_RESOLUTION1                     0b10000001
#define HTU2X_MEASUR_TEMP_DELAY1       10
#define HTU2X_MEASUR_HUMI_DELAY1       10
// Resolution: Humidity 8bit; Temperature 12bit; Delaytime (T=13ms H=3ms) => 20ms is safe for both
#define HTU2X_RESOLUTION2                     0b00000001
#define HTU2X_MEASUR_TEMP_DELAY2       15
#define HTU2X_MEASUR_HUMI_DELAY2       5
// Resolution: Humidity 10bit; Temperature 13bit; Delaytime (T=25ms H=5ms) => 30ms is safe for both
#define HTU2X_RESOLUTION3                     0b10000000
#define HTU2X_MEASUR_TEMP_DELAY3       25
#define HTU2X_MEASUR_HUMI_DELAY3       5
// Resolution: Humidity 12bit; Temperature 14bit; Delaytime (T=50ms H=16ms) => 70ms is safe for both
#define HTU2X_RESOLUTION4                     0b00000000
#define HTU2X_MEASUR_TEMP_DELAY4       50
#define HTU2X_MEASUR_HUMI_DELAY4       20

#define HTU2X_TEMPCOEFF                        -0.15


class HTU2X{
public:

    HTU2X();
    void begin(void);
    void startSingleMeasure(void);
    float getTemperature(void);
    float getHumidity(void);
    void setResolution(uint8_t);

protected:

private:

    void reset(void);
    uint8_t getStatusReg(void);
    void setStatusReg(uint8_t);

    uint8_t userReg;
    float humi;
    uint16_t humi_raw;
    float temp;
    uint16_t temp_raw;
    bool haveRawData;
    bool haveTemp;
    int tempDelayTime;
    int humiDelayTime;
};





#endif
