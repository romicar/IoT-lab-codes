#define powerpin  4 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define signalpin 25 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin

int val = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
  pinMode(powerpin, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(powerpin, LOW); // turn the sensor OFF
}

void loop() {
  digitalWrite(powerpin, HIGH);  // turn the sensor ON
  delay(10);                      // wait 10 milliseconds
  val = analogRead(signalpin);
  digitalWrite(powerpin, LOW);   

  Serial.print("The water sensor value: ");
  Serial.println(val);

  delay(1000);
}
