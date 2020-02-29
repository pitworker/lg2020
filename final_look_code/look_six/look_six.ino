#include <Wire.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define NECK_PIN     2 //bottom
#define MID_PIN      3
#define BOTTOM_PIN   4
#define FRONT_PIN    5
#define BACK_PIN     6

#define NECK_COUNT   12
#define MID_COUNT    12
#define BOTTOM_COUNT 12
#define FRONT_COUNT  12
#define BACK_COUNT   12

// LED strip
Adafruit_NeoPixel neck(NECK_COUNT, NECK_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid(MID_COUNT, MID_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottom(BOTTOM_COUNT, BOTTOM_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel front(FRONT_COUNT, FRONT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel back(BACK_COUNT, BACK_PIN, NEO_GRB + NEO_KHZ800);

uint32_t red;
uint32_t purple;
uint32_t blue;

int iterator = 0;

void setup() {
  Serial.begin(9600);
  neck.begin();
  mid.begin();
  bottom.begin();
  front.begin();
  back.begin();
  
  neck.show();
  mid.show();
  bottom.show();
  front.show();
  back.show();
  
  neck.setBrightness(50); // Sets the brightness to ~1/5 of max
  mid.setBrightness(50);
  bottom.setBrightness(50);
  front.setBrightness(50);
  back.setBrightness(50);

  blue = neck.Color(50, 200, 200);
  purple = neck.Color(255, 0, 255);
  red = neck.Color(255, 0, 80);

  for(int i = 0; i < neck.numPixels(); i++) {
    neck.setPixelColor(i, neck.Color(50, 200, 200));
  }

  for(int i = 0; i < mid.numPixels(); i++) {
    mid.setPixelColor(i, neck.Color(255, 0, 80));
  }

  for(int i = 0; i < bottom.numPixels(); i++) {
    bottom.setPixelColor(i, neck.Color(255, 0, 255));
  }

  for(int i = 0; i < front.numPixels(); i++) {
    front.setPixelColor(i, front.Color(255, 0, 80));
  }

   for(int i = 0; i < back.numPixels(); i++) {
    back.setPixelColor(i, neck.Color(255, 0, 255));
  }
  
  neck.show();
  mid.show();
  bottom.show();
  front.show();
  back.show();
  
  Serial.println("setup complete");
}

void loop() {
  iterator++;
  Serial.println(iterator);
  delay(600);
  for(int i = 0; i < neck.numPixels(); i++) {
    if ((iterator + i) % 3 == 0) {
      neck.setPixelColor(i, red);
      mid.setPixelColor(i, red);
      bottom.setPixelColor(i, red);
      front.setPixelColor(i, red);
      back.setPixelColor(i, red);
    } else if ((iterator + i) % 2 == 0) {
      neck.setPixelColor(i, purple);
      mid.setPixelColor(i, purple);
      bottom.setPixelColor(i, purple);
      front.setPixelColor(i, purple);
      back.setPixelColor(i, purple);
    } else {
      neck.setPixelColor(i, blue);
      mid.setPixelColor(i, blue);
      bottom.setPixelColor(i, blue);
      front.setPixelColor(i, blue);
      back.setPixelColor(i, blue);
    }
  }
//  for(int i = 0; i < mid.numPixels(); i++) {
//    if ((iterator + i) % 3 == 0) {
//      mid.setPixelColor(i, red);
//    } else if ((iterator + i) % 2 == 0) {
//      mid.setPixelColor(i, purple);
//    } else {
//      mid.setPixelColor(i, blue);
//    }
//  }
//  for(int i = 0; i < bottom.numPixels(); i++) {
//    if ((iterator + i) % 3 == 0) {
//      bottom.setPixelColor(i, red);
//    } else if ((iterator + i) % 2 == 0) {
//      bottom.setPixelColor(i, purple);
//    } else {
//      bottom.setPixelColor(i, blue);
//    }
//  }
  
  neck.show();
  mid.show();
  bottom.show();
  front.show();
  back.show();
}
