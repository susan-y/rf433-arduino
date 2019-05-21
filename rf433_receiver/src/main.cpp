#include <Arduino.h>
#include <stdint.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
int ledRed = 3; // the PWM pin the LED is attached to
int ledYellow = 5;
int ledGreen = 6;

void setup()
{
    Serial.begin(115200);  // Debugging only
    if (!driver.init()) {
      Serial.println("init failed");
    } else {
      Serial.println("init success!");
    }    

    pinMode(ledRed, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);
}

void loop()
{    
    uint8_t buf[50];
    memset(buf, 0, 50);
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      digitalWrite(ledRed, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledGreen, LOW);
      
      int i;
      // Message with a good checksum received, dump it.
      String message = (char*)buf;                                                  
      Serial.print("Message: ");
      Serial.println(message);                   
      
      if (message.equals("red")) {
        digitalWrite(ledRed, HIGH);
      } else if(message.equals("yellow")) {
        digitalWrite(ledYellow, HIGH);
      } else if(message.equals("green")) {
        digitalWrite(ledGreen, HIGH);
      } else {
        digitalWrite(ledGreen, HIGH);        
        digitalWrite(ledRed, HIGH);
      }
    } 
    delay(100);
}
