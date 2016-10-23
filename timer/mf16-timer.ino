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

void setup() {
  for (int i; i < LANES; i++){
    lcd[i] = Adafruit_7segment();
  }

  lcd[0].begin(0x70);
  lcd[1].begin(0x71);
  lcd[2].begin(0x72);

  for (int i; i < LANES; i++){
    lcd[i].println(i + 1);
    lcd[i].writeDisplay();
  }
}

uint16_t counter[LANES];
bool laneActive[LANES];
uint32_t startTime = 0;

void loop() {

    doStartButton();

    doLaneButtons();

    delay(10);

}

void doStartButton() {
  if (startBtn.uniquePress()){
      Particle.publish("StartButton","Start");
      startTime = millis();
      startRace();
  }
}

void doLaneButtons() {
  for (int i; i < LANES; i++){
    if (laneActive[i]) {
      counter[i] = formatTime(millis() - startTime);
      lcd[i].println(counter[i]);
      lcd[i].writeDisplay();
      if (laneBtn[i].uniquePress()){
          Particle.publish("LaneStop",(String)(i));
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
    lcd[i].println(counter[i]);
    lcd[i].writeDisplay();
  }
}

uint16_t formatTime(uint16_t milliseconds){
  uint16_t minutes = (int) (((milliseconds / (1000 * 60)) % 10) * 1000);
  uint16_t seconds = (int) ((milliseconds / 1000) * 10);
  uint16_t tenths  = (int) ((milliseconds / 100) % 10);
  return minutes + seconds + tenths;
}





// for reference and testing
void segmentTest(Adafruit_7segment matrix) {
  /*// try to print a number thats too long
  matrix.print(10000, DEC);
  matrix.writeDisplay();
  delay(500);

  // print a hex number
  matrix.print(0xBEEF, HEX);
  matrix.writeDisplay();
  delay(500);

  // print a floating point
  matrix.print(12.34);
  matrix.writeDisplay();
  delay(500);

  // print with print/println
  for (uint16_t counter = 0; counter < 9999; counter++) {
    matrix.println(counter);
    matrix.writeDisplay();
    delay(10);
  }*/

  // method #2 - draw each digit
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t counter = 0; counter < 9999; counter ++) {
    matrix.writeDigitNum(0, (counter / 1000), drawDots);
    matrix.writeDigitNum(1, (counter / 100) % 10, drawDots);
    matrix.drawColon(drawDots);
    matrix.writeDigitNum(3, (counter / 10) % 10, drawDots);
    matrix.writeDigitNum(4, counter % 10, drawDots);

    blinkcounter+=50;
    if (blinkcounter < 500) {
      drawDots = false;
    } else if (blinkcounter < 1000) {
      drawDots = true;
    } else {
      blinkcounter = 0;
    }
    matrix.writeDisplay();
    delay(10);
  }
}
