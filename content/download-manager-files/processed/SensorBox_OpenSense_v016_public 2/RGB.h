// call RGBLed(red); for red led
#include "arduino.h"

typedef struct {
  int r;
  int g;
  int b;
} RGB;

//connect RGB Led with resistors to pin:
#define redPin 13
#define greenPin 12
#define bluePin 11

RGB red = { 0 , 255 , 255 };
RGB blue = { 255, 255, 0};
RGB green = { 255, 0, 255};
RGB white = { 130,0,0};
RGB magenta = { 0,255,0 };
RGB yellow = { 0,0, 255};
RGB cyan = {255,0,0};
RGB mint =  {255,0,200};
RGB pink = {0,80, 80};
/*
StatusLed:
Boot - White 
Time NTP - pink -   
Data to opensense - green 
Data to Wunderground - cyan

Data to pvoutput - purple

Idle - yellow //Yellow in Idle status
Network error - Rood 
RF12 data receiving -  blue - 
*/

void RGBLed(RGB& rgb){
 analogWrite(redPin,rgb.r);
 analogWrite(greenPin,rgb.g);
 analogWrite(bluePin,rgb.b);
}

