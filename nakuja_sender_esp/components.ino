/**
 * broadCast - BroadCasts packets to the other peers.
 * @message: the message to be broadcasted to the other peers.
 */
void broadCast(const char *message)
{
        uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        esp_now_peer_info_t peerInfo = {};
        memcpy(&peerInfo.peer_addr, broadcastAddress, 6);

        if (!esp_now_is_peer_exist(broadcastAddress))
              esp_now_add_peer(&peerInfo);

         esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message, strlen(message));

         switch (result) {
                case ESP_OK:
                        Serial.println("Message Broadcasted Successfully");
                        break;
                case ESP_ERR_ESPNOW_NOT_INIT:
                        Serial.println("ESP-NOW not Init.");
                        break;
                case  ESP_ERR_ESPNOW_ARG:
                        Serial.println("Invalid Argument");
                        break;
                case ESP_ERR_ESPNOW_INTERNAL:
                      Serial.println("Internal Error");
                      break;
                case ESP_ERR_ESPNOW_NOT_FOUND:
                      Serial.println("Peer not found");
                      break;
                default:
                      Serial.println("Error occured during Sending");
                      break;
          }
          
          
  }

/**
 * Buzzer - turns buzzer on to produce Siren sound.
 * @pin: pin connecting Piezzo.
 * @command: either on or off.
 */

void Buzzer(const int *pin, char *command)
{
      int i;
      
      if (strcmp(command, "turn-on") == 0)
      {
            for (i = 100 ; i < 1000; i += 100)
            {  
                   tone(*pin, i);  
                  delay(50);   
            }

            for (i = 1000; i > 100; i -= 100)
            {
                  tone(*pin, i);
                  delay(50);
            }
            
      }
      else
      {
             noTone(*pin);
      }
 }


 void greet()
 {
  Serial.println("Hey there");
  }
