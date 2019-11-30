
#include <SoftwareSerial.h>

SoftwareSerial xBee(8, 9); // RX, TX out (8,9)

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  
  while (!Serial) {
    ; // wait for serial port to connect.
  }


  Serial.println("Starting...");

  // set the data rate for the SoftwareSerial port
  xBee.begin(9600);
  Serial.println("xBee Started.");
}

void loop() // run over and over
{
  if (xBee.available())
    Serial.println(xBee.read());
}
