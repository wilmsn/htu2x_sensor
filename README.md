# htu2x_sensor
Arduino and ESP library for the HTU2X temprature and humidity sensor 

I needed a library that works like this:

1)  Trigger the sensor to measure

2)  Get your results

3)  Let the sensor sleep and use minimal power only


The library works with fixed settings only. They are changable in the header file.

So the use of this library is as easy as:

Include this library and open an Instanz of this:
```
#include <htu2x_sensor.h>

HTU2X htu2x;
 
```
inside "setup" call the begin function:
```
  htu2x.begin();
  // Optional: Set Resolution of Sensor
  // Resolution: 
  // 1 => Humidity 11bit; Temperature 11bit; Delaytime (T=7ms H=8ms) => 20ms is safe for both
  // 2 => Humidity 8bit; Temperature 12bit; Delaytime (T=13ms H=3ms) => 20ms is safe for both
  // 3 => Humidity 10bit; Temperature 13bit; Delaytime (T=25ms H=5ms) => 30ms is safe for both
  // 4 => Humidity 12bit; Temperature 14bit; Delaytime (T=50ms H=16ms) => 70ms is safe for both
  htu2x.setResolution(1);  // 1 is default, no need to set it!

```
inside loop() do the following steps:
```
  // Tell the sensor to collect the measurements
  htu2x.startSingleMeasure();
  // Use the results as needed
  Serial.print("Temperature: ");
  Serial.print(htu2x.getTemperature());
  Serial.print(" C        HUmidity: ");
  Serial.print(htu2x.getHumidity());
  Serial.println(" RH");
```
State of this library: Testing!

