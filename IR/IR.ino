#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2

void setup() {
  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("Sony IR Remote Decoder");
  Serial.println("Press a button...");
}

void loop() {
  if (IrReceiver.decode()) {

    Serial.println("-------------------------");

    // Print decoded information
    IrReceiver.printIRResultShort(&Serial);

    // Show protocol and decoded data
    Serial.print("Protocol: ");
    Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));

    Serial.print("Address : 0x");
    Serial.println(IrReceiver.decodedIRData.address, HEX);

    Serial.print("Command : 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    Serial.print("Raw Data: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    Serial.print("Bits    : ");
    Serial.println(IrReceiver.decodedIRData.numberOfBits);

    IrReceiver.resume();
  }
}