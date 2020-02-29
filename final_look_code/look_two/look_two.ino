#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define RIGHT_PIN    6
#define LEFT_PIN     5
#define HEAD_PIN     4
#define RIGHT_COUNT 10
#define LEFT_COUNT  10
#define HEAD_COUNT  12

// LED strip
Adafruit_NeoPixel right(RIGHT_COUNT, RIGHT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left(LEFT_COUNT, LEFT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel head(HEAD_COUNT, HEAD_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  right.begin();
  left.begin();
  head.begin();
  
  right.show();
  left.show();
  head.show();
  
  right.setBrightness(50); // Sets the brightness to ~1/5 of max
  left.setBrightness(50);
  head.setBrightness(50);

  for(int i = 0; i < head.numPixels(); i++) {
    head.setPixelColor(i, head.Color(255, 255, 255));
  }
  head.show();


  for(int i = 0; i < left.numPixels(); i++) {
    if(i % 2 == 0) {
      left.setPixelColor(i, left.Color(0, 255, 255));
      right.setPixelColor(i, right.Color(0, 255, 255));
    } else {
      left.setPixelColor(i, left.Color(255, 0, 0));
      right.setPixelColor(i, right.Color(255, 0, 0));
    }
  }
  left.show();
  right.show();
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
