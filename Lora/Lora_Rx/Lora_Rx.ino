/*************************************************************************
    PROJECT NAME: Edgehax Lora_Rx
   AUTHOR: Edgehax
   CREATED DATE: 08/11/2023
   COPYRIGHT: Edgehax @MIT license for usage on Edgehax boards
   VERSION: 0.1.0

   DESCRIPTION:Edgehax Lora_Rx

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
  08/11/2023 -    0.1.0       -     Initial release of sample script.
 *************************************************************************/


#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 4
#define rst 14
#define dio0 2

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);
  while (!Serial);

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
//  while (!LoRa.begin(866E6)) {
  while(!LoRa.begin(866E6)){
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("--------------------------------");
  Serial.println(" Bharat Pi LoRa Test Program");
  Serial.println(" Function: Receiver");
  Serial.println("--------------------------------");
  Serial.println("LoRa Receiver");  
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: '");

    // read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
