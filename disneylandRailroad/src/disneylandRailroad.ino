/*
 * Project Disneyland Railroad Map
 * Description: Loops LEDs around an LED strip to simulate the trains at Disneyland.
 * Author: Tommy W Farley
 * Date: November, 2017
 */
#include <neopixel.h>

#define PIXEL_COUNT 144
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B

#define TRAIN_OFF_COLOR 0,0,0
#define TRAIN_LENGTH 4
//number of pixels each train should be

#define LOOPTIME 300
//time it takes to go around the track in seconds

int WAITTIME = Time.second() + LOOPTIME;
// 30 minutes to get around the whole track
// 30 minutes * 60 seconds = 1800 seconds

#define NEWORLEANS 45
#define TOONTOWN 85
#define TOMORROWLAND 123
#define MAINST 15
//pixel number positions of each station

#define JAN 175,200,250 //light blue
#define FEB 250,75,75 //pink
#define MAR 50,250,50 //clover green
#define APR 0,250,175 //teal
#define MAY 250,0,250 //magenta
#define JUN 0,250,100 //light green
#define JUL 0,250,0 //green
#define AUG 250,250,0 //yellow
#define SEP 250,150,0 //orange
#define OCT 150,0,250 //purple
#define NOV 250,100,0 //orange
#define DEC 250,0,0 //red

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);



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
    Serial.begin();
    Time.zone(-8);
    strip.begin();
    strip.show();
    Particle.syncTime();
    Particle.function("trainon", controlTrain);
}

//HomeBridge implementation
int controlTrain(String command) {
    if (command=="on" || command=="1=1" || command == "1") {
        Particle.publish("On");
        strip.setBrightness(255);
        SET_COLORS();
        strip.show();
    } else if (command=="off" || command=="1=0" || command =="0") {
        Particle.publish("Off");
        strip.setBrightness(0);
        strip.show();
    }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    TRAIN_CYCLE();
}

int SET_COLORS(){
    if (CURRENT_MONTH == 1) {
        TRAIN_ALTCOLOR = strip.Color(JAN);
        Particle.publish("Running Trains with January");
    }
    if (CURRENT_MONTH == 2) {
        TRAIN_ALTCOLOR = strip.Color(FEB);
        TRAIN_COLOR = strip.Color(DEC);
        Particle.publish("Running Trains with February");
    }
    if (CURRENT_MONTH == 3) {
        TRAIN_ALTCOLOR = strip.Color(MAR);
        Particle.publish("Running Trains with March");
    }
    if (CURRENT_MONTH == 4) {
        TRAIN_ALTCOLOR = strip.Color(APR);
        Particle.publish("Running Trains with April");
    }
    if (CURRENT_MONTH == 5) {
        TRAIN_ALTCOLOR = strip.Color(MAY);
        Particle.publish("Running Trains with May");
    }
    if (CURRENT_MONTH == 6) {
        TRAIN_ALTCOLOR = strip.Color(JUN);
        Particle.publish("Running Trains with June");
    }
    if (CURRENT_MONTH == 7) {
        TRAIN_ALTCOLOR = strip.Color(JUL);
        Particle.publish("Running Trains with July");
    }
    if (CURRENT_MONTH == 8) {
        TRAIN_ALTCOLOR = strip.Color(AUG);
        Particle.publish("Running Trains with August");
    }
    if (CURRENT_MONTH == 9) {
        TRAIN_ALTCOLOR = strip.Color(SEP);
        Particle.publish("Running Trains with September");
    }
    if (CURRENT_MONTH == 10) {
        TRAIN_ALTCOLOR = strip.Color(OCT);
        TRAIN_COLOR = strip.Color(MAR);
        Particle.publish("Running Trains with October");
    }
    if (CURRENT_MONTH == 11) {
        TRAIN_ALTCOLOR = strip.Color(NOV);
        TRAIN_COLOR = strip.Color(AUG);
        Particle.publish("Running Trains with November");
    }
    if (CURRENT_MONTH == 12) {
        TRAIN_ALTCOLOR = strip.Color(DEC);
        TRAIN_COLOR = strip.Color(MAR);
        Particle.publish("Running Trains with December");
    }
    strip.setPixelColor(TRAIN1_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN2_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN3_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN4_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN4_OFF, TRAIN_OFF_COLOR);
    strip.show();
}

void TRAIN_CYCLE(){
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
