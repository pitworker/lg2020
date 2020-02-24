// ===================== Serial Data Example ===================== //
/*
  This is an example of how to send and recieve data over USB
  In this example, we are communicating with an Arduino.
  
  It will listen for any data communicated over ther serial.
  In order to send data, we press the space bar to get things started.
*/
// ============================================================== //

import processing.serial.*; //this will allow us to monitor the serial connection
import javax.swing.*;       //this is just for quality of life, making selecting COM and sending values easier

Serial arduino;             //this will be the name of the port used to establish a connection with the Arduino
String arduinoData;         //this will hold data that will be sent / received to/from the Arduino
int[] arduinoVals;          //this will hold the converted string data into int data


int baud = 9600;            // Baud rate should match the arduino's baud rate for the Serial

final boolean debugPort = true; //if true, we'll print out the COM list to the terminal




void setup() {
   size(250, 120);
  //If we want, we can use frameRate() to define how often we want to talk with the arduino
  //per second. The default is 60, which would be the same as not including
  //the frameRate() function.
  frameRate(15);
  
  // ========================= GET COM NEEDED FROM USER ========================//
  String COMx = "";
    try {
      if(debugPort) printArray(Serial.list());
      int numPorts = Serial.list().length;
       if (numPorts != 0) {
        if (numPorts >= 2) {
          COMx = (String) JOptionPane.showInputDialog(null, 
          "Select the port associated with the Arduino.\n\n" +
          "If you are unsure of which port, one way to\nfind" +
          " out is to go to Tools > Port in the Arduino IDE.\n ", 
          "COM Port Selection:", 
          JOptionPane.QUESTION_MESSAGE, 
          null, 
          Serial.list(), 
          Serial.list()[0]);
   
          if (COMx == null) exit();
          if (COMx.isEmpty()) exit();
        }
       
        arduino = new Serial(this, COMx, baud); 
        arduino.bufferUntil('\n'); // buffer until CR/LF appears, but not required..
      }
      else {
        JOptionPane.showMessageDialog(frame,"Arduino is not connected to the PC");
        exit();
      } 
    }     
      
      catch (Exception e){ 
      //Print the type of error
      if (COMx == null){ 
        JOptionPane.showMessageDialog(frame,"No port was selected. If you wish to continue,\n" +
                                            "reopen the program, and select a COM port.");
      } else {
        JOptionPane.showMessageDialog(frame,"COM port " + COMx + " is not available (maybe in use by another program)\n" +
                                            "This may also mean that you have the Serial Monitor open in the\n Arduiono" +
                                            " program. If so, close it, and try again.");
      }
      System.err.print("** Error **  ");
      System.err.println(e.toString());
      exit();
    }
   // ========================= END COM SELECTION ========================//
}

void draw(){
  background(100);
  fill(255); //text color
  text("Press Space bar to send values. ", 10,30);
  text("Arduino Msg: ", 10,80);
  if (arduinoData != null) text(arduinoData,10,100); 
    
 //check to see if the Arduino is sending data
  checkArduino();
  arduino.write("!" + 16777215 + "," + 16777215 + "," + 16777215 + ";");
 }


void checkArduino() {
  // ========================= CHECK FOR ARDUINO SENDING DATA ========================//
  /*
  The program on the arduino starts by sending using Serial.println("1 342 234") or whatever numbers you want
  at a baud of 9600. This was setup when we created the serial port for processing in the beginning. Through
  this program, you should be ablet to change those reported values by pressing space bar to send new ones
  */
  
   while (arduino.available() > 0) {
    // get message until new line
    arduinoData = arduino.readStringUntil('\n');
    //if Arduino is sending somthing
    if(arduinoData != null){ 
      //if the first char read in is a '!' that means we're receiving a message
      //from the arduino, not data. This means we just want to print it out
      if (arduinoData.charAt(0) == '!') {
        println("Arduino " + arduinoData);
      } else {
      //use a space (' ') character to denote a new array element
      //this could be used for maths if we want
      arduinoVals = int(split(arduinoData, ' '));
      //Debug to terminal
      print("Arduino Incoming Data = ");
      //This should match the received data
      println(arduinoData); 
      //make sure everything went into the array correctly
      print("Arduino Vals =");
        for (int i = 0; i < arduinoVals.length ; i++) {
          if( i == arduinoVals.length) {
            println(" [" + i + "] = " + arduinoVals[i]);
          } else {
            print("[" + i + "] = " + arduinoVals[i] + " ");
          }
        }
      }
    }
   } //end while
  // ========================= END SERIAL CHECK ========================//
}


void keyPressed(){
  println(key);
  
  //check to see if space bar has been pressed
  if (key == ' '){
    
    //these elements will hold the data entered by the user.
   JTextField motNum = new JTextField(3);
   JTextField speed = new JTextField(3);
   JTextField rot = new JTextField(3);
   
    //this will be the format of the input dialog
    JPanel dataPanel = new JPanel();
    dataPanel.add(new JLabel("Motor Number:"));
    dataPanel.add(motNum);
    dataPanel.add(Box.createHorizontalStrut(15)); //spacer
    dataPanel.add(new JLabel("Speed:"));
    dataPanel.add(speed);
    dataPanel.add(Box.createHorizontalStrut(15)); //spacer
    dataPanel.add(new JLabel("Rotation:"));
    dataPanel.add(rot);
    
    int option = JOptionPane.showConfirmDialog(null, dataPanel, "Enter Values to Send:", JOptionPane.OK_CANCEL_OPTION);
    
    // ========================= CHECK USER INPUT ========================//
    //check to make sure only numbers were entered in the text boxes
    int i;
    try {
      
      i = Integer.parseInt(motNum.getText());
      i = Integer.parseInt(speed.getText());
      i = Integer.parseInt(rot.getText());
      
    } catch(NumberFormatException e) {
      //check to make sure the OK button was pressed. Otherwise, we'd just want to cancel.
      if (option == JOptionPane.OK_OPTION) {
      //since we receieved an error, make it so that the data send is cancled
       option = JOptionPane.CANCEL_OPTION;
      
      //Display Error Message
        JOptionPane.showMessageDialog(frame,
            "One of the values entered was not a whole number.",
            "Incorrect Value Entered",
            JOptionPane.ERROR_MESSAGE);
            
      //display on the terminal for debug
      println("you did not enter a number!");
      System.err.print("** Error **  ");
      System.err.println(e.toString());
      }
    }
    // ========================= END CHECK ========================//
    
    //if there weren't any errors with the data type, check to see if the we pressed ok or cancel
    //if ok, send the data
    if (option == JOptionPane.OK_OPTION) {
            println("Sending Data:\t");
            println("\tMotor Num - " + motNum.getText() + "\n\tSpeed - " + speed.getText() + "\n\tRotation - " + rot.getText() );
            
            //send the data to the arduino
            //the arudino will be expecting a incoming format of !#,#,#;
            //where ! tells the arduino these are new values beign sent
            // # is an int data type. ',' will let the arduino know that the value has ended, 
            //and ';' will indicate termination of sent data
            arduino.write("!" + motNum.getText() + "," + speed.getText() + "," + rot.getText()+ ";");
    } else {
        println("Data Send Canceled");
        //Display Cancel Message
        JOptionPane.showMessageDialog(frame,
            "Data Send Canceled.",
            " ",
            JOptionPane.WARNING_MESSAGE);
    }
  }
   
}
