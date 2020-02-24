// ===================== Serial Data Example ===================== //
/*
  This is an example of how to send and recieve data over USB
  In this example, we are communicating with Processing.

  The arduino will update processing every so often with the values saved.
  It will also listen for any data communicated over ther serial to change
  those stored values.
*/
// ============================================================== //

// This should be the same as in Processing Sketch
#define BAUD 9600

const byte numChars = 32;// What is the longest message we want to store?
char incData[numChars];  //This will hold the incoming data
char tempData[numChars]; //Temporary array for parsing

uint8_t rot = 0;             //stores rotation value
uint8_t spd = 0;             //stores speed value
uint8_t mtrNum = 0;          //stores the motor value


boolean newData = false;     //this will be used to keep track of incoming data

unsigned long previousMillis;//this will keep track of the last time we checked millis()
int interval = 10000;        //this is how often we want to update processing

void setup() {
  //start the Serial at the predetermined baued rate
  //Again, this should match the value in Processing
  Serial.begin(BAUD);
}

void loop() {
  //see if any data is being sent
  checkForData();
  
  //periodically send the values currently stored in the arduino
  //back out to processing
  if (Serial.available() <= 0 && millis()>= (previousMillis + interval)) {
   //print out the current values
    printCurrentData();
   //update previousMillis 
    previousMillis = millis();
  }
 
}

void checkForData() {
    static boolean inProgress = false;
    static byte index = 0;
    char startData = '!'; //the char we expect to be at the start of our data string
    char endData = ';';   //the char we expect to be at the end of our data string
    char readSer;         //this will hold each incoming byte one at a time
   
    //============ READ IN DATA  ============// 
    //for as long as we are recieveing new data
    while (Serial.available() > 0 && newData == false) {
       
        readSer = Serial.read(); //read one byte of the Serial

        if (inProgress == true) {
          //if we're not at the ending character...
            if (readSer != endData) {
                incData[index] = readSer;
                index++;
                
                if (index >= numChars) {
                    index = numChars - 1;
                }
            }
            else {
                incData[index] = '\0'; // terminate the string
                inProgress = false;    // data has been read in
                index = 0;             //reset the index
                newData = true;        //let it be known that there's new data
            }
        }

        else if (readSer == startData) {
          //if the first byte read in was our starting character
          //let's deal with the new data
            inProgress = true;
        }
    }
  //============ END READ IN DATA  ============//   
  //If we've got new data to process:
    if (newData){
      //store the data into a temp array since we'll be altering it
      //with strtok(), which replaces the commas with '\0'
      strcpy(tempData, incData);
      //split the array up so we can use it
      processData();
      //print conformation to Processing
      printCurrentData();
      //we've dealt with the new data, so now it's false
      newData = false;
   }
}

void  processData() {
/* We're now expecting the data to be #,#,#
 * We expect the values to be in the order of: motNum, spd, rot
 */
    char * strtokIndx;                  //this is used by strtok() as an index

    strtokIndx = strtok(tempData,",");  // get the first part up tp ','
    mtrNum = atoi(strtokIndx);          //convert to int
 
    strtokIndx = strtok(NULL, ",");     // this continues where the previous call left off
    spd = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ";");
    rot = atoi(strtokIndx);    
  
}

void printCurrentData() {
//we're using the '!' character to let processing know that we are
//just sending messages, not any data itself
  if (newData) {
    Serial.print("!Received Values:\t Mtr: ");
    Serial.print(mtrNum);
    Serial.print("\t Spd: ");
    Serial.print(spd);
    Serial.print("\t Rot: ");
    Serial.println(rot);
  }else {
    Serial.print("!Current Values:\t Mtr: ");
    Serial.print(mtrNum);
    Serial.print("\t Spd: ");
    Serial.print(spd);
    Serial.print("\t Rot: ");
    Serial.println(rot);
  } 
}
