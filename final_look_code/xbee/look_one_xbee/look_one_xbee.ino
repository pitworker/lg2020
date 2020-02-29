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

int coloridx = 0;
uint32_t colorsets[3][3];
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
   
  colorsets[0][0] = right.Color(70, 150, 255);
  colorsets[0][1] = right.Color(50, 200, 255);
  colorsets[0][2] = right.Color(100, 0, 255);
  
  colorsets[1][0] = right.Color(255, 0, 255);
  colorsets[1][1] = right.Color(0, 200, 200);
  colorsets[1][2] = right.Color(255, 0, 80);
  
  colorsets[2][0] = right.Color(255, 0, 0);
  colorsets[2][1] = right.Color(255, 255, 255);
  colorsets[2][2] = right.Color(0, 0, 255);

}

void loop() {
  
  Serial.println("loop");
  iterator++;
  delay(75);
  for(int i = 0; i < head.numPixels(); i++) {
    head.setPixelColor(i, colorset[coloridx][2]);
    left.setPixelColor(i, colorset[coloridx][0]);
    right.setPixelColor(i,colorset[coloridx][0]);
  }

  head.setPixelColor(iterator % HEAD_COUNT, colorset[coloridx][0]);
  left.setPixelColor(iterator % LEFT_COUNT, colorset[coloridx][2]);
  right.setPixelColor(iterator % RIGHT_COUNT, colorset[coloridx][2]);
  left.show();
  right.show();
  head.show();
  
}
