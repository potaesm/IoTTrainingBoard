#include "WiFi.h"
#include "UbidotsMicroESP32.h"
#include <Wire.h>
#include <Arduino.h>
#include <HTS221.h>

#define TOKEN  "Your_token_here"  // Put here your Ubidots TOKEN
#define WIFISSID "Your_WiFi_SSID" // Put here your Wi-Fi SSID
#define PASSWORD "Your_WiFi_Password" // Put here your Wi-Fi password
#define TOKEN  "BuRrbasruDn81HMN7TaefSa7H9SAWt"  // Put here your Ubidots TOKEN
double Humidity=0;
double Temperature=0;
Ubidots client(TOKEN);
void setup() {
  //Initiate the Wire library and join the I2C bus
  Wire.begin((int) 4 , (int) 5);
  pinMode(2, OUTPUT);
  smeHumidity.begin();
  Serial.begin(115200);
  delay(100);
  client.wifiConnection(WIFISSID, PASSWORD);
  client.setDataSourceName("My test");
  client.setDataSourceLabel("my-test");
  
  
}

// the loop function runs over and over again forever
void loop() {
  
  Humidity = smeHumidity.readHumidity();
  Serial.print("Humidity   : ");
  Serial.print(Humidity);
  Serial.println(" %");

  Temperature = smeHumidity.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.println(" celsius");
  
  client.add("Humidity",Humidity);
  client.add("Temperature",Temperature);
  client.sendAll(true);
   
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  delay(500);              // wait for a second

}

