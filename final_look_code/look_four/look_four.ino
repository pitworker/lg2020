#include <Wire.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

#define NECK_PIN     6 //thisone
#define MID_PIN      7 //middle
#define DRESS_UPPER_PIN   5 //top

#define NECK_COUNT   13
#define MID_COUNT    13
#define DRESS_UPPER_COUNT 13

// LED strip
Adafruit_NeoPixel neck(NECK_COUNT, NECK_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel mid(MID_COUNT, MID_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dress_upper(DRESS_UPPER_COUNT, DRESS_UPPER_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //Serial.begin(9600);
  neck.begin();
  mid.begin();
  dress_upper.begin();
  
  neck.setBrightness(50); // Sets the brightness to ~1/5 of max
  mid.setBrightness(50);
  dress_upper.setBrightness(50);

  for(int i = 0; i < NECK_COUNT; i++){
    neck.setPixelColor(i, neck.Color(255, 255, 0));
  }

  for(int i = 0; i < MID_COUNT; i++){
    mid.setPixelColor(i, mid.Color(0, 255, 255));
  }

  for(int i = 0; i < DRESS_UPPER_COUNT; i++){
    dress_upper.setPixelColor(i, dress_upper.Color(255, 0, 255));
  }
  
  neck.show();
  mid.show();
  dress_upper.show();
  
  //Serial.println("setup complete");
}

void loop() {
  //Serial.println("loop");
  delay(200);
}
