/** Arduino sketch */
 
#include <SoftwareSerial.h>
 
#define xbeeRx 9 // XBee DOUT
#define xbeeTx 8 // XBee DIN
 
SoftwareSerial xbee = SoftwareSerial(xbeeRx, xbeeTx);

int count;
 
void setup() {
  pinMode(xbeeRx, INPUT);
  pinMode(xbeeTx, OUTPUT);
  xbee.begin(9600);
  count = 0;
}
 
void loop() {
  xbee.println(count); // send the value via XBee

  count++;
}
