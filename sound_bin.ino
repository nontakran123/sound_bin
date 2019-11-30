#include<Servo.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(0, 1); // RX, TX
Servo servo;
DFRobotDFPlayerMini myDFPlayer;
int const trigPin = 6;
int const echoPin = 5;

void printDetail(uint8_t type, int value);

void setup(){
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT);     
servo.attach(9);
{
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
}
}

void loop(){       
int duration, distance;
digitalWrite(trigPin, HIGH); 
delay(1);
digitalWrite(trigPin, LOW);// Measure the pulse input in echo pin
duration = pulseIn(echoPin, HIGH);// Distance is half the duration devided by 29.1 (from datasheet)
distance = (duration/2) / 29.1;// if distance less than 0.5 meter and more than 0 (0 or less means over range) 
if(distance <= 21 && distance >= 0){
  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);  //Play the first mp3
  delay(5000);
  }else{
    myDFPlayer.volume(0);}
}
