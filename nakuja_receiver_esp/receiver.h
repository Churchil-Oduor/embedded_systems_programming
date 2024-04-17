#ifndef RECEIVER_H
#define RECEIVER_H

float getLoadCellData(HX711 &scale);
void receivedDataCallBack(const uint8_t *mac_ddress, const uint8_t *incomingData, int dataLen);
void sentDataCallBack(const uint8_t *macAddress, esp_now_send_status_t status);
void broadCast(const char *message);
#endif /* RECEIVER_H*/