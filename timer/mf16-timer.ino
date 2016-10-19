/*
* Rogue Hack Lab
* Rogue Valley Mini Maker Faire - 2016
* Micro Drone Racing
* 3 Lane Race Timer
* Hardware:
*   Particle Proton         https://www.particle.io/products/hardware/photon-wifi-dev-kit
*   Adafruit NeoPixel       https://www.adafruit.com/products/1461
* Libraries:
*   Arduino HAL button Lib  http://playground.arduino.cc/Code/Button (adapted)
*   Adafruit NeoPixel       https://github.com/adafruit/Adafruit_NeoPixel
* Authors: 
*   Kevin Conner            kevin.r.conner@gmail.com
*/

#include "Button.h"

#define START_BTN D0
#define LANE_1_BTN D1
#define LANE_2_BTN D2
#define LANE_3_BTN D3


void setup() {
    
    pinMode(START_BTN, INPUT_PULLDOWN);
    pinMode(LANE_1_BTN, INPUT_PULLDOWN);
    pinMode(LANE_2_BTN, INPUT_PULLDOWN);
    pinMode(LANE_3_BTN, INPUT_PULLDOWN);
    
    
    
}

void loop() {
    
    if (digitalRead(START_BTN) == HIGH){
        Particle.publish("btn","0");
    }
    if (digitalRead(LANE_1_BTN) == HIGH){
        Particle.publish("btn","1");
    }
    if (digitalRead(LANE_2_BTN) == HIGH){
        Particle.publish("btn","2");
    }
    if (digitalRead(LANE_3_BTN) == HIGH){
        Particle.publish("btn","3");
    }
    delay(50);
    
}