#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN   7
#define LED2_PIN  6
#define LED_COUNT 6

#define DELAY_TIME 50

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

// LED strip
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED2_PIN, NEO_GRB + NEO_KHZ800);

float velocityX, 
      velocityY,
      velocityZ;

void setupSensor() {
  /*
   * Initializes the LSM sensor
   */
  if (!lsm.begin())
  {
    Serial.println("ERROR: Unable to initialize the LSM9DS1.");
    while (1);
  }
  Serial.println("LSM9DS1 found.");
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}

void setupStrip() {
  /*
   * Initializes the LED strip
   */
  strip.begin();
  strip.show();
  strip.setBrightness(50); // Sets the brightness to ~1/5 of max

  strip2.begin();
  strip2.show();
  strip2.setBrightness(50);
}

float velocity(float prevV, float a) {
  /*  
   * Calculates the current velocity given the previous velocity
   * and the current acceleration.
   * NOTE: this ignores the presence of acceleration due to gravity,
   *       so velocity will be inaccurate as a result, possibly by
   *       a large factor.
   */
  float numSecs = ((float) DELAY_TIME) / 1000.0;
  return (a * numSecs) + prevV; 
}

void setup() {
  Serial.begin(115200);

  //setupSensor();
  setupStrip();

  velocityX = 0;
  velocityY = 0;
  velocityZ = 0;

  Serial.println("setup complete");
}

void loop() {
  /*sensors_event_t a;
  sensors_event_t m;
  sensors_event_t g;
  sensors_event_t temp;*/
  
  int accelCombined; 

  int rColor;

  /*lsm.read();
  lsm.getEvent(&a, &m, &g, &temp);

  //update velocity values
  velocityX = velocity(velocityX, a.acceleration.x);
  velocityY = velocity(velocityY, a.acceleration.y);
  velocityZ = velocity(velocityZ, a.acceleration.z);

  
  Serial.print("Gyro X: "); Serial.print(g.gyro.x);  Serial.print(" dps");
  Serial.print("\tY: "); Serial.print(g.gyro.y);     Serial.print(" dps ");
  Serial.print("\tZ: "); Serial.print(g.gyro.z);     Serial.println(" dps ");
  
  rColor = map(int(max(0.4, min(5.0, abs(m.magnetic.x))) * 51.0), 20, 255, 0, 255);*/
  
  for(int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0,255,0,0));/*strip.Color(rColor, rColor
    , 0));*/
    strip2.setPixelColor(i, strip.Color(0,255,0));
  }
  strip.show();
  strip2.show();
  delay(DELAY_TIME);
}
