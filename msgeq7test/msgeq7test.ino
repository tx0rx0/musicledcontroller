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

//Button/Pot Pins
#define button1 A2
#define button2 A3
#define volumepot A1

int spectrumValue[7]; // to hold a2d values
int index; //Index of the greatest Frequency Band


//Test Button Values
int button1state = 1;
int button2state = 1;

//button readings
int button1val;
int button2val;

//Previous button readings
int lastbutton1state = HIGH;
int lastbutton2state = HIGH;


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

//Button Debounce Variables
long lastdebouncetime1 = 0;
long lastdebouncetime2 = 0;
long debouncedelay = 50; 

//Individual LED Color Arrays
int redledpins[5] = { 1, 5, 9, 13, 10 };
int greenledpins[5] = { 3, 7, 11, 2, 14};
int blueledpins[5] = { 4, 8, 12, 6, 15};

//Individual LED Arrays
int led1pins[3] = {1, 3, 4};
int led2pins[3] = {5, 7, 8};
int led3pins[3] = {9, 11, 12};
int led4pins[3] = {13, 2, 6};
int led5pins[3] = {10, 14, 15};



//1r 1
//1g 3
//1b 4
//2r 5
//2g 7
//2b 8 
//3r 9
//3g 11 
//3b 12
//4r 13
//4g 2
//4b 6
//5r 10
//5g 14
//5b 15

int a;
int b;

//Returns common values in lednpins and colorledpins arrays
/*
int  common_elements1(int a[], int b[]){
  
a.sort();
b.sort();
n, o = 0, 0;
common = [];
while n < len(a) and 0 < len(b):

if (a[n] == b[o])
{
  common.append(a[i]);
  n += 1;
  n += 1;
}
if (a[n] < b[o])
{
  n += 1;
else
{
  o += 1;
}
}
*/

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
 pinMode(button2, INPUT);
 //pinMode(volumepot, INPUT);
 
 digitalWrite(resetPin, LOW);
 digitalWrite(strobePin, HIGH);
 
 //Sets Button pins high
 digitalWrite(button1, HIGH);
 digitalWrite(button2, HIGH);

 Serial.println("MSGEQ7 test by J Skoba");
}



  

void loop()
{
//resets pin values
Tlc.clear();
Tlc.update();
 digitalWrite(resetPin, HIGH);
 digitalWrite(resetPin, LOW);
 
 
 button1val = digitalRead(button1);
 button2val = digitalRead(button2);
 
int volume = analogRead(volumepot);

//Button Value Sets
 if (button1val != lastbutton1state )
 {
   lastdebouncetime1 = millis();
 }
 if (button2val != lastbutton2state)
 {
   lastdebouncetime2 = millis();
 }
 
 if((millis() - lastdebouncetime1) > debouncedelay)
 {
   button1state = button1val;
 }
 if((millis() - lastdebouncetime2) > debouncedelay)
 {
   button2state = button2val;
 }
 
 
 
 //saves button states
 lastbutton1state = button1val;
 lastbutton2state = button2val;
 
 //Counter Iterations
 if (button1state == 0)
 {
   j=j+1;
 }
 if (button2state == 0 )
 {
   k = k+1;
 }
 
 //Goes Back to 0
 if (j > 1)
 {
   j = 0;
 }
 



 
 //Light Level Trigger Setup
 if (volume > 0)
{
 lightlevel = 150;
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
 
 
if  (j == 1)
{
//Button Values  
button1val = digitalRead(button1);
button2val = digitalRead(button2);
   if (button2val == 0)
 {
  k += 1; 
 }
  if (k == 0)
  {
      Tlc.set(1, 4095);
      Tlc.set(2, 4095);
      Tlc.set(3, 4095);
      Tlc.set(4, 4095);
      Tlc.set(5, 4095);
      Tlc.set(6, 4095);
      Tlc.set(7, 4095);
      Tlc.set(8, 4095);
      Tlc.set(9, 4095);
      Tlc.set(10, 4095);
      Tlc.set(11, 4095);
      Tlc.set(12, 4095);
      Tlc.set(13, 4095);
      Tlc.set(14, 4095);
      Tlc.set(15, 4095);   
  }
  if (k == 1)
  {
    Tlc.set(1, 0);
      Tlc.set(2, 0);
      Tlc.set(3, 0);
      Tlc.set(4, 4095);
      Tlc.set(5, 0);
      Tlc.set(6, 4095);
      Tlc.set(7, 0);
      Tlc.set(8, 4095);
      Tlc.set(9, 0);
      Tlc.set(10, 0);
      Tlc.set(11, 0);
      Tlc.set(12, 4095);
      Tlc.set(13, 0);
      Tlc.set(14, 0);
      Tlc.set(15, 4095);
  }
   
   
      Tlc.update();
        //Resets State Checks
        
 
      
}

if (j == 0)
{
   //BASS ACTIVATED MODE
   if (spectrumValue[0] > lightlevel)
   {
      Tlc.set(3, 4095);
      Tlc.set(7, 4095);
      Tlc.set(11, 4095);
      Tlc.set(14, 4095);
      Tlc.set(2, 4095);
  
  
   }
   if (spectrumValue[1] > lightlevel)
   {
      Tlc.set(3, 2047);
      Tlc.set(7, 2047);
      Tlc.set(11, 2047);
      Tlc.set(14, 2047);
      Tlc.set(2, 2047);
  
  
   }
   // MIDDLE RESPONSE MODE
   if (spectrumValue[2] > lightlevel)
   {
     Tlc.set(4, 4095);
     Tlc.set(8, 4095);
     Tlc.set(12, 4095);
     Tlc.set(15, 4095);
     Tlc.set(6, 4095);
   }
 
   if (spectrumValue[3] > lightlevel)
   {
     Tlc.set(4, 2047);
     Tlc.set(8, 2047);
     Tlc.set(12, 2047);
     Tlc.set(15, 2047);
     Tlc.set(6, 2047);
   }
    // HIGH RESPONSE MODE
   if (spectrumValue[4] > lightlevel)
   {
     Tlc.set(1, 4095);
     Tlc.set(5, 4095);
     Tlc.set(9, 4095);
     Tlc.set(13, 4095);
     Tlc.set(10, 4095);
   }

 
  if (spectrumValue[5] > lightlevel)
 {
   Tlc.set(1, 2047);
   Tlc.set(5, 2047);
   Tlc.set(9, 2047);
   Tlc.set(13, 2047);
   Tlc.set(10, 2047);
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
 //Tlc.set(6, 4095);
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


