// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "NewPing.h"
#include "LiquidCrystal.h"
#include "LDR.h"
#include "LED.h"
#include "Switchable.h"
#include "Relay.h"
#include "SoilMoisture.h"
#include "Pump.h"
#include <Keypad.h>

#include <dht.h>

dht DHT;

#define DHT11_PIN 6


// Pin Definitions
#define DHT_PIN_DATA	6
#define HCSR04_PIN_TRIG	8
#define HCSR04_PIN_ECHO	7
#define KEYPADMEM3X4_PIN_3	11
#define KEYPADMEM3X4_PIN_2	10
#define KEYPADMEM3X4_PIN_1	9
#define KEYPADMEM3X4_PIN_7	15
#define KEYPADMEM3X4_PIN_6	14
#define KEYPADMEM3X4_PIN_5	13
#define KEYPADMEM3X4_PIN_4	12
#define LCD_PIN_RS	21
#define LCD_PIN_E	20
#define LCD_PIN_DB4	16
#define LCD_PIN_DB5	17
#define LCD_PIN_DB6	18
#define LCD_PIN_DB7	19
//#define LDR_PIN_SIG	A10
#define LEDBlue_PIN_VIN	2
#define LEDGreen_PIN_VIN	3
#define LEDRed_PIN_VIN	4
#define LEDYellow_PIN_VIN	5
#define RELAYMODULE_PIN_SIGNAL	22
#define SOILMOISTURE_PIN_SIG	A0
#define WATERPUMP_PIN_COIL1  38


// Global variables and defines
#define THRESHOLD_ldr   100
int ldrAverageLight;
// object initialization
//DHT dht(DHT_PIN_DATA);
NewPing hcsr04(HCSR04_PIN_TRIG,HCSR04_PIN_ECHO);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
//LDR ldr(LDR_PIN_SIG);
LED ledB(LEDBlue_PIN_VIN);
LED ledG(LEDGreen_PIN_VIN);
LED ledR(LEDRed_PIN_VIN);
LED ledY(LEDYellow_PIN_VIN);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
SoilMoisture soilMoisture(SOILMOISTURE_PIN_SIG);
Pump waterpump(WATERPUMP_PIN_COIL1);


// define vars for testing menu
const int timeout = 1000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'9','6','3'},
  {'8','5','2'},
  {'7','4','1'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {15, 14, 13, 12}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {11, 10, 9};    //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
//    dht.begin();
    // set up the LCD's number of columns and rows
     lcd.begin(16, 2);
//    ldrAverageLight = ldr.readAverage();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
   }

   // menu();
}





// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{


 int soilMoistureVal = soilMoisture.read();
int percentage=map(soilMoistureVal, 900, 400, 0, 100);

if(percentage>100){
      percentage=100;
      
      }else
      if(percentage<0){
        
      percentage=0;
      }
 
   //Serial.print(F("Val kk: "));
   Serial.println(percentage);
   
                if(percentage>85){
   
digitalWrite(LEDGreen_PIN_VIN, HIGH); 
digitalWrite(LEDRed_PIN_VIN, LOW);
digitalWrite(LEDYellow_PIN_VIN, LOW);
                       
         relayModule.off();       // 1. turns on
   
   
      lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture Content");
   
     
     lcd.setCursor(2, 1);
    lcd.print("Moist=");
    lcd.setCursor(8, 1);
    lcd.print(percentage);
    lcd.setCursor(11, 1);
    lcd.print("% ");
  } else 
      if(percentage<30){
       
          
digitalWrite(LEDGreen_PIN_VIN, LOW); 
digitalWrite(LEDRed_PIN_VIN, HIGH);
digitalWrite(LEDYellow_PIN_VIN, LOW);
                                     
   
    relayModule.on();       // 1. turns on
    //delay(500);

    
      lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("Moisture Content");
   
     
     lcd.setCursor(2, 1);
    lcd.print("Moist=");
    lcd.setCursor(8, 1);
    lcd.print(percentage);
    lcd.setCursor(11, 1);
    lcd.print("% ");
        }
//
        if(percentage>30 && percentage<85 ){

            
digitalWrite(LEDGreen_PIN_VIN, LOW); 
digitalWrite(LEDRed_PIN_VIN, LOW);
digitalWrite(LEDYellow_PIN_VIN, HIGH); 

         
      lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Moisture Content");
   
     
     lcd.setCursor(2, 1);
    lcd.print("Moist=");
    lcd.setCursor(8, 1); 
    lcd.print(percentage);
    lcd.setCursor(11, 1);
    lcd.print("% ");
          
          }


      char customKey = customKeypad.getKey();
     if (customKey){
    Serial.println(customKey);
    if(customKey=='1'){
      lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("Moisture Content");
   
     
     lcd.setCursor(2, 1);
    lcd.print("Moist=");
    lcd.setCursor(8, 1);
    lcd.print(percentage);
    lcd.setCursor(11, 1);
    lcd.print("% ");

    
      } else 

                if(customKey=='2'){
    
 int chk = DHT.read11(DHT11_PIN);
 
    lcd.clear();
    
      lcd.setCursor(0, 0);
    lcd.print("Room Temperature");
    lcd.setCursor(4, 1);
    lcd.print(DHT.temperature);
        lcd.setCursor(10, 1);
    lcd.print("^C");


    delay(3000);
      }else
      
              if(customKey=='3'){
                
    int chk = DHT.read11(DHT11_PIN);
 
    lcd.clear();
    
      lcd.setCursor(0, 0);
    lcd.print("Room Humidity");
    lcd.setCursor(4, 1);
    lcd.print(DHT.humidity);
        lcd.setCursor(10, 1);
    lcd.print("%");

    delay(3000);
     
    }else
    
                 if(customKey=='4'){

                
                  // set the cursor to (0,0):
                  lcd.setCursor(0, 0);
                  // print from 0 to 9:
                  for (int thisChar = 0; thisChar < 10; thisChar++) {
                    lcd.print("Intelligent Automatic Irrigation System");
                    delay(500);
                  }
                
                  // set the cursor to (16,1):
                  lcd.setCursor(16, 1);
                  // set the display to automatically scroll:
                  lcd.autoscroll();
                  // print from 0 to 9:
                  for (int thisChar = 0; thisChar < 10; thisChar++) {
                    lcd.print("");
                    delay(500);
                  }
                  // turn off automatic scrolling
                  lcd.noAutoscroll();
                
                  // clear screen for the next loop:
                  lcd.clear();

                // delay(600000);
//      lcd.clear();
//      // LDR (Mini Photocell) - Test Code
//    // Get current light reading, substract the ambient value to detect light changes
//    int ldrSample = ldr.read();
//    int ldrDiff = abs(ldrAverageLight - ldrSample);
//    Serial.print(F("Light Diff: ")); Serial.println(ldrDiff);
//
//    lcd.setCursor(0, 0);
//    lcd.print("Light Diff= ");
//    lcd.setCursor(12, 0);
//    lcd.print(ldrDiff);
////     lcd.setCursor(9, 0);
////    lcd.print("cm");
//delay(2000);
    }
    else
    
              if(customKey=='5'){
      lcd.clear();
       // Read distance measurment from UltraSonic sensor           
    int hcsr04Dist = hcsr04.ping_cm();
    delay(10);
    Serial.print(F("Distance: ")); Serial.print(hcsr04Dist); Serial.println(F("[cm]"));

    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.setCursor(6, 0);
    lcd.print(hcsr04Dist);
     lcd.setCursor(9, 0);
    lcd.print("cm");
    delay(2000);
    }

   
  }

delay(1000);
    }
