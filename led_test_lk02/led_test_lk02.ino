#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define FM_PIN     2
#define FS_PIN     7
#define BM_PIN     3
#define BS_PIN     5

#define FM_COUNT   7
#define FS_COUNT   6
#define BM_COUNT   4
#define BS_COUNT   5

// LED strip
Adafruit_NeoPixel fm(FM_COUNT, FM_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel fs(FS_COUNT, FS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bm(BM_COUNT, BM_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bs(BS_COUNT, BS_PIN, NEO_GRB + NEO_KHZ800);

int currentPos;

void setup() {
  Serial.begin(9600);
  
  currentPos = 0;
  
  fm.begin();
  fs.begin();
  bm.begin();
  bs.begin();
  
  fm.show();
  fs.show();
  bm.show();
  bs.show();
  
  fm.setBrightness(50); // Sets the brightness to ~1/5 of max
  fs.setBrightness(50);
  bm.setBrightness(50);
  bs.setBrightness(50);
  
  for(int i = 0; i < fm.numPixels(); i++) {
    fm.setPixelColor(i, fm.Color(255, 255, 255));
  }
  for(int i = 0; i < fs.numPixels(); i++) {
    fs.setPixelColor(i, fs.Color(255, 255, 255));
  }
  for(int i = 0; i < bm.numPixels(); i++) {
    bm.setPixelColor(i, bm.Color(255, 255, 255));
  }
  for(int i = 0; i < bs.numPixels(); i++) {
    bs.setPixelColor(i, bs.Color(255, 255, 255));
  }

  fm.show();
  fs.show();
  bm.show();
  bs.show();
  
  Serial.println("setup complete");
}

void loop() {
  Serial.println("loop");
  delay(75);
  
  for(int i = 0; i < fm.numPixels(); i++) {
    fm.setPixelColor(i, fm.Color(0, 0, 150));
  }
  for(int i = 0; i < fs.numPixels(); i++) {
    fs.setPixelColor(i, fs.Color(0,0,150));
  }
  for(int i = 0; i < bm.numPixels(); i++) {
    bm.setPixelColor(i, bm.Color(0,0,150));
  }
  for(int i = 0; i < bs.numPixels(); i++) {
    bs.setPixelColor(i, bs.Color(0,0,150));
  }

  if(currentPos < 4) {
    fm.setPixelColor(currentPos, fm.Color(255, 150, 150));
    fs.setPixelColor(currentPos, fs.Color(255, 150, 150));
    bm.setPixelColor(currentPos, bm.Color(255, 150, 150));
    bs.setPixelColor(currentPos, bs.Color(255, 150, 150));
  } else if(currentPos < 5) {
    fm.setPixelColor(currentPos, fm.Color(255, 150, 150));
    fs.setPixelColor(currentPos, fs.Color(255, 150, 150));
    bs.setPixelColor(currentPos, bs.Color(255, 150, 150));
  } else if(currentPos < 6) {
    fm.setPixelColor(currentPos, fm.Color(255, 150, 150));
    fs.setPixelColor(currentPos, fs.Color(255, 150, 150));
  } else {
    fm.setPixelColor(currentPos, fm.Color(255, 150, 150));
  }

  fm.show();
  fs.show();
  bm.show();
  bs.show();

  if(currentPos < 6) {
    currentPos++;
  } else {
    currentPos = 0;
  }
}
