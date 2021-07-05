#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "DHT.h"


/* --------------------- DHT11 Digital Sensor --------------------- */
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
/* --------------------- End --------------------- */

/* --------------------- LDR Sensor --------------------- */
int LDR = A5;     // Analog pin connected to the LDR sensor
int LDR_Value = 0; // the greater the intensity of light, the greater the corresponding voltage(LDR_Value) from the LDR will be
/* --------------------- End --------------------- */

/* --------------------- LED Moving Sign --------------------- */
// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 40;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 0; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  75
char curMessage[BUF_SIZE] = { "" };
bool newMessageAvailable = true;

//Global ...
char data[2] ;

void setup() {
  dht.begin();
  Serial.begin(9600);

  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
}


void loop() {
  float h = dht.readHumidity();        // read humidity
  float t = dht.readTemperature();     // read temperature
  LDR_Value = analogRead(LDR);
  if (Serial.available()) {
    Serial.readBytes(data, 24);
  }

  if (P.displayAnimate())
  {
    if (newMessageAvailable)
    {
      char newMessage[BUF_SIZE] = { "T: , H: , L: " };


      int Hour = 23, Minute = 32, Second = 43, Year = 2021, Month = 11, Day = 30;
      String message =  String(
                          "T: " + String(t, 0) + \
                          ", H: " + String(h, 0) + \
                          ", L: " + String(LDR_Value) + \
                          "Time: " + String(data)
                        );
//      String message = String(
//                         data
//                       );
      message.toCharArray(newMessage, BUF_SIZE);
      strcpy(curMessage, newMessage);
      newMessageAvailable = true;
    }
    P.displayReset();
  }
}
