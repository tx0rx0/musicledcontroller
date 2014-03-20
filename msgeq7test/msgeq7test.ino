/*
MSGEQ7 Controlled LED Cube Program
8 January, 2012
Tx0Rx0
All Rights Reserved
Inspiration from J. Skoba MSQEQ7 test
*/

#include "Tlc5940.h"

//MSGEQ7 Pins
#define analogPin A0 // read from multiplexer using analog input 0
#define strobePin 2 // strobe is attached to digital pin 2
#define resetPin  12 // reset is attached to digital pin 3

//Button Pins
#define button1 A2
int button1val = 0;
int spectrumValue[7]; // to hold a2d values
int index; //Index of the greatest Frequency Band

//Volume Constant
int volume;
int lightlevel;

//TLC5940 Pins
#define sclk 13
#define srin 11
#define blnk 10
#define xlat 9
#define gsclk 3

//Counter Variable
int j = 0;
int k = 0;
int m = 0;
int n = 0;
int o = 0;


//LED pins by color and LED number. 1st LED is right next to the voltage regulator

//TLC pin

//Channel 0 UNCONNECTED
//Channel 1 5 BLUE
//Channel 2 5 GREEN
//Channel 3 5 RED
//Channel 4 4 BLU
//Channel 5 4 GREEN
//Channel 6 4 RED
//Channel 7 3 BLUE
//Channel 8 3 GREEN
//Channel 9 3 RED
//Channel 10 2 BLUE
//Channel 11 2 GREEN
//Channel 12 2 RED
//Channel 13 1 BLUE
//Channel 14 1 GREEN
//Channel 15 1 RED

int a;
int b;


void setup()
{
 Serial.begin(9600);
 //Setup TLC and clears any residual data
Tlc.init();
Tlc.clear();
Tlc.update();
 
 
 //MSGEQ7 Arduino Pinmodes
 pinMode(analogPin, INPUT);
 pinMode(strobePin, OUTPUT);
 pinMode(resetPin, OUTPUT);
 analogReference(DEFAULT);
 
 //TLC5940 Pinmodes
 pinMode(sclk, OUTPUT);
 pinMode(srin, OUTPUT);
 pinMode(blnk, OUTPUT);
 pinMode(xlat, OUTPUT);
 pinMode(gsclk, OUTPUT);
 
 //Button and Pot Settings
 pinMode(button1, INPUT);
 
 digitalWrite(resetPin, LOW);
 digitalWrite(strobePin, HIGH);
 
 //Sets Button pins high
 digitalWrite(button1, HIGH);;

}

void loop()
{
//resets pin values
Tlc.clear();
Tlc.update();
 digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);
 
 
 button1val = digitalRead(button1);
 
 //Light Level Trigger Setup
 if (volume > 0)
{
 lightlevel = 400;
}
if (volume > 204)
{
  lightlevel = 200;
}
  if (volume > 408)
  {
    lightlevel = 250;
  }
 if (volume > 612)
 {
   lightlevel = 300;
 }
if (volume > 816)
{
  lightlevel = 1000;
}

lightlevel = 400;
 for (int i = 0; i < 7; i++)
 {
 digitalWrite(strobePin, LOW);
 delayMicroseconds(30); // to allow the output to settle
 spectrumValue[i] = analogRead(analogPin);
 
 //Returns index and value of the most intense frequency band
 
 int biggest = spectrumValue[0];
 for (int m = 1; m < 8; m++);
 if (spectrumValue[m] > biggest) 
 {
 biggest = spectrumValue[m]; 
  index = m;
  Serial.print(index);
 }
 
 

if (j == 0)
{
   //BASS ACTIVATED MODE
   if (spectrumValue[0] > lightlevel)
   {
      Tlc.set(1, 4095);
      Tlc.set(4, 4095);
      Tlc.set(7, 4095);
      Tlc.set(10, 4095);
      Tlc.set(13, 4095);
  
  
   }
   if (spectrumValue[1] > lightlevel)
   {
      Tlc.set(1, 2047);
      Tlc.set(4, 2047);
      Tlc.set(7, 2047);
      Tlc.set(10, 2047);
      Tlc.set(13, 2047);
  
  
   }
   // MIDDLE RESPONSE MODE
   if (spectrumValue[2] > lightlevel)
   {
     Tlc.set(2, 4095);
     Tlc.set(5, 4095);
     Tlc.set(8, 4095);
     Tlc.set(11, 4095);
     Tlc.set(14, 4095);
   }
 
   if (spectrumValue[3] > lightlevel)
   {
     Tlc.set(2, 2047);
     Tlc.set(5, 2047);
     Tlc.set(8, 2047);
     Tlc.set(11, 2047);
     Tlc.set(14, 2047);
   }
    // HIGH RESPONSE MODE
   if (spectrumValue[4] > lightlevel)
   {
     Tlc.set(3, 4095);
     Tlc.set(6, 4095);
     Tlc.set(9, 4095);
     Tlc.set(12, 4095);
     Tlc.set(15, 4095);
   }

 
  if (spectrumValue[5] > lightlevel)
 {
   Tlc.set(3, 2047);
   Tlc.set(6, 2047);
   Tlc.set(9, 2047);
   Tlc.set(12, 2047);
   Tlc.set(15, 2047);
 }

}

//CYLON MODE
if (j == 2)
{
  if (index == 0)
  {
  }
  if (index == 1)
  {
  }
  if (index == 2)
  {
  }
  if (index == 3)
  {
  }
  if (index == 4)
  {
  }
  if (index == 5)
  {
  }
  if (index == 6)
  {
  }
  if (index == 7)
  {
  }
  
  
}
if (j > 1)
{
  j = 0;
}
 
 //Pushes Changes to the TLC
 Tlc.update();



 //Serial.println();
 // comment out/remove the serial stuff to go faster
 // - its just here for show
 if (spectrumValue[i] < 10)
 {
 Serial.print(" ");
 Serial.print(spectrumValue[i]);
 }
 else if (spectrumValue[i] < 100 )
 {
 
 Serial.print(" ");
 Serial.print(spectrumValue[i]);
 }
 else
 {
 Serial.print(" ");
 Serial.print(spectrumValue[i]);
 }

 digitalWrite(strobePin, HIGH);
 }
 Serial.println();



}


