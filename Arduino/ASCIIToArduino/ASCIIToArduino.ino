int motor1 = 5;
int motor2 = 9;//add more motors if necessary
char inChar;//ASCII char from main program

void setup(){
  Serial.begin(9600);//begin reading serially
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  analogWrite(motor1, 0);//zero out motors
  analogWrite(motor2, 0);
}

void loop(){  
  if(Serial.available())
    inChar = (char)Serial.read(); //read value from main program

  analogWrite(motor1, (int)inChar * 2); //repeat this for additional motors
  analogWrite(motor2, (int)inChar * 2); 

}
