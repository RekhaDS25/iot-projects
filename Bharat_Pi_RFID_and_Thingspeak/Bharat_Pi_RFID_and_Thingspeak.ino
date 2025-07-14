/*************************************************************************
   PROJECT NAME: /*************************************************************************
   PROJECT NAME: Edgehax NavIC Shield test firmware 
   AUTHOR:Edgehax
   CREATED DATE: 26/03/2024
   COPYRIGHT: Edgehax @MIT license for usage on Edgehax boards
   VERSION: 2.0

   DESCRIPTION: NavIC get latlong and other navigation parameters using Edgehax NavIC tracker shield.

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
   26/03/2024 -    1.0       -    Initial release with Lat long and other nav parameters. Prints to serial monitor.
   05/08/2024 -    2.0       -    Switched to Hardware serial as the software serial had issues with baud rates,
                             -    Added Google maps link so that lat long can be viewed from URL printed on serial monitor

 *************************************************************************/

#include <TinyGPS++.h> //Lib version compatible - 13.0.0
#include <HardwareSerial.h> //This is available from ESP32 itself not an external lib so we are good here.


#define GPS_RX_PIN 33
#define GPS_TX_PIN 32 


TinyGPSPlus gps;
HardwareSerial gpsSerial(1);


void setup() {
    Serial.begin(115200);  
    gpsSerial.begin(115200, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN); 
    delay(5000);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("**********************************************************************************");
    Serial.println("  Edgehax NavIC Shield Test Program\n  You can use the NavIC shield on any Bharat Pi boards.\n");
    Serial.println("  Please wait while the NavIC module latches to satellites.\n");
    Serial.println("  You will notice the \"Red LED\" (PPS) on NavIC shield blinking once it latches.\n\n");
    Serial.println("  IMPORTANT: Ensure that the antenna has sky visibility and its not cloudy else it may not latch.");
    Serial.println("**********************************************************************************");
    Serial.println();
    Serial.println();
    Serial.println("  Awaiting for NavIC satellite signal latching...");
    Serial.println();
    Serial.println();
}


void loop() {
    // Read data from GPS module
    while (gpsSerial.available() > 0) {
        if (gps.encode(gpsSerial.read())) {
            if (gps.location.isValid()) {
                // Get latitude and longitude
                float latitude = gps.location.lat();
                float longitude = gps.location.lng();
                String  date = gps.date.day() + "/" + gps.date.month();
                String time = gps.time.hour() + ":" + gps.time.minute();
                double speedKnots = gps.speed.knots();
                float  courseDeg = gps.course.deg();
                double altitudeMts = gps.altitude.meters();
                uint32_t satellites = gps.satellites.value();
                double hdop = gps.hdop.hdop();

                // Print latitude and longitude, you can uncommment other parameter if you like to view those as well like date/time etc.
                Serial.print("Lat: ");
                Serial.println(latitude, 7);
                Serial.print("Long: ");
                Serial.println(longitude, 7);
                Serial.print("View lat long on Google Maps ===>>> ");
                Serial.println("http://maps.google.com/maps?q=" + String(latitude, 7) + "," + String(longitude, 7));
                // Serial.print("Date: ");
                // Serial.println(date);
                // Serial.print("Time: ");
                // Serial.println(time);
                Serial.print("Speed (knots): ");
                Serial.println(speedKnots, 7);                                                
                Serial.print("Course (degree): ");
                Serial.println(courseDeg, 7);
                Serial.print("Altitude (Meters): ");
                Serial.println(altitudeMts, 7);    
                Serial.print("Satellites:");
                Serial.println(satellites, 7);  
                Serial.print("HDOP:");
                Serial.println(hdop, 7);    
                Serial.println();
                Serial.println();                                                            
            }
        }
    }
} RFID_and_Thingspeak
   AUTHOR: Bharat Pi
   CREATED DATE: 15/05/2024
   COPYRIGHT: BharatPi @MIT license for usage on Bharat Pi boards
   VERSION: 0.1.1

   DESCRIPTION: Bharat Pi RFID_and_Thingspeak
    RFID Module pin connection
    SDA (SS)	-> GPIO21
    SCK	->  GPIO 18 
    MOSI	-> GPIO 23
    MISO ->	GPIO 19
    RST	-> GPIO27
    3.3V	-> 3.3V pin
    GND ->	GND pin 

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
   15/05/2024 -    0.1.0       -    Initial release of sample script.
 *************************************************************************/

#include <WiFi.h>
#include <HTTPClient.h>
#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 21
#define RST_PIN 27

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

// Valid UIDs and corresponding student names
byte validUIDs[][4] = {
  {0xA3, 0x57, 0xB3, 0x30},  // UID of student 1
  {0x53, 0x15, 0x57, 0xC8},  // UID of student 2
  // Add more valid UIDs here
};
const char* studentNames[] = {
  "Bharatpi",  // Name of student 1
  "Welcome",   // Name of student 2
  // Add more student names here
};

const char* ssid = "smile123";
const char* password = "123456789";
const char* server = "http://api.thingspeak.com/update";
const char* apiKey = "1ZQ9LAB3G9CYY6GA";  // change the api key 

void setup() {
  Serial.begin(115200);
  SPI.begin();       // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String rfid = "";
  // Read the RFID tag
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    rfid += String(mfrc522.uid.uidByte[i], HEX);
  }
  rfid.toUpperCase();
  Serial.println("RFID tag: " + rfid);

  // Match the UID
  String studentName = "Unknown";
  for (byte i = 0; i < sizeof(validUIDs) / sizeof(validUIDs[0]); i++) {
    if (memcmp(mfrc522.uid.uidByte, validUIDs[i], mfrc522.uid.size) == 0) {
      studentName = studentNames[i];
      break;
    }
  }
  Serial.println("Student name: " + studentName);

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "?api_key=" + apiKey + "&field2=" + studentName + "&field1=" + rfid;
    Serial.println("URL: " + url); // Debugging URL
    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Response payload: " + payload); // Debugging payload
    } else {
      Serial.println("Error in HTTP request: " + String(http.errorToString(httpCode).c_str()));
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(10000); // Send data every 10 seconds
}
