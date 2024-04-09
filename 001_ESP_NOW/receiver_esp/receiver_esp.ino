#include <esp_now.h>
#include "WiFi.h"

typedef struct struct_message
{
	char message[32];
	int b;
	float c;
	bool d;
} message_packet;

message_packet myData;
void onDataRecv(const uint8_t *macAddress, const uint8_t *incomingData, int len)
{
	memcpy(&myData, incomingData, sizeof(myData));
	Serial.print("Bytes received: ");
 	Serial.println(len);
	Serial.print("Char: ");
	Serial.println(myData.message);
	Serial.print("Int: ");
	Serial.println(myData.b);
	Serial.print("Float: ");
	Serial.println(myData.c);
	Serial.print("Bool: ");
  	Serial.println(myData.d);
	Serial.println();
}

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);

	if (esp_now_init() != ESP_OK)
	{
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	esp_now_register_recv_cb(onDataRecv);
}

void loop()
{

}
