/*
    Author: Mehmet Furkan KAYA
    Version: Arduino CANBUS Receiver
    Arbitration ID: 0x036
*/

#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(10);

#define BUZZER_PIN 5
#define LED_PIN 13

void setup() { 
  Serial.begin(9600);
  SPI.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    
    if (canMsg.can_id == 0x036) {  
      Serial.print("ID: 0x");
      Serial.println(canMsg.can_id, HEX);

      Serial.print("Data: ");
      for (int i = 0; i < canMsg.can_dlc; i++) { 
        Serial.print(canMsg.data[i]);
        Serial.print(" ");
      }
      Serial.println();

      if (canMsg.data[0] == 1) {
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
      } else if (canMsg.data[0] == 0) {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
      }
    }
  }
}
