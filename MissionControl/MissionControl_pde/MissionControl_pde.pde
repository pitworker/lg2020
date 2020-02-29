/** Processing sketch */
 
import processing.serial.*;
 
Serial xbee;

boolean looks[];

final int baud = 9600;
final int numLooks = 1;
 
void setup() {
  frameRate(15);
  size(300, 300);
  println((Object[])Serial.list()); // print list of available serial ports
  // you might need to change the Serial.list()[VALUE]
  xbee = new Serial(this, Serial.list()[0], baud);
  xbee.bufferUntil('\n');
  
  looks = new boolean[numLooks];
  for(int i = 0; i < looks.length; i++) {
    looks[i] = false;
  }
  
  connectToLooks();
}
 
void draw() {
  // you could map the incoming data to a graphical or 
  // text display
}

boolean connectToLooks() {
  String incoming = null;
  int loops = 0;
  boolean success = true;
  
  while(xbee.available() > 0) {
    for(int i = 0; i < looks.length; i++) {
      while(looks[i] == false) {
        if(loops > 100) {
          success = false;
          break;
        }
        println("Connecting to look " + i);
        xbee.write("!" + i + "~\n");
        incoming = xbee.readStringUntil('\n');
        if(incoming != null) {
          if(incoming.equals("~" + i + "!")) {
            looks[i] = true;
            println("look " + i + " connected");
          } else {
            println("received: " + incoming);
          }
        }
        loops++;
        delay(100);
      }
    }
    if(!success) {
      println("CONNECTION TIMED OUT");
      return success;
    }
    xbee.write("!" + numLooks + "~\n");
    println("ALL LOOKS CONNECTED");
    return success;
  }
  return success;
}
