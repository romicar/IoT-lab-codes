#include <string.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>
WiFiClient  client;
unsigned long counterChannelNumber = 1764266;                // Channel ID
const char * myCounterReadAPIKey = "TKN642TK1PEG90IJ";      // Read API Key
const int FieldNumber1 = 1;                                 // The field you wish to read
const int FieldNumber2 = 2;                                 // The field you wish to read

void setup()
{
  pinMode(5,OUTPUT);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("wifi name", "password");           // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() 
{
 int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
 Serial.println(A);
 digitalWrite(5,A);
}
