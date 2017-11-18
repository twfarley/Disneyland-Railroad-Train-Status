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
#define TRAIN2_COLOR 0,0,0
#define TRAIN_LENGTH 8

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int waitTime = 25;
int i;
int j;
int TRAIN1 = 0;
int TRAIN2 = 136;
//void spin(int R, int G, int B);

void setup() {
  strip.begin();
  strip.show();
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    //spin (TRAIN_COLOR);
    strip.setPixelColor(TRAIN1, TRAIN1_COLOR);
    strip.setPixelColor(TRAIN2, TRAIN2_COLOR);
    strip.setBrightness(8);
    strip.show();

    TRAIN1 ++;
    TRAIN2 ++;

    if (TRAIN1 > PIXEL_COUNT) {
      TRAIN1 = 0;
    }
    if (TRAIN2 > PIXEL_COUNT) {
      TRAIN2 = 0;
    }
    strip.show();
}

/*void spin(int R, int G, int B) {
    for(i=0; i < PIXEL_COUNT; i++) {
        strip.setPixelColor(i, R,G,B);
        strip.setBrightness(8);
        strip.show();
        delay(waitTime);
    }
    for(j=0; j < PIXEL_COUNT; j++) {
        strip.setPixelColor(j, 0,0,0);
        strip.show();
        delay(waitTime);
    }
}*/
