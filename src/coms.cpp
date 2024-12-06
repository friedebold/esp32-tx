#include <Arduino.h>
#include <coms.h>
#include <main.h>

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xA0, 0xA3, 0xB3, 0xAA, 0x6C, 0xA8};

esp_now_peer_info_t peerInfo;

struct SendData
{
    Remote remote_data;
    PID pid_data;
};

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&incoming, incomingData, sizeof(incoming));
}

void setup_wifi()
{
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
    // Register peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
};

void send_data(PID pid_data)
{
    SendData send_data = {remote_data, pid_data};
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&send_data, sizeof(send_data));
};