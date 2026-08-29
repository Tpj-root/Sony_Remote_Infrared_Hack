#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2

// =====================================================
// IR KEY DATABASE
// =====================================================

struct IRKey {
  const char* name;
  decode_type_t protocol;
  uint16_t address;
  uint16_t command;
  uint8_t bits;
};

// -----------------------------------------------------
// Add your keys here
// -----------------------------------------------------

IRKey keys[] = {

  // name       protocol  address  command  bits
  { "CH+",      NEC,      0x00,    0x47,    32 },
  { "CH",      NEC,      0x00,    0x00,    32 },
  { "CH-",      NEC,      0x00,    0x45,    32 },
  { "NEXT",      NEC,      0x00,    0x40,    32 },
  { "PREV",      NEC,      0x00,    0x44,    32 },
  { "VOL-",      NEC,      0x00,    0x7,    32 },
  { "ZERO",      NEC,      0x00,    0x16,    32 },
  { "100+",      NEC,      0x00,    0x19,    32 },
  { "ONE",      NEC,      0x00,    0xC,    32 },
  { "TWO",      NEC,      0x00,    0x18,    32 },
  { "THREE",      NEC,      0x00,    0x5E,    32 }


  // Future keys:
  // { "CH-",   NEC,      0x00,    0x46,    32 },
  // { "VOL+",  NEC,      0x00,    0x40,    32 },
  // { "VOL-",  NEC,      0x00,    0x44,    32 },
  // { "POWER",  NEC,      0x00,    0x45,    32 },

};

// Automatically calculate number of keys
const uint8_t NUM_KEYS = sizeof(keys) / sizeof(keys[0]);


// =====================================================
// FIND KEY
// =====================================================

const char* findKey(decode_type_t protocol,
                    uint16_t address,
                    uint16_t command,
                    uint8_t bits) {

  for (uint8_t i = 0; i < NUM_KEYS; i++) {

    if (keys[i].protocol == protocol &&
        keys[i].address  == address &&
        keys[i].command  == command &&
        keys[i].bits     == bits) {

      return keys[i].name;
    }
  }

  return nullptr;
}


// =====================================================
// PRINT UNKNOWN IR DATA
// =====================================================

void printUnknownData() {

  Serial.println();
  Serial.println("UNKNOWN KEY");
  Serial.println("-------------------------");

  Serial.print("Protocol= ");
  Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));

  Serial.print("Address = 0x");
  Serial.println(IrReceiver.decodedIRData.address, HEX);

  Serial.print("Command = 0x");
  Serial.println(IrReceiver.decodedIRData.command, HEX);

  Serial.print("Raw Data= 0x");
  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

  Serial.print("Bits    = ");
  Serial.println(IrReceiver.decodedIRData.numberOfBits);

  Serial.println("-------------------------");
}


// =====================================================
// SETUP
// =====================================================

void setup() {

  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println();
  Serial.println("==============================");
  Serial.println("     IR KEY IDENTIFIER");
  Serial.println("==============================");

  Serial.print("Stored keys: ");
  Serial.println(NUM_KEYS);

  Serial.println();
  Serial.println("Press a button...");
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  if (IrReceiver.decode()) {

    decode_type_t protocol =
        IrReceiver.decodedIRData.protocol;

    uint16_t address =
        IrReceiver.decodedIRData.address;

    uint16_t command =
        IrReceiver.decodedIRData.command;

    uint8_t bits =
        IrReceiver.decodedIRData.numberOfBits;


    // -------------------------------------------------
    // Ignore repeat frames
    // -------------------------------------------------

    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {

      IrReceiver.resume();
      return;
    }


    // -------------------------------------------------
    // Search stored keys
    // -------------------------------------------------

    const char* keyName =
        findKey(protocol, address, command, bits);


    // -------------------------------------------------
    // MATCH FOUND
    // -------------------------------------------------

    if (keyName != nullptr) {

      Serial.print("KEY: ");
      Serial.println(keyName);

    }

    // -------------------------------------------------
    // UNKNOWN KEY
    // -------------------------------------------------

    else {

      printUnknownData();

    }


    IrReceiver.resume();
  }
}