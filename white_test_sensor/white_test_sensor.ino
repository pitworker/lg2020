#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN   6
#define LED_COUNT 6

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

// LED strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupSensor() {
  if (!lsm.begin())
  {
    Serial.println("ERROR: Unable to initialize the LSM9DS1.");
    while (1);
  }
  Serial.println("LSM9DS1 found.");
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

void setupStrip() {
  strip.begin();
  strip.show();
  strip.setBrightness(50); // Sets the brightness to ~1/5 of max
}

void setup() {
  Serial.begin(9600);

  setupSensor();
  setupStrip();

  Serial.println("setup complete");
}

void loop() {
  sensors_event_t a;
  sensors_event_t m;
  sensors_event_t g;
  sensors_event_t temp;
  
  int accelCombined; 

  int accelColor;

  lsm.read();
  lsm.getEvent(&a, &m, &g, &temp);

  accelCombined = abs(int(a.acceleration.x) | 
                      int(a.acceleration.y) | 
                      int(a.acceleration.z));
  
  Serial.print("Accel X: "); 
  Serial.print(a.acceleration.x); 
  Serial.print(" m/s^2");
  
  Serial.print("\tY: "); 
  Serial.print(a.acceleration.y);     
  Serial.print(" m/s^2 ");
  
  Serial.print("\tZ: "); 
  Serial.print(a.acceleration.z); 
  Serial.println(" m/s^2 ");

  Serial.print("Combined accel: ");
  Serial.println(accelCombined);

  accelColor = map(min(accelCombined, 20), 0, 20, 0, 255);
  
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(int(a.acceleration.x * 10), 
                           int(a.acceleration.y * 10),
                           int(a.acceleration.z * 10)));
  }
  strip.show();
  delay(200);
}
