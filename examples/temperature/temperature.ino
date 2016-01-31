#include <Wire.h>
#include "fabo-adt7410.h"

#define DEVICE_ADDR (0x48)

void setup() {
  Serial.begin(9600);
  
  faboTemperature.searchDevice(); 
  faboTemperature.configure();
}

void loop() {

  float temp = faboTemperature.readTemperature(); 

  Serial.print("Temperarue: ");
  Serial.println(temp);
  delay(1000);
}
