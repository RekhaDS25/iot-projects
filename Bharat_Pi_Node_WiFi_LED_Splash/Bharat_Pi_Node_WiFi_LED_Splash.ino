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
} Node_WiFi_LED_Splash
   AUTHOR: Bharat Pi
   CREATED DATE: 26/03/2024
   COPYRIGHT: BharatPi @MIT license for usage on Bharat Pi boards
   VERSION: 0.1.0

   DESCRIPTION: Bharat Pi Node_WiFi_LED_Splash.
   
   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
   26/03/2024 -    0.1.0       -    Initial release of sample script.
   
 *************************************************************************/

void ledBlink(int time){
  digitalWrite(2, HIGH);
  delay(time);
  digitalWrite(2, LOW);
  delay(time);
  digitalWrite(12, HIGH);
  delay(time);
  digitalWrite(12, LOW);
  delay(time);
  digitalWrite(13, HIGH);
  delay(time);
  digitalWrite(13, LOW);  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  ledBlink(25);
  ledBlink(25);
  ledBlink(25);
  ledBlink(25);
  ledBlink(25);
  ledBlink(25);  
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);
  ledBlink(50);  
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);
  ledBlink(100);  
  ledBlink(250);
  ledBlink(250);
  ledBlink(250);
  ledBlink(250); 
  ledBlink(500); 
  ledBlink(1000);  

  digitalWrite(2, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:  
  digitalWrite(2, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
}
