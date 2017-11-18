/*
 * Project disneylandRailroad
 * Description:
 * Author:
 * Date:
 */
#include <neopixel.h>

#define PIXEL_COUNT 144
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B
#define TRAIN1_COLOR 255,255,0
#define TRAIN2_COLOR 0,255,255
#define TRAIN3_COLOR 255,0,255
#define TRAIN_OFF 0,0,0
#define TRAIN_LENGTH 8

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = 75;

int TRAIN1 = 0;
int TRAIN1_OFF = TRAIN1 - TRAIN_LENGTH;
int TRAIN2 = 48;
int TRAIN2_OFF = TRAIN2 - TRAIN_LENGTH;
int TRAIN3 = 96;
int TRAIN3_OFF = TRAIN3 - TRAIN_LENGTH;

void setup() {
  strip.begin();
  strip.show();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    strip.setPixelColor(TRAIN1, TRAIN1_COLOR);
    strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF);
    strip.setPixelColor(TRAIN2, TRAIN2_COLOR);
    strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF);
    strip.setPixelColor(TRAIN3, TRAIN3_COLOR);
    strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF);
    strip.setBrightness(1);
    strip.show();

    TRAIN1 ++;
    TRAIN1_OFF ++;
    TRAIN2 ++;
    TRAIN2_OFF ++;
    TRAIN3 ++;
    TRAIN3_OFF ++;
    strip.show();

    if (TRAIN1 > PIXEL_COUNT) {
      TRAIN1 = 0;
    }
    if (TRAIN1_OFF > PIXEL_COUNT) {
      TRAIN1_OFF = 0;
    }
    if (TRAIN2 > PIXEL_COUNT) {
      TRAIN2 = 0;
    }
    if (TRAIN2_OFF > PIXEL_COUNT) {
      TRAIN2_OFF = 0;
    }
    if (TRAIN3 > PIXEL_COUNT) {
      TRAIN3 = 0;
    }
    if (TRAIN3_OFF > PIXEL_COUNT) {
      TRAIN3_OFF = 0;
    }

    strip.show();
    delay(waitTime);
}
