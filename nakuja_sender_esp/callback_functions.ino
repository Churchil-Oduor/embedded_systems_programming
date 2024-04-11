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
void onDataSent(const uint8_t *mac_address, esp_now_send_status_t status)
{}


/**
 * onReceiveData - gets called upon receiving data from the peer esp we are connected to
 * 
 * @mac_address: MAC address of the peer from sending this data.
 * @incomingData: pointer to the actual received data.
 * @len: length of actual received data.
 */
void onReceiveData(const uint8_t *mac_ddress, const uint8_t *incomingData, int len)
{}
