#include <Arduino.h>
#include <coms.h>
#include <main.h>

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xE4, 0x65, 0xB8, 0x12, 0x9C, 0x2C};
esp_now_peer_info_t peerInfo;

void setup_wifi()
{
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
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

struct SendData
{
    Remote remote_data;
    PID pid_data;
};

void send_data(PID pid_data)

{
    SendData send_data = {remote_data, pid_data};
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&send_data, sizeof(send_data));
    if (result == ESP_OK)
    {
        // Serial.println("✅ Sent success");
    }
    else
    {
        //  Serial.println("❌ Sent failed");
    }
};