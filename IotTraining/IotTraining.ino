
#include "TenTrackIoT.h"
TenTrackIoT LED, SWITCH, LDR, HT, RFID, MPU, GPS;

bool state = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {

  LED.Blink(32, 500);
  // HT.InitDHT(2);

  if (SWITCH.IsPressed(33)) {
    state = LED.Toggle();
    if (state) {
      LED.On(25);
    } else {
      LED.Off(25);
    }
  }

  if (state) {
//    Serial.print("LDR Read : ");
//    Serial.println(LDR.ReadLDR(26));
//
//    Serial.print("Temperature Read : ");
//    Serial.println(HT.ReadTemperature());
//
//    Serial.print("Humidity Read : ");
//    Serial.println(HT.ReadHumidity());
//
//    Serial.println(RFID.ReadRFID());
//    if (MPU.IsMoved()) {
//      Serial.println("Moved!");
//    }
//    Serial.println(GPS.ReadLatitude(), 6);
  }

}
