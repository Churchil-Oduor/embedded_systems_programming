/*
  NAKUJA PROJECT
  MAIN INTIATOR
  - Transmits load cell calibrated readings
  - Ignition of motor
*/

#include <WiFi.h>
#include <esp_now.h>
#include "HX711.h"
#define DOUT_PIN 13 //The HX711 DAT connected to GPIO 21
#define CLK_PIN 32 //The HX711 CLK connected to GPIO 22


HX711 scale;

void setup() {
  
    Serial.begin(115200);
    scale.begin(DOUT_PIN, CLK_PIN);
    unsigned long t_ = 0;
    
}

void loop() {
        if (scale.is_ready())
        {
                long reading = scale.read();
                float force = (map(reading, 0, 4096, 0, 800) - 9225) / 100;
                Serial.println("Weight: " + String(force));
          }
          else
          {
                Serial.println("HX711 not ready");
            }

           delay(1000);

}
