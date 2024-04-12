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

void setup()
{
    Serial.begin(115200);
    scale.begin(DOUT_PIN, CLK_PIN); 
}

void loop() 
{
    float lcell_readings;
    lcell_readings = getLoadCellData(scale);
    Serial.print("Weight Applied: " + String(lcell_readings) + " N");
}

