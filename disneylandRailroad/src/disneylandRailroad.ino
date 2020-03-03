#include <neopixel.h>

#define PIXEL_COUNT 144
#define PIXEL_PIN D6
#define PIXEL_TYPE WS2812B

#define TRAIN_LENGTH 18
//number of pixels each train should be
//144 / 8 (each color plus each off) = 18

#define LOOPTIME 30
//time in seconds it takes to go around the track

#define MAINST 18
#define NEWORLEANS 54
#define TOONTOWN 90
#define TOMORROWLAND 126
//pixel number positions of each station

#define LIGHTBLUE 50,200,225 //light blue
#define PINK 250,75,75 //pink
#define GREEN 50,250,50 //clover green
#define TEAL 0,250,175 //teal
#define MAGENTA 250,0,250 //magenta
#define LIGHTGREEN 0,250,100 //light green
#define YELLOW 250,250,0 //yellow
#define ORANGE 250,150,50 //orange
#define PURPLE 150,0,250 //purple
#define BLUE 0,0,250 //blue
#define RED 250,0,0 //red
#define WHITE 250,250,250 //white
#define OFF 0,0,0 // black or off

#define ONE_DAY_MILLIS (24 * 60 * 60 * 1000)
unsigned long lastSync = millis();

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

uint32_t TRAIN_COLOR = strip.Color(WHITE);
uint32_t TRAIN_ALTCOLOR = strip.Color(WHITE);
uint32_t TRAIN_OFF_COLOR = strip.Color(OFF);

//sets the trains to white as default

int CURRENT_MONTH = Time.month();

int TRAIN1_POSITION = MAINST;
int TRAIN1_OFF = TRAIN1_POSITION - TRAIN_LENGTH;
int TRAIN2_POSITION = NEWORLEANS;
int TRAIN2_OFF = TRAIN2_POSITION - TRAIN_LENGTH;
int TRAIN3_POSITION = TOONTOWN;
int TRAIN3_OFF = TRAIN3_POSITION - TRAIN_LENGTH;
int TRAIN4_POSITION = TOMORROWLAND;
int TRAIN4_OFF = TRAIN4_POSITION - TRAIN_LENGTH;
//setting start positions for trains

String STATE =  String("1");

void setup() {
    Serial.begin();
    strip.begin();
    Time.zone(-8);
    rainbowCycle(0);
    CONTROL_TRAIN("1");
    SET_COLORS();
    strip.show();
    Particle.function("HomeKitControl", CONTROL_TRAIN);
    Particle.function("Debug Month", DEBUG_MONTH);
    Particle.variable("HomeKitState", STATE);
    Particle.variable("HomeKitActual", CONTROL_TRAIN);
    Particle.variable("Current Month", CURRENT_MONTH);
}

//Publishes a function to Particle to control with HomeBridge
int CONTROL_TRAIN(String command) {
    if (command == "1") {
        Particle.publish("On");
        strip.setBrightness(250);
        STATE = command;
        strip.show();
    } if (command =="0") {
        Particle.publish("Off");
        STATE = command;
        strip.setBrightness(0);
        strip.show();
    } if (command == "?" && STATE == "1") {
        command = STATE;
        Particle.publish("On");
        strip.setBrightness(250);
        strip.show();
    } else if (command == "?" && STATE == "0") {
        Particle.publish("Off");
        strip.setBrightness(0);
        strip.show();
    }
}

void DEBUG_MONTH(int &ref) {
    if (NEW_MONTH != CURRENT_MONTH) {
        CURRENT_MONTH = NEW_MONTH;
        SET_COLORS();
    }
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    TRAIN_CYCLE();
    SYNC_TIME();
}

void SYNC_TIME() {
  if (millis() - lastSync > ONE_DAY_MILLIS) {
    // Request time synchronization from the Particle Device Cloud
    Particle.syncTime();
    lastSync = millis();
    SET_COLORS();
  }
}

