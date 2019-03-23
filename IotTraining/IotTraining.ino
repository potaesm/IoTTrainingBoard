
#include "TenTrackIoT.h"
TenTrackIoT LED5, LED1, LED2, LED3, SW1, SW2, SW3, LDR, HT, RFID, MPU, GPS;

bool state1 = 0;
bool state2 = 0;
bool state3 = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {

  LED5.Blink(32, 500);

  if (SW1.IsPressed(15)) {
    state1 = LED1.Toggle();
    if (state1) {
      LED1.On(13);
    } else {
      LED1.Off(13);
    }
  }
  
  if (SW2.IsPressed(2)) {
    state2 = LED2.Toggle();
    if (state2) {
      LED2.On(12);
    } else {
      LED2.Off(12);
    }
  }
  
  if (SW3.IsPressed(4)) {
    state3 = LED3.Toggle();
    if (state3) {
      LED3.On(14);
    } else {
      LED3.Off(14);
    }
  }

  if (state1) {
    Serial.print("LDR : ");
    Serial.println(LDR.ReadLDR(0));
    //Serial.println(RFID.ReadRFID());
  }
  if (state2) {
    Serial.print("Temperature & Humidity : ");
    Serial.print(HT.ReadTemperature(27));
    Serial.print(", ");
    Serial.println(HT.ReadHumidity(27));
    //Serial.println(GPS.ReadLatitude(), 6);
  }
  
  if (state3) {
    if (MPU.IsMoved()) {
      Serial.println("Moved!");
    }
    
  }
}
