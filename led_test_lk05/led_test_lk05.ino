#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define NECK_PIN     2
#define MID_PIN      5
#define BOTTOM_PIN   6
#define FRONT_PIN    4
#define BACK_PIN     3

#define NECK_COUNT   5
#define MID_COUNT    5
#define BOTTOM_COUNT 6
#define FRONT_COUNT  7
#define BACK_COUNT   7

// LED strip
Adafruit_NeoPixel neck(NECK_COUNT, NECK_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid(MID_COUNT, MID_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bottom(BOTTOM_COUNT, BOTTOM_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel front(FRONT_COUNT, FRONT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel back(BACK_COUNT, BACK_PIN, NEO_GRB + NEO_KHZ800);

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

  for(int i = 0; i < bottom.numPixels(); i++) {
    neck.setPixelColor(i, neck.Color(255, 255, 0));
    mid.setPixelColor(i, mid.Color(255, 255, 0));
    bottom.setPixelColor(i, bottom.Color(255, 255, 0));
  }


  for(int i = 0; i < front.numPixels(); i++) {
    front.setPixelColor(i, front.Color(255, 0, 0));
    back.setPixelColor(i, back.Color(255, 0, 0));
  }
  
  neck.show();
  mid.show();
  bottom.show();
  front.show();
  back.show();
  
  Serial.println("setup complete");
}

void loop() {
  Serial.println("loop");
  delay(200);
  /*for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(random(256), random(256), random(256)));
  }
  strip.show();
  delay(1000);*/
}
