/*************************************************************************
   PROJECT NAME:  Edgehax Ultrasonic sensor Sample Code
   AUTHOR: Edgehax
   CREATED DATE: 02/08/2023
   COPYRIGHT: Edgehax @MIT license for usage on Edgehax boards
   VERSION: 0.1.1

   DESCRIPTION: This script will give you the sample testing of ultrasonic sensor,
   which will measure the distance and
   prints the distance values in cm when you run the code.

   REVISION HISTORY TABLE:
   ------------------------------------------
   Date      | Firmware Version | Comments
   ------------------------------------------
   02/08/2023 -    0.1.0       -    Initial release of ultrasonic sensor sample script to read the data.
                                    (Used Arduino IDE version - 2.3.2,
                                    Used board manager - esp32 by Espressif version - 2.0.16)
                                    
   o6/06/2024 -    0.1.1       -    Added the Updated version of board manager and lib
                                    (esp32 by Espressif version - 3.0.0,
                                    NewPing Lib version - 1.9.7)

 *************************************************************************/     


#include <NewPing.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


#define TRIG_PIN 33
#define ECHO_PIN 32


#define MAX_DISTANCE 200 // Maximum distance to measure (in centimeters)


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // Create a NewPing object


LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your LCD I2C address if different


void setup() {
  lcd.begin();
  lcd.backlight();
  lcd.print("Ultrasonic Sensor");
  lcd.print("By Bharath Pi");
  }
