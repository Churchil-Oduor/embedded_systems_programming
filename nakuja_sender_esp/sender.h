#ifndef SENDER_H
#define SENDER_H

/**
 * msg_packet - struct holding the message and contents that are transmitted as a packet
 * 
 * @message: message to be transmitted.
 * 
 * Description: The packet structure is an encapsulation(i.e a wrapper holding information) that 
 * holds info that is transmitted to the receiveing ESP. The receiveing ESP will open this packet to view
 * the details.
 */
typedef struct struct_packet
{
  char message[100];
}msg_packet;

void sentDataCallBack(const uint8_t *mac_address, esp_now_send_status_t status);
void receivedDataCallBack(const uint8_t *mac_ddress, const uint8_t *incomingData, int dataLen);
void Buzzer(const int *pin, char *command);
void broadCast(const char *message);

#endif  /*SENDER_H*/
