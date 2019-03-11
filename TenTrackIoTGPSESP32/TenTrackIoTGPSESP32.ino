#include "WiFi.h"
#include "UbidotsMicroESP32.h"
#include <Wire.h>
#include <Arduino.h>
#include "TenTrackIoT.h"

#define TOKEN  "A1E-dstwbgPaMMxcc53WdWtu1g7aOZfwng"  // Put here your Ubidots TOKEN
#define WIFISSID "boom" // Put here your Wi-Fi SSID
#define PASSWORD "123456789" // Put here your Wi-Fi password

Ubidots client(TOKEN);
TenTrackIoT GPS, LED;

void setup() {
  Serial.begin(115200);
  client.wifiConnection(WIFISSID, PASSWORD);
  client.setDataSourceName("My test"); // ชื่อ Device
  client.setDataSourceLabel("my-test"); // ชื่อ variable ใน Device
}

void loop() {
  LED.Blink(4, 1000);
  if (GPS.ReadLatitude() != 0.000000 && GPS.ReadLongitude() != 0.000000) {
    client.add("Latitude", GPS.ReadLatitude());
    client.add("Longitude", GPS.ReadLongitude());
    client.sendAll(true);
  }
}
