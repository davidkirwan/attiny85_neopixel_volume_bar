/*
 attiny85 powered neopixel volume bar

 Requires Adafruit NeoPixel Library: https://github.com/adafruit/Adafruit_NeoPixel
 attiny85: https://www.aliexpress.com/item/Digispark-Kickstarter-USB-Development-Board-for-arduino-NEW/32279051124.html
 DFPlayer Mini: https://www.aliexpress.com/item/DFPlayer-Mini-MP3-Player-Module-for-Arduino/32477796921.html
 Microphone:  https://www.aliexpress.com/item/Wholesale-Sound-Detection-Sensor-Module-Sound-Sensor-Intelligent-Vehicle-For-Arduino/1540010132.html
 NeoPixel Bar: https://www.aliexpress.com/item/WS2812-5050-8Bit-Board-Full-color-RGB-LED-Bar-for-Arduino-Developer/32704874557.html
 GPL v3
*/

#include <Adafruit_NeoPixel.h>

#define MICPIN         A0
#define NEOPIXELPIN    2
#define NUMPIXELS      8

int peakhigh = 0;
int peaklow = 1023;
int peak = 0;
int threshold = 0;
int lvl = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);


void setup(){
  //Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop(){
  peak = 0;
  lvl = 0;
  peak = analogRead(MICPIN);

  if(peak > peakhigh){ 
    peakhigh = peak;
  }

  if(peak < peaklow){ 
    peaklow = peak;
  }

  threshold = ((peakhigh - peaklow) / 2) + peaklow;

  if(peak >= threshold){
    lvl = map(peak, threshold, peakhigh, 0, 8);
  }
  else{
    lvl = map(peak, peaklow, threshold, 0, 8);
  }
  
    
  /*
  Serial.print(peak);
  Serial.print(", ");
  Serial.print(treshhold);
  Serial.print(", ");
  Serial.print(peaklow);
  Serial.print(", ");
  Serial.print(peakhigh);
  Serial.print(", ");
  Serial.println(lvl);
  */

  
  for(int i=0;i<lvl;i++){
    if(i < 4)
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // green
    if(i < 6)
      pixels.setPixelColor(i, pixels.Color(0, 255, 0)); // yellow
    else
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // red
  }
  for(int i=NUMPIXELS;i>lvl;i--){
    pixels.setPixelColor(i, 0);
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(20);
}
