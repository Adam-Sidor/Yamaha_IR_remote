#include "PinDefinitionsAndMore.h"  // Set IR_SEND_PIN for different CPU's
//#include "TinyIRSender.hpp"       //use when u use IR diode
#include "TinyIRSenderReverse.hpp"  //use when u direct connect EPS to reciver in Yamaha
#include <BluetoothSerial.h>

// Serial
bool stringComplete = false;
String inputString = "";

// BT
String deviceName = "YamahaController";
BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin(deviceName);
  Serial.begin(115200);
  Serial.print("Send IR signals at pin: ");
  Serial.println(IR_SEND_PIN);
  inputString.reserve(200);
  pinMode(IR_SEND_PIN, OUTPUT);
  digitalWrite(IR_SEND_PIN,HIGH);//comment this line if u are using IR diode
}

void loop() {
  serialBTEvent();
  if (stringComplete) {
    if (catchSerial("PowerSwitch"))
      sendONKYO(IR_SEND_PIN, 0x817E, 0xD52A, 0);
    if (catchSerial("InputUp"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x601F, 0);
    if (catchSerial("InputDown"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x5C23, 0);
    if (catchSerial("Mute"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xE31C, 0);
    if (catchSerial("VolumeUp"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xE51A, 0);
    if (catchSerial("VolumeDown"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xE41B, 0);
    inputString = "";
    stringComplete = false;
  }
}

bool catchSerial(String text) {
  int where = inputString.indexOf(text);
  if (where != -1) {
    return true;
  } else {
    return false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else
      inputString += inChar;
  }
}

//BT event
void serialBTEvent() {
  while (SerialBT.available()) {
    char inChar = (char)SerialBT.read();
    if (inChar == '\n') {
      stringComplete = true;
    } else
      inputString += inChar;
  }
}