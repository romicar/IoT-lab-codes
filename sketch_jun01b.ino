#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int trigPin = 5; // transmitter which emits sound
const int echoPin = 18;
const int buzzerPin = 25;// receiver that receives reflected sound

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
//#define CM_TO_INCH 0.393701

long duration; // time between transmission and reception
long threshold;
long distance; // centimeters

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("yatharth and vanshika");
  Serial.println("Pair device with bluetooth.");

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, HIGH);
  
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

  if(SerialBT.available()) {
    threshold = SerialBT.read();
    Serial.write(threshold);
  }
  
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * (SOUND_SPEED) / 2;
  if(distance>400) // ultrasound maximum range roughly 500
  {
    SerialBT.print("Distance: ");
  SerialBT.println("400");
  distance=400;
  }
  else
  {
  // Prints the distance on the Serial Monitor
  SerialBT.print("Distance in cm: ");
  SerialBT.println(distance);
  }
  if(threshold < distance)
  {
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
  }


  
  delay(1000);
}
