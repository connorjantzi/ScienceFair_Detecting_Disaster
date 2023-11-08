/***************************************************************************
 THIS IS CONNOR Science project.
 This is using AI to maintain green spaces.
 It uses a water pump controlled by a transistor
 It used a Temperature, Pressure, and Humidity sensor to determine when to Water.
 It has a LCD screen to display data
 It has a LED system which lights up before the Water Pump begins to warn people in the area.
 
 ***************************************************************************/

#include <Wire.h>
#include "cactus_io_BME280_I2C.h"   // Temperature sensor library.
#include <LiquidCrystal_I2C.h>     // LCD library
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 

// Create the BME280 object
BME280_I2C bme;              // I2C using default 0x77 
// or BME280_I2C bme(0x76);  // I2C using address 0x76
float temp;
int ledPin=8; //definition digital 8 pins as pin to control the LED

// PUMP CONTROL
int motorPin = 3;

void setup() {
 Serial.begin(9600);

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  bme.setTempCal(-1);
  
  Serial.println("Pressure\tHumdity\t\tTemp\t\tTemp");

  // activate LED
  // pinMode(ledPin,OUTPUT);    //Set the digital 8 port mode, OUTPUT: Output mode

  // lcd setup
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light

  // PUMP CONTROL IN SETUP
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
}

void loop() {

    bme.readSensor(); 
  
    Serial.print(bme.getPressure_MB()); Serial.print("\t\t");    // Pressure in millibars
    Serial.print(bme.getHumidity()); Serial.print("\t\t");
    Serial.print(bme.getTemperature_C()); Serial.print(" *C\t");
    Serial.print(bme.getTemperature_F()); Serial.println(" *F\t");
    
    temp = bme.getTemperature_C();  // write temperature to a variable
    Serial.print ("Our Science project");
    Serial.print (temp);
    Serial.print ("Connor and Tanner");
    if(temp>15) digitalWrite(ledPin,HIGH);

    // PUMP CONTROL 
    // ADD IF STATEMENTS DEPENDING ON TEMPERATURE HERE
    //digitalWrite (motorPin, HIGH); // on
   // digitalWrite (motorPin, LOW); // off

    if(temp > 25) // turn on pump and led on this condition
    {
      digitalWrite (motorPin, HIGH); // turn pump on
      pinMode(ledPin,OUTPUT); // turn on led
    }
    if(temp < 25) // turn on pump and led on this condition
    {
      digitalWrite (motorPin, LOW); // turn pump off
      
    }

    //LCD code
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("Temperture"); //You can write 16 Characters per line .
    delay(1000);//Delay used to give a dynamic effect
    lcd.setCursor(0,2);  //Defining positon to write from second row,first column .
    lcd.print(temp);if(temp > 15) // turn on pump and led on this condition
    {
      digitalWrite (motorPin, HIGH); // on
      pinMode(ledPin,OUTPUT); // turn on led
    }if(temp > 15) // turn on pump and led on this condition
    {
      digitalWrite (motorPin, HIGH); // on
      pinMode(ledPin,OUTPUT); // turn on led
    }
    delay(4000); 

    lcd.clear();//Clean the screen
    lcd.setCursor(0,0); 
    lcd.print( "the fair");
    lcd.setCursor(0,1);
    lcd.print("humidity");
    delay(4000); 
    
    // add a 2 second delay to slow down the output
    delay(8000);
}
