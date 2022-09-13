#include <htu2x_sensor.h>

HTU2X htu2x;

void setup() {
  Serial.begin(115200);
  Serial.println("HTU2X examples");
  htu2x.begin();
}

void loop() {
  htu2x.startSingleMeasure();
  delay(100);
  Serial.print(" Temperature: ");
  Serial.print(htu2x.getTemperature());
  Serial.print(" C        HUmidity: ");
  Serial.print(htu2x.getHumidity());
  Serial.println(" RH");
  delay(1000);
}
