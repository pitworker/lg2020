#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define A_PIN    6
#define B_PIN    5
#define C_PIN    4

#define A_COUNT 11
#define B_COUNT 10
#define C_COUNT 10

// LED strip
Adafruit_NeoPixel a(A_COUNT, A_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel b(B_COUNT, B_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel c(C_COUNT, C_PIN, NEO_GRB + NEO_KHZ800);

uint32_t colors[3];
int iterator = 0;

void setup() {
  Serial.begin(9600);
  
  a.begin();
  b.begin();
  c.begin();
  
  a.show();
  b.show();
  c.show();
  
  a.setBrightness(50); // Sets the brightness to ~1/5 of max
  b.setBrightness(50);
  c.setBrightness(50);

  colors[0] = a.Color(50, 200, 200);
  colors[1] = a.Color(255, 0, 255);
  colors[2] = a.Color(255, 0, 80);
  
  for(int i = 0; i < a.numPixels(); i++) {
    a.setPixelColor(i, a.Color(255,255,255));
  }

  for(int i = 0; i < b.numPixels(); i++) {
    b.setPixelColor(i, b.Color(255,0,255));
  }

  for(int i = 0; i < c.numPixels(); i++) {
    c.setPixelColor(i, c.Color(255,0,0));
  }
  
  a.show();
  b.show();
  c.show();
  
  Serial.println("setup complete");
}

void loop() {
  iterator++;
  for(int i = 0; i < a.numPixels(); i++) {
    a.setPixelColor(i, colors[(i + 1 +  iterator) % 3]);
  }

  for(int i = 0; i < b.numPixels(); i++) {
    b.setPixelColor(i, colors[(i + 2 + iterator) % 3]);
  }

  for(int i = 0; i < c.numPixels(); i++) {
    c.setPixelColor(i, colors[(i + 3+  iterator) % 3]);
  }

  a.show();
  b.show();
  c.show();
  delay(1000);
}
