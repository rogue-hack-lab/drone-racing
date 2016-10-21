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
*   Adafruit LCDBackpack (bkobkobko remix)  https://github.com/bkobkobko/SparkCoreLibraries/tree/master/Adafruit
* Authors:
*   Kevin Conner            kevin.r.conner@gmail.com
*/

#include "Button.h"


#define LCD_PIN D4
#define LANES 3

#define START_BTN_PIN D2
#define LANE_1_BTN_PIN D3
#define LANE_2_BTN_PIN D4
#define LANE_3_BTN_PIN D5
Button startBtn = Button(START_BTN_PIN, BUTTON_PULLDOWN_INTERNAL);
Button laneBtn[LANES] = {
  Button(LANE_1_BTN_PIN, BUTTON_PULLDOWN_INTERNAL),
  Button(LANE_2_BTN_PIN, BUTTON_PULLDOWN_INTERNAL),
  Button(LANE_3_BTN_PIN, BUTTON_PULLDOWN_INTERNAL)
};


void setup() {

}

void loop() {

    if (startBtn.uniquePress()){
        Particle.publish("StartButton","Start");
    }

    for (int i; i < LANES; i++){
      if (laneBtn[i].uniquePress()){
          Particle.publish("LaneButton",(String)(i));
      }
    }

    delay(50);

}