void SET_COLORS(){
    if (CURRENT_MONTH == 1) {
        TRAIN_COLOR = strip.Color(BLUE);
        TRAIN_ALTCOLOR = strip.Color(LIGHTBLUE);
        TRAIN_OFF_COLOR = strip.Color(WHITE);
        Particle.publish("Blue and White");
        strip.show();
    } else if (CURRENT_MONTH == 1) {
        TRAIN_COLOR = strip.Color(PINK);
        TRAIN_ALTCOLOR = strip.Color(RED);
        Particle.publish("Pink and Red");
        strip.show();
    } else if (CURRENT_MONTH == 3) {
        TRAIN_COLOR = strip.Color(GREEN);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Green and White");
        strip.show();
    } else if (CURRENT_MONTH == 4) {
        TRAIN_COLOR = strip.Color(TEAL);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Teal and White");
        strip.show();
    } else if (CURRENT_MONTH == 5) {
        TRAIN_COLOR = strip.Color(MAGENTA);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Magenta and White");
        strip.show();
    } else if (CURRENT_MONTH == 6) {
        TRAIN_COLOR = strip.Color(LIGHTGREEN);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Light Green and White");
        strip.show();
    } else if (CURRENT_MONTH == 7) {
        TRAIN_COLOR = strip.Color(RED);
        TRAIN_ALTCOLOR = strip.Color(BLUE);
        TRAIN_OFF_COLOR = strip.Color(WHITE);
        Particle.publish("Red, White and Blue");
        strip.show();
    } else if (CURRENT_MONTH == 8) {
        TRAIN_COLOR = strip.Color(YELLOW);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Yellow and White");
        strip.show();
    } else if (CURRENT_MONTH == 9) {
        TRAIN_COLOR = strip.Color(ORANGE);
        TRAIN_ALTCOLOR = strip.Color(WHITE);
        Particle.publish("Orange and WHITE");
        strip.show();
    } else if (CURRENT_MONTH == 10) {
        TRAIN_COLOR = strip.Color(PURPLE);
        TRAIN_ALTCOLOR = strip.Color(GREEN);
        TRAIN_OFF_COLOR = strip.Color(ORANGE);
        Particle.publish("Purple, Orange and Green");
        strip.show();
    } else if (CURRENT_MONTH == 11) {
        TRAIN_COLOR = strip.Color(ORANGE);
        TRAIN_ALTCOLOR = strip.Color(YELLOW);
        Particle.publish("Orange and Yellow");
        strip.show();
    } else if (CURRENT_MONTH == 12) {
        TRAIN_COLOR = strip.Color(RED);
        TRAIN_ALTCOLOR = strip.Color(GREEN);
        Particle.publish("Red and Green");
        strip.show();
    }
}

void TRAIN_CYCLE(){
    strip.setPixelColor(TRAIN1_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN1_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN2_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN2_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN3_POSITION, TRAIN_COLOR);
    strip.setPixelColor(TRAIN3_OFF, TRAIN_OFF_COLOR);
    strip.setPixelColor(TRAIN4_POSITION, TRAIN_ALTCOLOR);
    strip.setPixelColor(TRAIN4_OFF, TRAIN_OFF_COLOR);
    
    TRAIN1_POSITION ++;
    TRAIN1_OFF ++;
    TRAIN2_POSITION ++;
    TRAIN2_OFF ++;
    TRAIN3_POSITION ++;
    TRAIN3_OFF ++;
    TRAIN4_POSITION ++;
    TRAIN4_OFF ++;
    
    strip.show();
    delay(LOOPTIME);

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
}

void SET_ALL(byte red, byte green, byte blue) {
  for(int i = 0; i < PIXEL_COUNT; i++ ) {
    strip.setPixelColor(i, red, green, blue); 
  }
  strip.show();
}

void rainbowCycle(int SpeedDelay) {
  Particle.publish("Starting up...");
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*2; j++) { // 2 cycles of all colors on wheel
    for(i=0; i< PIXEL_COUNT; i++) {
      c=Wheel(((i * 256 / PIXEL_COUNT) + j) & 255);
      strip.setPixelColor(i, *c, *(c+1), *(c+2));
    }
    strip.show();
    delay(SpeedDelay);
  }
  SET_ALL(OFF);
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
