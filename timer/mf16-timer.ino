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

#define START_BTN_PIN D0
#define LANE_1_BTN_PIN D1
#define LANE_2_BTN_PIN D2
#define LANE_3_BTN_PIN D3

#define LCD_PIN D4


Button btnS = Button(START_BTN_PIN, BUTTON_PULLDOWN_INTERNAL);
Button btn1 = Button(LANE_1_BTN_PIN, BUTTON_PULLDOWN_INTERNAL);
Button btn2 = Button(LANE_2_BTN_PIN, BUTTON_PULLDOWN_INTERNAL);
Button btn3 = Button(LANE_3_BTN_PIN, BUTTON_PULLDOWN_INTERNAL);

void setup() {

}

void loop() {

    if (btnS.uniquePress()){
        Particle.publish("btnS","isPressed");
    }
    if (btn1.uniquePress()){
        Particle.publish("btn1","isPressed");
    }
    if (btn2.uniquePress()){
        Particle.publish("btn2","isPressed");
    }
    if (btn3.uniquePress()){
        Particle.publish("btn3","isPressed");
    }

    delay(50);

}
