#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define LOOK_ID   0
#define NUM_LOOKS 1
#define BAUD   9600
#define NUM_CHARS 4

#define XBEE_IN   8
#define XBEE_OUT  7

#define A_PIN     2
#define B_PIN     3
#define C_PIN     4
#define D_PIN     5
#define E_PIN     6

#define A_COUNT  12
#define B_COUNT  12
#define C_COUNT  12
#define D_COUNT  12
#define E_COUNT  12

char incData[NUM_CHARS];
char tempData[NUM_CHARS];

boolean newData = false;

unsigned long previousMillis;
int interval = 10000;

char reveivedChars[NUM_CHARS];

boolean mcConnect;
boolean startSeq;

// LED strip
Adafruit_NeoPixel a(A_COUNT, A_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel b(B_COUNT, B_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel c(C_COUNT, C_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel d(D_COUNT, D_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel e(E_COUNT, E_PIN, NEO_GRB + NEO_KHZ800);

SoftwareSerial xBee(XBEE_IN, XBEE_OUT); // RX, TX out

void setup() {
  mcConnect = false;
  startSeq  = false;
  
  Serial.begin(BAUD);

  while (!Serial) {
    ;
  }

  Serial.println("starting...");

  xBee.begin(BAUD);

  Serial.println("xBee Started.");

  /*for(int i = 0; i < NUM_CHARS; i++) {
    receivedChars[i] = 0;
  }*/
  
  a.begin();
  b.begin();
  c.begin();
  d.begin();
  e.begin();
  
  a.show();
  b.show();
  c.show();
  d.show();
  e.show();
  
  a.setBrightness(50); // Sets the brightness to ~1/5 of max
  b.setBrightness(50);
  c.setBrightness(50);
  d.setBrightness(50);
  e.setBrightness(50);
  
  for(int i = 0; i < a.numPixels(); i++) {
    a.setPixelColor(i, a.Color(255, 255, 255));
  }
  for(int i = 0; i < b.numPixels(); i++) {
    b.setPixelColor(i, b.Color(255, 255, 255));
  }
  for(int i = 0; i < c.numPixels(); i++) {
    c.setPixelColor(i, c.Color(255, 255, 255));
  }
  for(int i = 0; i < d.numPixels(); i++) {
    d.setPixelColor(i, d.Color(255, 255, 255));
  }
  for(int i = 0; i < e.numPixels(); i++) {
    e.setPixelColor(i, e.Color(255, 255, 255));
  }

  a.show();
  b.show();
  c.show();
  d.show();
  e.show();
  
  Serial.println("setup complete");
}

void loop() {
  if(!mcConnect) {
    Serial.println("connecting to mission control");
    for(int i = 0; i < a.numPixels(); i++) {
      a.setPixelColor(i, a.Color(255,0,0));
      b.setPixelColor(i, b.Color(255,0,0));
      c.setPixelColor(i, c.Color(255,0,0));
      d.setPixelColor(i, d.Color(255,0,0));
      e.setPixelColor(i, e.Color(255,0,0));
      a.show();
      b.show();
      c.show();
      d.show();
      e.show();
    }
    int incoming = checkForData('!','~');
    Serial.println(incoming);
    if(incoming == LOOK_ID) {
      Serial.println("connected to mission control");
      mcConnect = true;
      xBee.write("~0!\n");
    }
  } else if(!startSeq) {
    Serial.println("waiting for start signal");
    for(int i = 0; i < a.numPixels(); i++) {
      a.setPixelColor(i, a.Color(0,255,0));
      b.setPixelColor(i, b.Color(0,255,0));
      c.setPixelColor(i, c.Color(0,255,0));
      d.setPixelColor(i, d.Color(0,255,0));
      e.setPixelColor(i, e.Color(0,255,0));
      a.show();
      b.show();
      c.show();
      d.show();
      e.show();
    }
    int incoming = checkForData('!','~');
    if(incoming == NUM_LOOKS) {
      Serial.println("start signal received");
      startSeq = true;
    }
  } else {
    Serial.println("sequence running");
    for(int i = 0; i < a.numPixels(); i++) {
      a.setPixelColor(i, a.Color(0,0,255));
      b.setPixelColor(i, b.Color(0,0,255));
      c.setPixelColor(i, c.Color(0,0,255));
      d.setPixelColor(i, d.Color(0,0,255));
      e.setPixelColor(i, e.Color(0,0,255));
      a.show();
      b.show();
      c.show();
      d.show();
      e.show();
    }
  }
  delay(200);
  /*for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(random(256), random(256), random(256)));
  }
  strip.show();
  delay(1000);*/
}



int checkForData(char startData, char endData) {
  static boolean inProgress = false;
  static byte index = 0;
  char readChar;

  while (xBee.available() > 0 && newData == false) {
    readChar = xBee.read();
    Serial.println(readChar);
    if(inProgress) {
      if(readChar != endData) {
        incData[index] = readChar;
        index++;

        if (index >= NUM_CHARS) {
          index = NUM_CHARS - 1;
        }
      } else {
        incData[index] = '\0';
        inProgress = false;
        index = 0;
        newData = true;
      }
    } else if (readChar == startData) {
      inProgress = true;
    }
  
    if (newData) {
      strcpy(tempData,incData);
      Serial.println(incData);
      newData = false;
      return processData(endData);
    }
    return -1;
  } 
  return -1;
}

int processData(char endChar) {
/* We're now expecting the data to be #
 * We expect the values to be in the order of: motNum, spd, rot
 */
    char* strtokIndx;                   //this is used by strtok() as an index

    strtokIndx = strtok(tempData,"endChar");  // get the first part up tp '~'
    return atoi(strtokIndx);          //convert to int
}
