/*************************************************************************
   PROJECT NAME: Edgehax Wi-Fi_Connect_with_Time_Sync
   AUTHOR: Edgehax
   CREATED DATE: 26/03/2024
   COPYRIGHT: Edgehax @MIT license for usage on Bharat Pi boards
   VERSION: 0.1.0

   DESCRIPTION: Edgehax Wi-Fi_Connect_with_Time_Sync

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
   26/03/2024 -    0.1.0       -    Initial release of sample script.
   
 *************************************************************************/


#include <WiFi.h>
#include "time.h"

const char* ssid       = "ACT 1ST FLOOR"; // Wi-Fi to connect, ensure to type exact name and is case sensitive 
const char* password   = "1@Jjj4656#"; //Wi-Fi password

const char* ntpServer = "pool.ntp.org"; //NTP server to which the board will set the time
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

IPAddress ipAddress;
bool isWIFIConnected = false;

void printLocalTime()
{
  struct tm timeinfo;
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%d%m%y_%H%M%S");
}

void setup() {
  Serial.begin(115200);
  Serial.flush();

  Serial.printf("Connecting to Wi-Fi: %s", ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    vTaskDelay(1000);
    Serial.print(".");
  }

  isWIFIConnected = true;
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ipAddress = WiFi.localIP();

  Serial.println("Timesync in progress...");
  printLocalTime();  

  delay(1000);
  WiFiClient client;
}

void loop() {
  // put your main code here, to run repeatedly:

}
