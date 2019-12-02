/** Processing sketch */
 
import processing.serial.*;
 
Serial xbee;
 
String potVal;

int r;
int g;
int b;

int c;
 
void setup() {
  size(300, 300);
  println((Object[])Serial.list()); // print list of available serial ports
  // you might need to change the Serial.list()[VALUE]
  xbee = new Serial(this, Serial.list()[2], 9600);
  
  r = 255;
  g = 255;
  b = 255;
  
  c = 0x00FFFFFF;
}
 
void draw() {
  // you could map the incoming data to a graphical or 
  // text display
  
  if (keyPressed) {
    if (key == 'r' || key == 'R') {
      r = ~ r & 0x000000FF;
    } else if (key == 'g' || key == 'G') {
      g = ~ g & 0x000000FF; 
    } else if (key == 'b' || key == 'B') {
      b = ~ b & 0x000000FF;
    }
  }
 
  c = 0xFF000000 | (r << 16) | (g << 8) | (b);
  
  String data = "<" + c + ">";
  
  xbee.write(data);
  println(hex(c));
  /*potVal = xbee.readStringUntil(10); // read incoming data until line feed
  if (potVal != null) {
    println("Incoming data: " + potVal);
  }*/
}