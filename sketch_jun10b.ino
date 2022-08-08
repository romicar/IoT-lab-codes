#include <PubSubClient.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <WebServer.h>

int led_pin = 5;

long channelID = 1764340;

const char* api_key = "9QXK8D4CKXFDAWWF";

const char* ssid = "ASUS_X00TD";
const char* pass = "z@idhotspot";

WiFiClient client;

WebServer server(80);

String SendHTML(void){
 String ptr = "<!DOCTYPE html> <html>\n";
 ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
 ptr +="<title>LED Control</title>\n";
 ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
 ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
 ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
 ptr +=".button-on {background-color: #1abc9c;}\n";
 ptr +=".button-on:active {background-color: #16a085;}\n";
 ptr +=".button-off {background-color: #34495e;}\n";
 ptr +=".button-off:active {background-color: #2c3e50;}\n";
 ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
 ptr +="</style>\n";
 ptr +="</head>\n";
 ptr +="<body>\n";
 ptr +="<h1>ESP8266 with ThingSpeak Server</h1>\n";
 ptr +="<h3>Using Station(STA) Mode</h3>\n";
 ptr +="<h4>Control status For D1</h4>\n";
 ptr +="<a class=\"button button-on\" href=\"https://api.thingspeak.com/update?api_key=ZIPERNKS5LI66JUD&field1=0\">ON</a>\n";
 ptr +="<a class=\"button button-off\" href=\"https://api.thingspeak.com/update?api_key=ZIPERNKS5LI66JUD&field1=1\">OFF</a>\n";
 ptr +="</body>\n";
 ptr +="</html>\n";
 return ptr;
}

void f(){
  server.send(200,"text/html",SendHTML());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting wifi");
    delay(1000);
  }
  Serial.println("Wifi COnnected!");
  server.on("/",f);
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
  server.begin();
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
   server.handleClient();
   int in_data = ThingSpeak.readIntField(channelID, 1, api_key);
   int statusCode = ThingSpeak.getLastReadStatus();
   Serial.println(String("Status code: ") + String(statusCode));
   Serial.print("Server returned ");
   Serial.println(in_data);
   if (in_data==1){
    digitalWrite(led_pin, LOW);
   }else{
     digitalWrite(led_pin, HIGH);
   }
   delay(500);
}
