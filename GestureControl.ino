//MrHobbyelectronics
//www.mrhobbytronics.com
//www.YouTube.com/Mrhobbyelectronics
//#include "Keyboard.h"
//#include <Keyboard.h>
//#include <HID.h>

//Sensor 1
int trigPin1 = 2;
int echoPin1 = 3;

//Sensor 2
int trigPin2 = 4;
int echoPin2 = 5;

long duration1, cm1;
long duration2, cm2;

//Status variables
int value1;
int value2;

void setup() {
  Serial.begin(9600);
  //Keyboard.begin();

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop(){
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
// convert the time into a distance
  cm1 = (duration1/2) / 29.1;
  
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  // convert the time into a distance
  cm2 = (duration2/2) / 29.1;
  
delay(300);

Serial.println(cm1);
Serial.println(cm2);
  //set value 1 true
  if (cm1 < 20){
    value1 = 1;
    delay(100);
  }
  
  if (cm2 < 20 && value1 == 1){
    value1 = 0;
    goLeft();
    delay(100);
    
  }

  //set value 2 true
  if (cm2 < 20){
    value2 = 1;
    delay(100);
  }
  
  if (cm1 < 20 && value2 == 1){
    value2 = 0;
    goRight();
    delay(100);
  }
}

void goLeft(){
  Serial.println("Im left");
  //Keyboard.print("Youtube.com/MrHobbyElectronics");
  //Keyboard.write(KEY_RETURN);
    delay(100);
}

void goRight(){
  Serial.println("Im right");
    //Keyboard.print("www.mrhobbytronics.com");
  //Keyboard.write(KEY_RETURN);
    delay(100);  
}
