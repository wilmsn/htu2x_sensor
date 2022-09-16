#include <htu2x_sensor.h>

HTU2X htu2x;

void setup() {
  Serial.begin(115200);
  Serial.println("HTU2X Sensor Demo");
  htu2x.begin();
  // Optional: Set Resolution of Sensor
  // Resolution: 
  // 1 => Humidity 11bit; Temperature 11bit; Delaytime (T=7ms H=8ms) => 20ms is safe for both
  // 2 => Humidity 8bit; Temperature 12bit; Delaytime (T=13ms H=3ms) => 20ms is safe for both
  // 3 => Humidity 10bit; Temperature 13bit; Delaytime (T=25ms H=5ms) => 30ms is safe for both
  // 4 => Humidity 12bit; Temperature 14bit; Delaytime (T=50ms H=16ms) => 70ms is safe for both
  htu2x.setResolution(1);  // 1 is default, no need to set it!
}

void loop() {
  htu2x.startSingleMeasure();
  delay(100);
  Serial.print(" Temperature: ");
  Serial.print(htu2x.getTemperature());
  Serial.print(" C        Humidity: ");
  Serial.print(htu2x.getHumidity());
  Serial.println(" RH");
  delay(2000);
}
