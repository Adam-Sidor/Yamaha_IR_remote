#include "PinDefinitionsAndMore.h"  // Set IR_SEND_PIN for different CPU's
#include "TinyIRSender.hpp"         //use when u use IR diode
//#include "TinyIRSenderReverse.hpp"  //use when u direct connect EPS to reciver in Yamaha
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
  // digitalWrite(IR_SEND_PIN,HIGH);//comment this line if u are using IR diode
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
    if (catchSerial("HDMI1"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x3847, 0);
    if (catchSerial("HDMI2"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x354a, 0);
    if (catchSerial("HDMI3"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x324d, 0);
    if (catchSerial("Audio1"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x1a65, 0);
    if (catchSerial("Audio2"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x1768, 0);
    if (catchSerial("Audio3"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x037c, 0);
    if (catchSerial("Audio4"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x007f, 0);
    if (catchSerial("Audio5"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xd3ac, 0);
    if (catchSerial("Audio6"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xcfb0, 0);
    if (catchSerial("Setup"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x7b84, 0);
    if (catchSerial("Return"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x55aa, 0);
    if (catchSerial("Enter"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x21de, 0);
    if (catchSerial("Up"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x629d, 0);
    if (catchSerial("Down"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x639c, 0);
    if (catchSerial("Left"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x609f, 0);
    if (catchSerial("Right"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x619e, 0);
    if (catchSerial("Option"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0x146b, 0);
    if (catchSerial("Sleep"))
      sendONKYO(IR_SEND_PIN, 0x857A, 0xcf30, 0);
    customValue();
    inputString = "";
    stringComplete = false;
  }
}

void customValue() {
  if (catchSerial("H")) {
    uint16_t customAddress = 0, customCommand = 0;
    String customAddr = "";
    if (inputString[2] == 'A' || inputString[2] == 'a')
      customAddr = "0x85" + inputString.substring(1, inputString.indexOf("-"));
    else if (inputString[2] == 'E' || inputString[2] == 'e')
      customAddr = "0x81" + inputString.substring(1, inputString.indexOf("-"));
    customAddress = strtol(customAddr.c_str(), NULL, 16);
    String customCom = "0x" + inputString.substring(inputString.indexOf("-") + 1);
    customCommand = strtol(customCom.c_str(), NULL, 16);
    Serial.println(customAddress);
    Serial.println(customCommand);
    sendONKYO(IR_SEND_PIN, customAddress, customCommand, 0);
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