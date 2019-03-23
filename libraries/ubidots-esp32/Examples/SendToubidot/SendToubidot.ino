#include "WiFi.h"
#include "UbidotsMicroESP32.h"

#define TOKEN  "Your_token_here"  // Put here your Ubidots TOKEN
#define WIFISSID "Your_WiFi_SSID" // Put here your Wi-Fi SSID
#define PASSWORD "Your_WiFi_Password" // Put here your Wi-Fi password



// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


Ubidots client(TOKEN);


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize serial communication:
  Serial.begin(115200);
  delay(10);
  client.wifiConnection(WIFISSID, PASSWORD);
  client.setDataSourceName("Demo");
  client.setDataSourceLabel("demo");
 // client.sendAll(true);
}

void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
      client.add("Box1",buttonPushCounter++);
      client.sendAll(true);
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;

}
