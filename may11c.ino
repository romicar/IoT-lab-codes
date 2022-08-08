

void setup() {
  Serial.begin(9600);
  pinMode(25, OUTPUT); // signal pin
  pinMode(4, OUTPUT); // power for sensor pin
  digitalWrite(15, LOW);
  pinMode(5, OUTPUT); //buzzer pin
  digitalWrite(5,LOW);//BUZZER PIN
  pinMode(13, OUTPUT); //touch pin
  digitalWrite(17,LOW);//GROUND FOR SENSOR
}

double reqwaterlevel = 10;
int touch;

void loop() {

  
  touch = touchRead(13);
  if(touch < 40)
  {
      digitalWrite(4, HIGH);
  double waterlevel = analogRead(25);
  waterlevel = (waterlevel*40)/4096;
  Serial.print("Water Level: ");
  Serial.println(waterlevel);
  digitalWrite(4, LOW);
  
    //digitalWrite(5, HIGH);
    reqwaterlevel = 13.5;
    
    Serial.print("Required water level: ");
    Serial.println(reqwaterlevel);
    if(waterlevel < reqwaterlevel)
    {
      digitalWrite(5, LOW);
    }
    else
    {
      digitalWrite(5, HIGH);
    }

    
  }
 

  delay(500);

}
