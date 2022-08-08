#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int trigPin = 5; // transmitter which emits sound
const int echoPin = 2; // receiver that receives reflected sound

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_M 0.01
#define BuzzerPin 4

long duration; // time between transmission and reception
float distanceCm;
float distanceM;

float parameterCm=400;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("romica & charu");
  Serial.println("Pair device with bluetooth.");
  pinMode(17,OUTPUT);
  pinMode(21,OUTPUT);
  digitalWrite(17,HIGH);
  digitalWrite(21,LOW);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(trigPin, LOW); // short low pulse to ensure you get a clean high pulse
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15); // 10 microseconds pulse emits ultrasound
  // ultrasound is upto several GHz
  // so we use 10 mcirosecond = 100kHz
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to meter
  distanceM = distanceCm * CM_TO_M;
  SerialBT.print("Distance in centimeters");
  SerialBT.println(distanceCm);

  SerialBT.print("Distance in metre");
  SerialBT.println(distanceM);

  if(parameterCm > distanceCm)
  {
    digitalWrite(BuzzerPin, LOW);
    SerialBT.println( "too close");
  }
  
  else {
    digitalWrite(BuzzerPin, HIGH);
    SerialBT.println("distance greater than 4");
    
  }
  
  
 
  delay(1000);
}
