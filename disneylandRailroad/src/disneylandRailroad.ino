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

#define TRAIN_COLOR 255,255,255
#define TRAIN_OFF_COLOR 0,0,0
#define TRAIN_LENGTH 8

#define MAINST 36
#define NEWORLEANS 72
#define TOONTOWN 108
#define TOMORROWLAND 144

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = Time.second() + 12.5;

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
    SPARKLE(0,0,0, 0);
  }
}

// loop() runs over and over again, as quickly as it can execute.

void loop() {
    TRAIN_CYCLE();
}

void TRAIN_CYCLE(){
  strip.setPixelColor(TRAIN1_POSITION, TRAIN_COLOR);
  strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN2_POSITION, TRAIN_COLOR);
  strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN3_POSITION, TRAIN_COLOR);
  strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF_COLOR);
  strip.setPixelColor(TRAIN4_POSITION, TRAIN_COLOR);
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

  if (TRAIN1_POSITION > PIXEL_COUNT) {
    TRAIN1_POSITION = 0;
  }
  if (TRAIN1_OFF > PIXEL_COUNT) {
    TRAIN1_OFF = 0;
  }
  if (TRAIN2_POSITION > PIXEL_COUNT) {
    TRAIN2_POSITION = 0;
  }
  if (TRAIN2_OFF > PIXEL_COUNT) {
    TRAIN2_OFF = 0;
  }
  if (TRAIN3_POSITION > PIXEL_COUNT) {
    TRAIN3_POSITION = 0;
  }
  if (TRAIN3_OFF > PIXEL_COUNT) {
    TRAIN3_OFF = 0;
  }
  if (TRAIN4_OFF > PIXEL_COUNT) {
    TRAIN4_OFF = 0;
  }
  strip.show();

  delay(waitTime);
}

void SPARKLE(byte red, byte green, byte blue, int SpeedDelay) {
  int SPARKLE_PIXEL = random(PIXEL_COUNT);
  strip.setPixelColor(SPARKLE_PIXEL,red,green,blue);
  strip.show();
  delay(SpeedDelay);
  strip.setPixelColor(SPARKLE_PIXEL,0,0,0);
}
