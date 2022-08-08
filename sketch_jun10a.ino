#include <ThingSpeak.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include <WiFi.h>

#define SIGNAL_PIN 33

const char *ssid = "Galaxy F42 5G5634";
const char *password = "rxof7629";

const char* server = "mqtt3.thingspeak.com"; //Change
char mqttUserName[] = "mwa0000026745003";
char mqttPass[] = "MQTTPASS"; // API
long channelID = 1764266;
char writeAPI[] = "PPMXRJMEFKUSWG9P";

int fieldsToPublish[8] = {1,0,0,0,0,0,0,0};

// Setting up WiFi Client object
WiFiClient client;
// Setting up Publisher Sub-Client Object
PubSubClient mqttClient(server, 1883, client);//server,port,client

void setup() {
  Serial.begin(115200);

  //Setting up Wifi Connection
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Setting up MQTT Broker details
  mqttClient.setServer(server, 1883); //set MQTT broker details 
}

String str_connect = "mwa0000026745003";

void loop() {
  while(!mqttClient.connected()) //check if mqtt client is connected
  //if not connected call mqttClient.connect function
  {
    Serial.println("Connect Loop");
    //client ID,username,password
    Serial.println(mqttClient.connect("LTAGLwcYNBUIIAUxEhYNIyU","LTAGLwcYNBUIIAUxEhYNIyU","aIwxKtxgwzrkIBFlqr4bIEwv"));
    Serial.println(mqttClient.connected());
    //mqttConnect();
  }
  Serial.println("MQTT Connected");
  mqttClient.loop(); //calling loop to maintain connection with server

  delay(1000);
  
  int value = analogRead(SIGNAL_PIN);//reading integer data from D1
  
  Serial.print("Value :");
  Serial.println(value);


  mqttPublish(channelID, writeAPI, value); //publish on mqtt server
  delay(1000);
//call the mqtt publish function
}

void mqttPublish(long pubChannelID, char* pubWriteAPIKey, int value)
{
  String dataString = "field1=" + String(value);

  for(int i=0;i<8;++i)
  {
    if(fieldsToPublish[i])
    {
      Serial.println(dataString);
      String topicString = "channels/" +String(pubChannelID)+ "/publish";
      mqttClient.publish(topicString.c_str(),dataString.c_str());
      Serial.print("pubChannelID :");
      Serial.println(pubChannelID); //printing the pubChannel ID
      Serial.println("");
    }
  }
}
