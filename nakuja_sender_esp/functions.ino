/**
 * This files contains the various functions defined by us.
 */

/**
  * sentDataCallBack - gets called when data is transmitted. 
  * 
  * @macAaddress: Pointer to MAC address of the peer the
  * data was sent to.
  * @status: indicates the status of the sending operation.
  */
void sentDataCallBack(const uint8_t *macAddress, esp_now_send_status_t status)
{
    if (status == ESP_NOW_SEND_SUCCESS)
        Serial.println("Last Packet Sent to MAC-Address")
}


/**
 * receivedDataCallBack- gets called upon receiving data from the peer esp we are connected to
 * The function prints the time of data reception and the data received.
 * @mac_address: MAC address of the peer from sending this data.
 * @incomingData: pointer to the actual received data.
 * @dataLen: length of actual received data.
 */
void receivedDataCallBack(const uint8_t *mac_ddress, const uint8_t *incomingData, int dataLen)
{
  int msgLen;
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];

  msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
  strncpy(buffer, (const char *)incomingData, msgLen);
  buffer[msgLen] = '\0';

  Serial.print(millis());
  Serial.print(", ");
  Serial.println(buffer);
}

/**
 * broadCast - BroadCasts packets to the other peers and returns response
 * on the Serial output on the status of the sent packet either sent successfully
 * or an error occured during transmission.
 * @message: the message to be broadcasted to the other peers.
 */
void broadCast(const char *message)
{
  uint8_t broadcastAddress[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
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
    case ESP_ERR_ESPNOW_ARG:
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
