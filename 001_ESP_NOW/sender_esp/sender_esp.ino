#include <esp_now.h>
#include "WiFi.h"

typedef struct struct_message
{
	char message[32];
	int b;
	float c;
	bool d;
}msg_packet;

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
msg_packet packet;
esp_now_peer_info_t peerInfo;

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Sent Successfully" : "Failure Occured");
}

void setup()
{
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	if (esp_now_init() != ESP_OK)
	{
		Serial.println("Failed to Initialize ESP");
		return;
	}

	esp_now_register_send_cb(onDataSent);
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;

	if (esp_now_add_peer(&peerInfo) != ESP_OK)
	{
		Serial.println("Failed to add peer");
		return;
	}
}

void loop()
{
	strcpy(packet.message, "Hello There.....I am alive buddy!!");
	packet.b = random(1, 20);
	packet.c = 1.2;
	packet.d = false;

	esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &packet, sizeof(packet));

	if (result == ESP_OK)
		Serial.println("Sent with Successs!!");
	else
		Serial.println("Error occured while attempting to send the data");
	delay(2000);
}
