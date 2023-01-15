int pinMotor1f = 4;
int pinMotor1b = 5;
int pinMotor2f = 7;
int pinMotor2b = 6;
int pinSpeed1 = 3;
int pinSpeed2 = 9;
//Initiating the pins that control the motors

int trigPin = 10;
int echoPin = 8;
//Initiating the pins for the ultrasonic sensor

double motorSpeed1;
double motorSpeed2;
//Vatiables for the motor speeds
 
void setup(){
 
  pinMode(pinMotor1f,OUTPUT);
  pinMode(pinMotor1b,OUTPUT);
  pinMode(pinMotor2f,OUTPUT);
  pinMode(pinMotor2b,OUTPUT);
  pinMode(pinSpeed1,OUTPUT);
  pinMode(pinSpeed2,OUTPUT);
 
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  //Designating the pins as Output/Input
 
  Serial.begin(9600);
 
}
 
void loop(){
 
  int distanceFront = readDistance();
  Serial.print("Distance front:");
  Serial.print(distanceFront);
  Serial.println("cm");
  //The car reads the distance in front of it, puts it in the distanceFront variable, and prints it to the serial monitor.
 
  if(distanceFront>35){
   DrivingForward(75);
   //If the distance in front of the car is more than 35cm it keeps driving forward at 75% speed (the speed can be changed)
  }
  else{
    Stop();
    delay(300);
    //If the distance in front of the car becomes less than 35cm it stops and:
    
    turnRight();
    int distanceRight = readDistance();
      if (distanceRight>1500 || distanceRight<0){
          distanceRight = readDistance();}  
    Serial.print("Distance right:");
    Serial.print(distanceRight);
    Serial.println("cm");
    delay(300);
    //The car faces right and measures the distance to the right. If the distance is too high or too low (suggesting a problem with the measurement) it measures again, in an attempt to minimise the possible problems. It then proceeds to print the value to the serial monitor.
    
    turnLeft();
    turnLeft();
    int distanceLeft = readDistance();
      if (distanceLeft>1500 || distanceLeft<0){
          distanceLeft = readDistance();}
    Serial.print("Distance left:");
    Serial.print(distanceLeft);
    Serial.println("cm");
    delay(300);
    //The car turns left and measures the distance to the left. If the distance is too high or too low (suggesting a problem with the measurement) it measures again. It then proceeds to print the value to the serial monitor.

 
    if((distanceLeft>distanceRight) && (distanceLeft>distanceFront)){
      DrivingForward(75);
    //The car checks if the distance to the left is greater than that to the right and to the front. If that is the case, it starts driving to the left.
      
    }
    else if((distanceRight>distanceLeft) && (distanceRight>distanceFront)){
      turnRight();
      turnRight();
      DrivingForward(75);
    //The car checks if the distance to the right is greater than that to the left and to the front. If that is the case, it starts driving to the right.
      
    }
    else{
      turnRight();
      DrivingBackward(50);
      delay(1500);
      turnRight();
      //if the distance to the right and to the left is both less than that in front (meaning it's less than 35cm => it's surrounded and the only way out is back), then the car ratates to its original orientation and drives back.
    }
  }
 
}
 
 
void forward1(int fSpeed1){
  digitalWrite(pinMotor1f, HIGH);
  digitalWrite(pinMotor1b, LOW);
  analogWrite(pinSpeed1, fSpeed1);
  //Standart function for driving the right motors forward with a desired speed put in the function brackets
}
 
void backward1(int bSpeed1){
  digitalWrite(pinMotor1f, LOW);
  digitalWrite(pinMotor1b, HIGH);
  analogWrite(pinSpeed1, bSpeed1);
  //Standart function for driving the right motors backward with a desired speed put in the function brackets 
}
 
void forward2(int fSpeed2){
  digitalWrite(pinMotor2f, HIGH);
  digitalWrite(pinMotor2b, LOW);
  analogWrite(pinSpeed2, fSpeed2);
  //Standart function for driving the left motors forward with a desired speed put in the function brackets
}
 
void backward2(int bSpeed2){
  digitalWrite(pinMotor2f, LOW);
  digitalWrite(pinMotor2b, HIGH);
  analogWrite(pinSpeed2, bSpeed2);
  //Standart function for driving the left motors backward with a desired speed put in the function brackets
}
 
void DrivingForward(int speeed1){
  //Standart function for driving forward with a constant speed given as a percentage in the function brackets
  motorSpeed1 = 0.01*speeed1;
  motorSpeed2 = 0.01*speeed1;
  forward1(motorSpeed1*255);
  forward2(motorSpeed2*255); 
}
 
void DrivingBackward(int speeed2){
  //Standart function for driving backward with a constant speed given as a percentage in the function brackets
  motorSpeed1 = 0.01*speeed2;
  motorSpeed2 = 0.01*speeed2;
  backward1(motorSpeed1*255);
  backward2(motorSpeed2*255); 
}
 
void Stop(){
  //Function that stops the car
  motorSpeed1 = 0.0;
  motorSpeed2 = 0.0;
  forward1(motorSpeed1*255);
  forward2(motorSpeed2*255);
}
 
void turnRight(){
  //Function that makes the car turn right by 90 degrees
  motorSpeed1 = 1.0;
  motorSpeed2 = 1.0;
  forward1(motorSpeed1*255);
  backward2(motorSpeed2*255);
  delay(250);
  Stop();
}
 
void turnLeft(){
  //Function that makes the car turn left by 90 degrees
  motorSpeed1 = 1.0;
  motorSpeed2 = 1.0;
  backward1(motorSpeed1*255);
  forward2(motorSpeed2*255);
  delay(250);
  Stop();
}
 
int readDistance(){
  //Function that reads the distance with the ultrasonic sensor and returns its value
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  long echoPinReading = pulseIn(echoPin, HIGH);
  int distance = echoPinReading*0.034/2;
  return distance;
}