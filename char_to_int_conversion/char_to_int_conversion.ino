
//makes the character array of length 3
char* make_char_array(int red, int green, int blue){
  char r = (unsigned char)red;
  int rr = (int)r;
  char* val = malloc(sizeof(char) * 3);

  //we have to place it in the range [-128, 127]
  val[0] = (red - 128); 
  val[1] = (green - 128);
  val[2] = (blue - 128);
  return val;
}

//gets red val
int get_red(char* arr){
  char a = arr[0];
  return (int)a + 128; //convert from [-128, 127] -> [0, 255]
}

//gets green val
int get_green(char* arr){
  return (int)arr[1] + 128; //convert from [-128, 127] -> [0, 255]
}

//gets blue val
int get_blue(char* arr){
  return (int)arr[2] + 128; //convert from [-128, 127] -> [0, 255]
}

void setup() {

  int red = 255;
  int green = 50;
  int blue = 100;

  Serial.begin(9600);

  Serial.println("start:");
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);

  //"package" to send
  char* package = make_char_array(red, green, blue);

  int recieved_red = get_red(package);
  int recieved_green = get_green(package);
  int recieved_blue = get_blue(package);

  Serial.println("received:");
  Serial.println(recieved_red);
  Serial.println(recieved_green);
  Serial.println(recieved_blue);

}

void loop() {
  // put your main code here, to run repeatedly:
  
}
