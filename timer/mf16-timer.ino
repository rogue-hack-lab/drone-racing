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
#include "Adafruit_LEDBackpack.h"

void segmentTest(Adafruit_7segment matrix);

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

Adafruit_7segment lcd[LANES];

uint8_t raceState;
enum raceStates {
  rsQuiet,      //do nothing
  rsInit,       //start up state
  rsDemo,       //while there is no race going
  rsReadySetGo, //when a race is about to begin
  rsRacing,     //while a race is active
  rsFinish,     //when a lane finishes
  rsComplete    //when all lanes are finished
};

uint32_t counter[LANES];
bool laneActive[LANES];
uint32_t startTime = 0;

//   __   ____ _____  _     ___        _        _     ___   ___   ___
//  ( (` | |_   | |  | | | | |_)     _|_)      | |   / / \ / / \ | |_)
//  _)_) |_|__  |_|  \_\_/ |_|       (|__7     |_|__ \_\_/ \_\_/ |_|
void setup() {
  for (int i; i < LANES; i++){
    lcd[i] = Adafruit_7segment();
  }

  lcd[0].begin(0x70);
  lcd[1].begin(0x71);
  lcd[2].begin(0x72);

  for (int i; i < LANES; i++){
    lcd[i].writeDigitNum(0, 0, true);
    lcd[i].writeDigitNum(1, 0, false);
    lcd[i].writeDigitNum(3, 0, true);
    lcd[i].writeDigitNum(4, 0, false);
    lcd[i].writeDisplay();
  }
}

void loop() {
    doStartButton();
    doLaneButtons();
    delay(10);
}




void doStartButton() {
  if (startBtn.uniquePress()){
      Particle.publish("raceState",(String)(rsReadySetGo));
      startRace();
      delay(2000);
      while (startBtn.isPressed()){}
      Particle.publish("raceState",(String)(rsRacing));
      startTime = millis();
  }
}

void doLaneButtons() {
  for (int i; i < LANES; i++){
    if (laneActive[i]) {
      formatTime(i, millis() - startTime);
      //lcd[i].println(counter[i]);
      //lcd[i].writeDisplay();
      if (laneBtn[i].uniquePress()){
          Particle.publish("raceState",(String)(rsFinish));
          Particle.publish("laneSelect",(String)(i));
          laneActive[i] = !laneActive[i];
      }
    }
  }
}

//reset lane counters to zero
void startRace(){
  for (int i; i < LANES; i++){
    counter[i] = 0;
    laneActive[i] = true;
    lcd[i].writeDigitNum(0, 0, true);
    lcd[i].writeDigitNum(1, 0, false);
    lcd[i].writeDigitNum(3, 0, true);
    lcd[i].writeDigitNum(4, 0, false);
    lcd[i].writeDisplay();
  }
}

void formatTime(int lane, uint32_t milliseconds){
  uint32_t minutes = (uint8_t)((milliseconds / 60000) % 10);
  milliseconds %= 60000;
  uint32_t seconds = (uint8_t)(milliseconds / 1000);
  milliseconds %=  1000;
  uint32_t tenths  = (uint8_t)((milliseconds / 100) % 10);

  lcd[lane].writeDigitNum(0, minutes, true);
  lcd[lane].writeDigitNum(1, (int) seconds / 10, false);
  lcd[lane].writeDigitNum(3, seconds % 10, true);
  lcd[lane].writeDigitNum(4, tenths, false);
  lcd[lane].writeDisplay();
}
