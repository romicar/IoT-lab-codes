
#include "Tone.h"
#define buzzer  5 
#define touch 13 //touch 4 



 
int val = 0;
void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(buzzer, LOW); // turn the sensor OFF
}

void loop() {
  val = touchRead(touch);
  //digitalWrite(touch, LOW);   
  Serial.println(val);
  delay(1000);
  if(val<20){
    //digitalWrite(touch, HIGH);
    tone(5,10000,2000,0);
    noTone(5,0);
    //digitalWrite(touch, LOW);
  }
}
