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
```
inside loop() do the following steps:
```
  // Tell the sensor to collect the measurements
  htu2x.startSingleMeasure();
  // Make sure to wait at least 10 milliseconds
  delay(100);
  // Use the results as needed
  Serial.print("Temperature: ");
  Serial.print(htu2x.getTemperature());
  Serial.print(" C        HUmidity: ");
  Serial.print(htu2x.getHumidity());
  Serial.println(" RH");
```
State of this library: Testing!

