/**
 * NAKUJA PROJECT
 * SENDER CODE
 * Sends signal to receiver to ignite the Motor and
 * receives the transmitted data the peer esp collecting the loadcell data.
 */
 
#include <WiFi.h>
#include <esp_now.h>
#include "sender.h"
#define STATUS_BUTTON 14 // gpio14 pin connceted to button.



esp_now_peer_info_t peerInfo;
const int BUZZER_PIN = 18;

/** button configurations **/
int btn_IsPressed = HIGH;

void setup()
{
      /** Pushbutton uses inbuilt pullup resistor**/
      pinMode(STATUS_BUTTON, INPUT_PULLUP);
      pinMode(BUZZER_PIN, OUTPUT);

      
      Serial.begin(115200);
      WiFi.mode(WIFI_STA);
  
       if (esp_now_init() != ESP_OK)
      {
          Serial.println("Error occurred during initializing ESP");
          return;
      }
      
      esp_now_register_recv_cb(receivedDataCallBack);
      esp_now_register_send_cb(sentDataCallBack);

     peerblock:
     if (esp_now_add_peer(&peerInfo) != ESP_OK)
     {
         Serial.println("Error...Failed to Add Peer");
         delay(2000);
         Serial.println("Restarting ESP-NOW protocol.....");
         ESP.restart();
         goto peerblock; /**calling peerblock to recheck if peering was successful**/
     }
   
}

void loop()
{
  
        btn_IsPressed = !digitalRead(STATUS_BUTTON);
        if (btn_IsPressed)
            broadCast("on");
}
