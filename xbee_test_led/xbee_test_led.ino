
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    7
#define XBEE_IN    8
#define XBEE_OUT   9

#define LED_COUNT  6

#define DELAY_TIME 50

#define NUM_CHARS 32

SoftwareSerial xBee(8, 9); // RX, TX out (8,9)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int color;
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
    int newColor = receivedStr.toInt();

    if(newColor != color) {
      color = newColor;
      for(int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(getG(color),getR(color),
                                           getB(color)));
      }
      strip.show();
    }
    
    Serial.print(receivedStr);
    Serial.print(", ");
    Serial.println(color, HEX);
    newData = false;  
  }
}

byte getR(int c) {
  return (byte) ((c >> 16) & 0x000000FF);
}

byte getG(int c) {
  return (byte) ((c >> 8) & 0x000000FF);
}

byte getB(int c) {
  return (byte) (c & 0x000000FF);
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

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= NUM_CHARS) {
                    ndx = NUM_CHARS - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}
