/*
* min 984 mid 1500 max 2005
*	
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SDA 8 //Define SDA pins
#define SCL 9 //Define SCL pins
const int servoSignalPin = 1; // GPIO pin connected to the servo tester signal output
volatile int pulseWidth = 0; // Variable to store the pulse width
int percent = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(115200);
  pinMode(servoSignalPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(servoSignalPin), pulseISR, CHANGE);
    Wire.begin(SDA, SCL); // attach the IIC pin 
  if (!(i2CAddrTest(0x27))) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init(); // LCD driver initialization
  lcd.backlight(); // Open the backlight
  lcd.setCursor(0,0); // Move the cursor to row 0, column 0
  lcd.print("hello, world!"); // The print content is displayed on the LCD
}

void loop() {
  // Print the pulse width every second
  Serial.print("Pulse Width: ");
  Serial.print(pulseWidth);
  Serial.println(" microseconds");
  
   lcd.print(percent ); 
    lcd.print("%" );// You can make spaces using well... spaces
    delay(250);
    lcd.clear();
    lcd.setCursor(0, 0); // Or setting the cursor in the desired position.

}

void pulseISR() {
  static unsigned long lastTime = 0;
  unsigned long currentTime = micros();

  if (digitalRead(servoSignalPin) == HIGH) {
    // Rising edge
    lastTime = currentTime;
  } else {
    // Falling edge
    pulseWidth = currentTime - lastTime; // Calculate pulse width
  }
  percent = map(pulseWidth, 1500, 2005, 0, 100);

}
bool i2CAddrTest(uint8_t addr) {
 Wire.begin();
 Wire.beginTransmission(addr);
 if (Wire.endTransmission() == 0) {
 return true;
 }
 return false;
}
