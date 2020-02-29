#include <Wire.h>
#include <SPI.h>
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

uint32_t colors[3];
int iterator = 0;

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
   
  colors[0] = right.Color(70, 150, 255);
  colors[1] = right.Color(50, 200, 255);
  colors[2] = right.Color(100, 0, 255);

  for(int i = 0; i < head.numPixels(); i++) {
    head.setPixelColor(i, head.Color(255, 255, 255));
  }
  


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
  head.show();
  Serial.println("setup complete");
}

void loop() {
  Serial.println("loop");
  iterator++;
  delay(200);
  for(int i = 0; i < head.numPixels(); i++) {
    head.setPixelColor(i, colors[2]);
    left.setPixelColor(i, colors[0]);
    right.setPixelColor(i,colors[0]);
  }

  head.setPixelColor(iterator % HEAD_COUNT, colors[0]);
  left.setPixelColor(iterator % LEFT_COUNT, colors[2]);
  right.setPixelColor(iterator % RIGHT_COUNT, colors[2]);
  left.show();
  right.show();
  head.show();
}
