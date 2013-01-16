//Mr. Active - no predictions! ;)

float waittime = 0.5;
float brightthresh;
float threshold;
int sensor = 0;

void setup(){
  reset();
  calibrateBrightThresh();
}

void loop(){
  findLight(); //so sophisticated!
  waitMin(waittime);
}

void reset(){
  turnXAngle(0);
  turnYAngle(0);
}

void calibrateBrightThresh(){
  digitalWrite(13, HIGH);
  while(digitalRead(12) == LOW){} //button press on pin 12
  brightthresh = analogRead(sensor);
  digitalWrite(13, LOW);
}

void findLight(){
  findLightX();
  findLightY();
}

void findLightX(){ //points dish toward light in x dimension, returns x value (angle, 0 to 180)
  int sensorval = analogRead(sensor);
  int prevsensorval = 0;
  
  boolean motorright = false; //true for left, false for right for motor direction
  
  do{
    if(sensorval>prevsensorval+threshold){
      //right way
    }
    if(sensorval<prevsensorval-threshold){
      //wrong way
      motorright = !motorright;
    }
    turnXMotor(motorright); //true for left, false for right
  }while(sensorval < brightthresh);
}

void findLightY(){ //points dish toward light in x dimension, returns x value (angle, 0 to 180)
  int sensorval = analogRead(sensor);
  int prevsensorval = 0;
  
  boolean motorright = false; //true for left, false for right for motor direction
  
  do{
    if(sensorval>prevsensorval+threshold){
      //right way
    }
    if(sensorval<prevsensorval-threshold){
      //wrong way
      motorright = !motorright;
    }
    turnYMotor(motorright); //true for left, false for right
  }while(sensorval < brightthresh);
}

void waitMin(float time){ //waits "time" in minutes, neglecting read/write times for data :P
  float wait = time*1000*60; //converted to milliseconds
  int delaytime = 500; //wait time between reads
  int count = wait/delaytime;
  for(int x = 0; x++; x<count){
    sendLightSensor();
    delay(delaytime);
  }
}

void sendLightSensor(){
  digitalWrite(analogRead(0)/4, 10);
}

void turnXMotor(boolean direction){
  if(direction){ //left for true, right for false
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
}

void turnYMotor(boolean direction){
  if(direction){ //left for true, right for false
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
}

void stopXMotor(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  
}

void stopYMotor(){
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);  
}

float getXDegree(){
  analogRead(1)*(360/1023); //range from 0-1023 times degrees per 1023 constant
}

float getYDegree(){
  analogRead(2)*(360/1023); //range from 0-1023 times degrees per 1023 constant
}

void turnXAngle(float angle){
  if(angle > getXDegree()){ //motor should turn right
    turnXMotor(false);
    while(angle > getXDegree());
    stopXMotor();
  }
  else if(angle < getXDegree()){
    turnXMotor(false);
    while(angle > getXDegree());
    stopXMotor();
  }
}

void turnYAngle(float angle){
  if(angle > getYDegree()){ //motor should turn right
    turnYMotor(false);
    while(angle > getYDegree());
    stopYMotor();
  }
  else if(angle < getYDegree()){
    turnYMotor(false);
    while(angle > getYDegree());
    stopYMotor();
  }
}
