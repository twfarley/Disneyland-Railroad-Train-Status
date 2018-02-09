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

#define TRAIN_OFF_COLOR 0,0,0
#define TRAIN_LENGTH 1
//number of pixels each train should be

#define LOOPTIME 1800
//time it takes to go around the track in seconds

#define NEWORLEANS 45
#define TOONTOWN 85
#define TOMORROWLAND 123
#define MAINST 15
//positions of each station

#define OPENTIME 8
#define CLOSETIME 21
#define SPARKLE_RUNTIME 30
//hours that the animations should start and stop.
//runtime is how long the fireworks (sparkle) will run

#define JAN 173,204,255 //light blue
#define FEB 255,72,72 //pink
#define MAR 44,255,37 //clover green
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

int WAITTIME = Time.second() + LOOPTIME;
// 30 minutes to get around the whole track
// 30 minutes * 60 seconds = 1800 seconds

uint32_t TRAIN_COLOR = strip.Color(255, 255, 255);
uint32_t TRAIN_ALTCOLOR = strip.Color(255, 255, 255);
//sets the trains to white as default

int CURRENT_MONTH = Time.month();
int CURRENT_DAY = Time.day();
int DAYTIME = Time.hour();

int TRAIN1_POSITION = MAINST;
int TRAIN1_OFF = TRAIN1_POSITION - TRAIN_LENGTH;
int TRAIN2_POSITION = NEWORLEANS;
int TRAIN2_OFF = TRAIN2_POSITION - TRAIN_LENGTH;
int TRAIN3_POSITION = TOONTOWN;
int TRAIN3_OFF = TRAIN3_POSITION - TRAIN_LENGTH;
int TRAIN4_POSITION = TOMORROWLAND;
int TRAIN4_OFF = TRAIN4_POSITION - TRAIN_LENGTH;

void setup() {
  //Particle.syncTime();
  Time.zone(-8);
  strip.begin();
  strip.show();
}

// loop() runs over and over again, as quickly as it can execute.

void loop() {
  if (CURRENT_MONTH == 2 && CURRENT_DAY == 9){
    RAINBOW(5);
  } else {
    TRAIN_CYCLE();
    SPARKLE();
  }
}

void TRAIN_CYCLE(){
  strip.setBrightness(200);
  if (CURRENT_MONTH == 1) {
    TRAIN_ALTCOLOR = strip.Color(JAN);
  }
  if (CURRENT_MONTH == 2) {
    TRAIN_ALTCOLOR = strip.Color(FEB);
    TRAIN_COLOR = strip.Color(DEC);
  }
  if (CURRENT_MONTH == 3) {
    TRAIN_ALTCOLOR = strip.Color(MAR);
  }
  if (CURRENT_MONTH == 4) {
    TRAIN_ALTCOLOR = strip.Color(APR);
  }
  if (CURRENT_MONTH == 5) {
    TRAIN_ALTCOLOR = strip.Color(MAY);
  }
  if (CURRENT_MONTH == 6) {
    TRAIN_ALTCOLOR = strip.Color(JUN);
  }
  if (CURRENT_MONTH == 7) {
    TRAIN_ALTCOLOR = strip.Color(JUL);
  }
  if (CURRENT_MONTH == 8) {
    TRAIN_ALTCOLOR = strip.Color(AUG);
  }
  if (CURRENT_MONTH == 9) {
    TRAIN_ALTCOLOR = strip.Color(SEP);
  }
  if (CURRENT_MONTH == 10) {
    TRAIN_ALTCOLOR = strip.Color(OCT);
  }
  if (CURRENT_MONTH == 11) {
    TRAIN_ALTCOLOR = strip.Color(NOV);
  }
  if (CURRENT_MONTH == 12) {
    TRAIN_ALTCOLOR = strip.Color(DEC);
    TRAIN_COLOR = strip.Color(MAR);
  }

  if (Time.hour() >= OPENTIME && Time.hour() < CLOSETIME) {
    strip.setPixelColor(TRAIN1_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN2_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN3_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN4_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN4_OFF, TRAIN_OFF_COLOR);
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
    if (TRAIN4_POSITION > PIXEL_COUNT - 1) {
      TRAIN4_POSITION = 0;
    }
    if (TRAIN4_OFF > PIXEL_COUNT - 1) {
      TRAIN4_OFF = 0;
    }
    strip.show();
    delay(WAITTIME);
  }
}

void SPARKLE() {
  int SPARKLE_PIXEL = random(PIXEL_COUNT);
  int RSPARKLE = random(255);
  int GSPARKLE = random(255);
  int BSPARKLE = random(255);
  int BLOOMTIME = random(50);
  if (Time.hour() == CLOSETIME && Time.minute() <= SPARKLE_RUNTIME) {
    for (int i=180; i<255; i++) {
       strip.setBrightness(i);
       strip.setPixelColor(SPARKLE_PIXEL,RSPARKLE,GSPARKLE,BSPARKLE);
       strip.show();
       delay(2);
     }
    for (int i=255; i>0; i--) {
      strip.setBrightness(i);
      //strip.setPixelColor(SPARKLE_PIXEL,i,0,0);
      strip.show();
      delay(8);
    }
    delay(BLOOMTIME);
    strip.setPixelColor(SPARKLE_PIXEL,0,0,0);
  }
}

void RAINBOW(int SpeedDelay) {
  byte *c;
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< PIXEL_COUNT; i++) {
      c=Wheel(((i * 256 / PIXEL_COUNT) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
