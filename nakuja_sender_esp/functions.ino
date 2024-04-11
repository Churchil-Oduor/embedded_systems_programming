/**
 * This files contains the various functions defined by us.
 */

 /**
  * onDataSent - gets called when data is transmitted. 
  * 
  * @mac_address: Pointer to MAC address of the peer the
  * data was sent to.
  * @status: indicates the status of the sending operation.
  */
void sentDataCallBack(const uint8_t *mac_address, esp_now_send_status_t status)
{
        
}


/**
 * onReceiveData - gets called upon receiving data from the peer esp we are connected to
 * The function prints the time of data reception and the data received.
 * @mac_address: MAC address of the peer from sending this data.
 * @incomingData: pointer to the actual received data.
 * @len: length of actual received data.
 */
void receivedDataCallBack(const uint8_t *mac_ddress, const uint8_t *incomingData, int dataLen)
{
      int msgLen;
      char buffer[ESP_NOW_MAX_DATA_LEN + 1];

      msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
      strncpy(buffer, (const char*)incomingData, msgLen);
      buffer[msgLen] = '\0';

      Serial.print(millis());
      Serial.print(", ");
      Serial.println(buffer);
}

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
