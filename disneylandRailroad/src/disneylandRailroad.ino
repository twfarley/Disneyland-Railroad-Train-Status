/*
 * Project disneylandRailroad
 * Description: Loops LEDs around a strip to simulate the trains at Disneyland.
 * Author: Tommy W Farley
 * Date: November, 2017
 */
#include <neopixel.h>

#define PIXEL_COUNT 144
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B

#define TRAIN_ALTCOLOR 255,220,94
#define TRAIN_OFF_COLOR 0,0,0
#define TRAIN_LENGTH 8

#define MAINST 36
#define NEWORLEANS 72
#define TOONTOWN 108
#define TOMORROWLAND 144

#define JAN 173,204,255 //light blue
#define FEB 255,160,226 //pink
#define MAR 44,237,37 //clover green
#define APR 0,255,174 //teal
#define MAY 255,0,255 //magenta
#define JUN 0,255,100 //light green
#define JUL 0,255,0 //green
#define AUG 255,200,0 //yellow
#define SEP 255,180,0 //light orange
#define OCT 255,110,0 //orange
#define NOV 150,0,255 //purple
#define DEC 255,0,0 //red

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int WAITTIME = Time.second() + 12.5;

uint32_t TRAIN_COLOR = strip.Color(255, 255, 255);

int CURRENT_MONTH = Time.month();

int TRAIN1_POSITION = MAINST;
int TRAIN1_OFF = TRAIN1_POSITION - TRAIN_LENGTH;
int TRAIN2_POSITION = NEWORLEANS;
int TRAIN2_OFF = TRAIN2_POSITION - TRAIN_LENGTH;
int TRAIN3_POSITION = TOONTOWN;
int TRAIN3_OFF = TRAIN3_POSITION - TRAIN_LENGTH;
int TRAIN4_POSITION = TOMORROWLAND;
int TRAIN4_OFF = TRAIN4_POSITION - TRAIN_LENGTH;

void setup() {
  strip.begin();
  strip.show();
  if(Time.isValid() != true){
    Particle.syncTime();
    waitUntil(Particle.syncTimeDone);
  }
  Time.zone(-8);
  int SPARKLE_OFF_TIME = (Time.second() + 3);
  while (Time.second() < SPARKLE_OFF_TIME) {
    SPARKLE(0,0,0,0);
  }
}

// loop() runs over and over again, as quickly as it can execute.

void loop() {
    TRAIN_CYCLE();
}

void TRAIN_CYCLE(){
  if (CURRENT_MONTH == 1) {
    TRAIN_COLOR = JAN;
  } //if CURRENT_MONTH doesn't work then just use Time.month() here.
  if (CURRENT_MONTH == 2) {
    TRAIN_COLOR = FEB;
  }
  if (CURRENT_MONTH == 3) {
    TRAIN_COLOR = MAR;
  }
  if (CURRENT_MONTH == 4) {
    TRAIN_COLOR = APR;
  }
  if (CURRENT_MONTH == 5) {
    TRAIN_COLOR = MAY;
  }
  if (CURRENT_MONTH == 6) {
    TRAIN_COLOR = JUN;
  }
  if (CURRENT_MONTH == 7) {
    TRAIN_COLOR = JUL;
  }
  if (CURRENT_MONTH == 8) {
    TRAIN_COLOR = AUG;
  }
  if (CURRENT_MONTH == 9) {
    TRAIN_COLOR = SEP;
  }
  if (CURRENT_MONTH == 10) {
    TRAIN_COLOR = OCT;
  }
  if (CURRENT_MONTH == 11) {
    TRAIN_COLOR = NOV;
  }
  if (CURRENT_MONTH == 12) {
    TRAIN_COLOR = DEC;
  }

  strip.setPixelColor(TRAIN1_POSITION, TRAIN_COLOR);
  strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN2_POSITION, TRAIN_ALTCOLOR);
  strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN3_POSITION, TRAIN_COLOR);
  strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN4_POSITION, TRAIN_ALTCOLOR);
  strip.setPixelColor(TRAIN4_OFF, TRAIN_OFF_COLOR);
  strip.setBrightness(1);
  strip.show();

  TRAIN1_POSITION ++;
  TRAIN1_OFF ++;
  TRAIN2_POSITION ++;
  TRAIN2_OFF ++;
  TRAIN3_POSITION ++;
  TRAIN3_OFF ++;
  TRAIN4_POSITION ++;
  TRAIN4_OFF ++;
  strip.show();

  if (TRAIN1_POSITION > PIXEL_COUNT - 1) {
    TRAIN1_POSITION = 0;
  }
  if (TRAIN1_OFF > PIXEL_COUNT - 1) {
    TRAIN1_OFF = 0;
  }
  if (TRAIN2_POSITION > PIXEL_COUNT - 1) {
    TRAIN2_POSITION = 0;
  }
  if (TRAIN2_OFF > PIXEL_COUNT - 1) {
    TRAIN2_OFF = 0;
  }
  if (TRAIN3_POSITION > PIXEL_COUNT - 1) {
    TRAIN3_POSITION = 0;
  }
  if (TRAIN3_OFF > PIXEL_COUNT - 1) {
    TRAIN3_OFF = 0;
  }
  if (TRAIN4_OFF > PIXEL_COUNT - 1) {
    TRAIN4_OFF = 0;
  }
  strip.show();

  delay(WAITTIME);
}

void SPARKLE(byte red, byte green, byte blue, int SpeedDelay) {
  int SPARKLE_PIXEL = random(PIXEL_COUNT);
  strip.setPixelColor(SPARKLE_PIXEL,red,green,blue);
  strip.show();
  delay(SpeedDelay);
  strip.setPixelColor(SPARKLE_PIXEL,0,0,0);
}
