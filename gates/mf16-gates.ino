/*
* Rogue Hack Lab
* Rogue Valley Mini Maker Faire - 2016
* Micro Drone Racing
* Race Gate LED control system
* Hardware:
*   Particle Proton         https://www.particle.io/products/hardware/photon-wifi-dev-kit
*   Adafruit NeoPixel       https://www.adafruit.com/products/1461
* Libraries:
*   Adafruit NeoPixel       https://github.com/adafruit/Adafruit_NeoPixel
* Authors:
*   Code adapted from SparkCore NeoPixel example library https://github.com/technobly/SparkCore-NeoPixel
*   Kevin Conner            kevin.r.conner@gmail.com
*/

/** TODO:
 * 1. Refactor code to allow for different particle boards/strips to be addressed
 * 2. Add VFX
 *  a. Sparkle  - have static colors brighten then fade to black
 *  b. Worm     - have worms (consecutively lit LED's of varying length) travel along the strip
 */

#include "application.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D7
#define PIXEL_COUNT 60
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

enum lane {lane1, lane2, lane3};

enum scrollDirection {up, down, in, out};

int gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };


//   __    ___   _     ___   ___   __
//  / /`  / / \ | |   / / \ | |_) ( (`
//  \_\_, \_\_/ |_|__ \_\_/ |_| \ _)_)

uint32_t black = Adafruit_NeoPixel::Color(0,0,0);
uint32_t white = Adafruit_NeoPixel::Color(255,255,255);

uint32_t red = Adafruit_NeoPixel::Color(255,0,0);
uint32_t orange = Adafruit_NeoPixel::Color(255,150,0);
uint32_t yellow = Adafruit_NeoPixel::Color(255,255,0);
uint32_t green = Adafruit_NeoPixel::Color(0,255,0);
uint32_t blue = Adafruit_NeoPixel::Color(0,0,255);
uint32_t cyan = Adafruit_NeoPixel::Color(0,255,255);
uint32_t magenta = Adafruit_NeoPixel::Color(255,0,255);

uint32_t lane1Color = green;
uint32_t lane2Color = white;
uint32_t lane3Color = blue;

uint8_t getRed(uint32_t color){
    return (color >> 16) & 0xff;
}
uint8_t getGreen(uint32_t color){
    return (color >> 8) & 0xff;
}
uint8_t getBlue(uint32_t color){
    return color & 0xff;
}

//   __   ____ _____  _     ___        _        _     ___   ___   ___
//  ( (` | |_   | |  | | | | |_)     _|_)      | |   / / \ / / \ | |_)
//  _)_) |_|__  |_|  \_\_/ |_|       (|__7     |_|__ \_\_/ \_\_/ |_|
void setup() {
    strip.begin();
    strip.show();
    Particle.subscribe("StartButton",readySetGo);
    Particle.subscribe("LaneStop",lanePressed);
}





void loop() {


    //allOn(red);
    //rainbow(1000,10000);

    /*wipe(orange, 20, up);
    wipe(black, 20, up);

    wipe(green, 20, down);
    wipe(black, 20, down);*/

    wipe(white, 20, in);
    //wipe(black, 20, in);

    wipe(blue, 20, out);
    //wipe(black, 20, out);

    /*fadeIn(cyan, 4);
    fadeOut(cyan, 8);

    allOn(magenta);
    delay(250);
    flash(yellow, 50, 750);
    flash(white, 100, 750);
    flash(yellow, 10, 750);
    wipe(black, 20, out);
    delay(2000);*/

}

//   ___    __    __    ____      __   ____  ___    _     ____  _      __    ____  __
//  | |_)  / /\  / /`  | |_      ( (` | |_  / / \  | | | | |_  | |\ | / /`  | |_  ( (`
//  |_| \ /_/--\ \_\_, |_|__     _)_) |_|__ \_\_\\ \_\_/ |_|__ |_| \| \_\_, |_|__ _)_)

void readySetGo(const char *event, const char *data){
    fadeOut(red,3);
    fadeOut(red,3);
    fadeOut(yellow,3);
    flash(green, 50, 500);
    allOn(green);
    delay(1000);
}

void lanePressed(const char *event, const char *data){
    flash(yellow, 50, 500);
}

void race(){

}

void oneMinuteRemaining(){

}

//    __    _      _   _       __   _____  _   ___   _      __
//   / /\  | |\ | | | | |\/|  / /\   | |  | | / / \ | |\ | ( (`
//  /_/--\ |_| \| |_| |_|  | /_/--\  |_|  |_| \_\_/ |_| \| _)_)

