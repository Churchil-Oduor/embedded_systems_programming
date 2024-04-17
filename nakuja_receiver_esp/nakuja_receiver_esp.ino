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
    WiFi.mode(WIFI_STA);
    scale.begin(DOUT_PIN, CLK_PIN); 

    while (esp_now_init() != ESP_OK)
    {
         Serial.println("Error during ESP_NOW Initialization...");
         delay(1000);
         Serial.println("Attempting to Restart and Initialize...");
         ESP.restart();
    }

    esp_now_register_recv_cb(receivedDataCallBack);
    esp_now_register_send_cb(sentDataCallBack);
  
}


void loop() 
{
    float lcell_readings;
    int time_interval_to_return_data; // in millis
    char float_to_str_buffer[32];

    time_interval_to_return_data = 1000;
    lcell_readings = getLoadCellData(scale);
    Serial.println("Weight Applied: " + String(lcell_readings) + " N");
    //convert lcell_readings of type float into const *char type to be passed into broadcast type.
    snprintf(float_to_str_buffer, sizeof(float_to_str_buffer), "%f", lcell_readings);
    broadCast(float_to_str_buffer);
    delay(time_interval_to_return_data);
    
}

