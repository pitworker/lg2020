
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    4
#define XBEE_IN    9
#define XBEE_OUT   8

#define LED_COUNT  6

#define DELAY_TIME 50

#define NUM_CHARS 8

SoftwareSerial xBee(8, 9); // RX, TX out (8,9)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

long int color;
int currentIndex;

char receivedChars[NUM_CHARS];

boolean newData = false;

void setupStrip() {
  /*
   * Initializes the LED strip
   */
  strip.begin();
  strip.show();
  strip.setBrightness(50); // Sets the brightness to ~1/5 of max
}

void setupXBee() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.println("Starting...");

  // set the data rate for the SoftwareSerial port
  xBee.begin(9600);
  
  Serial.println("xBee Started.");
}

void setup() {
  setupStrip();
  setupXBee();

  color = 0;
  currentIndex = 0;

  for (int i = 0; i < NUM_CHARS; i++) {
    receivedChars[i] = 0;
  }
}

void loop() {
  recvWithStartEndMarkers();
  if (newData) {
    String receivedStr = String(receivedChars);
    long int newColor = receivedStr.toInt();

    byte red = getR(color);
    byte green = getG(color);
    byte blue = getB(color);

    if(newColor != color) {
      color = newColor;
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(green,red,blue));
      }
      strip.show();
    }
    Serial.print("red: ");
    Serial.print(red);
    Serial.print(", green: ");
    Serial.print(green);
    Serial.print(", blue: ");
    Serial.println(blue);
    Serial.print("received: ");
    Serial.print(receivedStr);
    Serial.print(", parsed: ");
    Serial.println(color, HEX);
    newData = false;  
  }
}

byte getR(long int c) {
  //Serial.println((byte) ((c >> 16) & 0x000000FF), HEX);

  long int red = (c >> 16) & 0x000000FF;
  
  //Serial.print("red ");
  //Serial.println(red);
  return (byte) red;
}

byte getG(long int c) {

  long int green = (c >> 8) & 0x000000FF;

  //Serial.print("green ");
  //Serial.println(green);
  return (byte) green;
}

byte getB(long int c) {
  long int blue = c & 0x000000FF;

  //Serial.print("blue ");
  //Serial.println(blue);
  return (byte) blue;
}

void recvWithStartEndMarkers() { 
  //https://forum.arduino.cc/index.php?topic=396450.0
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (xBee.available() > 0 && newData == false) {
        rc = xBee.read();
        bool wasColon = false;
        Serial.println(rc);
        if (recvInProgress == true) {
            if (rc != endMarker && ((rc >= '0' && rc <= '9') || rc == ':')) {
                //if (wasColon && (rc >= '0' && rc <= '9')) {
                    receivedChars[ndx] = rc;
                    ndx++;
                    //Serial.println(rc);
                  //  wasColon = false;
                //} else if (rc == ':') {
                //    wasColon = true;
                //}
            }
            else if (rc == endMarker) {
                //Serial.println(ndx);
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
            else {
                recvInProgress = false;
                ndx = 0;
                newData = false;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