void rainbow(uint8_t wait, unsigned long duration) {
    uint16_t i, j;
    unsigned long endTime = millis() + duration;
    while(millis() < endTime){
        for(j=0; j < 256; j++) {
            for(i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i, Wheel((i+j) & 255));
            }
            strip.show();
            delay(wait/strip.numPixels());
        }
    }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    if(WheelPos < 85) {
        return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    } else if(WheelPos < 170) {
        WheelPos -= 85;
        return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else {
        WheelPos -= 170;
        return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
}




// Fill the dots one after the other with a color
void wipe(uint32_t color, uint8_t wait, uint8_t direction) {
    switch (direction) {
        case up:
            wipeUp(color, wait);
            break;
        case down:
            wipeDown(color, wait);
            break;
        case in:
            wipeIn(color, wait);
            break;
        case out:
            wipeOut(color,wait);
            break;
    }
}
void wipeUp(uint32_t color, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, color);
        strip.show();
        delay(wait);
    }
}
void wipeDown(uint32_t color, uint8_t wait) {
    for(uint16_t i=strip.numPixels(); i>0; i--) {
        strip.setPixelColor(i-1, color);
        strip.show();
        delay(wait);
    }
}
void wipeIn(uint32_t color, uint8_t wait) {
    uint8_t middle = strip.numPixels()/2;
    for (uint8_t i=0; i<middle; i++){
        strip.setPixelColor(i, color);
        strip.setPixelColor(strip.numPixels() - 1 - i, color);
        strip.show();
        delay(wait);
    }

}
void wipeOut(uint32_t color, uint8_t wait) {
    uint8_t middle = strip.numPixels()/2;
    for (uint8_t i=0; i<=middle; i++){
        strip.setPixelColor(middle - i, color);
        strip.setPixelColor(middle + i, color);
        strip.show();
        delay(wait);
    }
}





void fadeIn(uint32_t color, uint8_t wait) {
    uint8_t r = getRed(color);
    uint8_t g = getGreen(color);
    uint8_t b = getBlue(color);
    for(int j = 0; j < 256 ; j++){
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i, Adafruit_NeoPixel::Color(map(j,0,255,0,r),map(j,0,255,0,g),map(j,0,255,0,b)));
        }
        delay(wait);
        strip.show();
    }
}
void fadeOut(uint32_t color, uint8_t wait) {
    uint8_t r = getRed(color);
    uint8_t g = getGreen(color);
    uint8_t b = getBlue(color);
    for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=0; i<strip.numPixels(); i++) {
          strip.setPixelColor(i, Adafruit_NeoPixel::Color(map(j,0,255,0,r),map(j,0,255,0,g),map(j,0,255,0,b)));
        }
        delay(wait);
        strip.show();
    }
}
void pulse(uint32_t color, uint8_t wait) {
    fadeIn(color, wait);
    fadeOut(color, wait);
}

void allOn(uint32_t color){
    for(int i = 0; i<strip.numPixels(); i++){
        strip.setPixelColor(i,color);
    }
    strip.show();
}

void flash(uint32_t color, uint8_t cycle, unsigned long duration) {
    unsigned long endTime = millis()+duration;

    while (millis() < endTime){
        allOn(color);
        delay(cycle);
        allOn(black);
        delay(cycle);
    }
}

















void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength) {

  if(whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while(true){
    for(int j=0; j<256; j++) {
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
          strip.setPixelColor(i, gamma[j],gamma[j],gamma[j] );
        }
        else{
          strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }

      }

      if(millis() - lastTime > whiteSpeed) {
        head++;
        tail++;
        if(head == strip.numPixels()){
          loopNum++;
        }
        lastTime = millis();
      }

      if(loopNum == loops) return;

      head%=strip.numPixels();
      tail%=strip.numPixels();
        strip.show();
        delay(wait);
    }
  }

}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// void marquis(uint8_t wait, uint8_t color1, uint8_t color1pix, uint8_t color2, uint8_t color2pix, int direction) {
//     /*
//     * A scrolling marquis
//     * specify two colors and the number of pixels for each color
//     * specify which direction it should scroll and at what speed (ms)
//     */
//     for (int j=0; j<scrollWidth; j++){
//         for(int i=0; i<PIXEL_COUNT; i++){
//             if (i % scrollWidth == 0) {
//                 strip.setPixelColor(i, color);
//             } else {

//             }

//         }
//     }

// }
