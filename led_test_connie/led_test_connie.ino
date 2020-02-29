#include <Wire.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define NECK_PIN     3 //thisone
#define MID_PIN      1
#define DRESS_UPPER_PIN   4
#define DRESS_BOTTOM_PIN   2

#define NECK_COUNT   5
#define MID_COUNT    7
#define DRESS_UPPER_COUNT 12
#define DRESS_BOTTOM_COUNT 12

// LED strip
Adafruit_NeoPixel neck(NECK_COUNT, NECK_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid(MID_COUNT, MID_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dress_upper(DRESS_UPPER_COUNT, DRESS_UPPER_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dress_bottom(DRESS_BOTTOM_COUNT, DRESS_BOTTOM_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //Serial.begin(9600);
  neck.begin();
  mid.begin();
  dress_upper.begin();
  dress_bottom.begin();
  
  neck.setBrightness(50); // Sets the brightness to ~1/5 of max
  mid.setBrightness(50);
  dress_upper.setBrightness(50);
  dress_bottom.setBrightness(50);

  for(int i = 0; i < NECK_COUNT; i++){
    neck.setPixelColor(i, neck.Color(255, 0, 0));
  }

  for(int i = 0; i < MID_COUNT; i++){
    mid.setPixelColor(i, mid.Color(0, 255, 0));
  }

  for(int i = 0; i < DRESS_UPPER_COUNT; i++){
    dress_upper.setPixelColor(i, dress_upper.Color(0, 255, 255));
  }

  for(int i = 0; i < DRESS_BOTTOM_COUNT; i++){
    dress_bottom.setPixelColor(i, dress_bottom.Color(255, 255, 0));
  }
  
  neck.show();
  mid.show();
  dress_upper.show();
  dress_bottom.show();
  
  //Serial.println("setup complete");
}

void loop() {
  //Serial.println("loop");
  delay(200);
}
