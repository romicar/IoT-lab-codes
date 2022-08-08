#include "WiFi.h"
#include "WebServer.h"

const char* ssid = "Galaxy M319E1D";
const char* password =  "gewi4493";

WebServer server(80);
IPAddress ip;

//#define BUZZER_PIN
//#define LED_PIN
#define PIR_pin 17

String page = "";
String x;
String data = "";

void setup() {
 
  Serial.begin(9600);

  pinMode(PIR_pin, INPUT);
  
  WiFi.begin(ssid, password);

 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  ip = WiFi.localIP();
  Serial.println(ip);


  server.on("/data.txt",[](){
    if(x == "Motion Detected")
    {
      data = "Motion Detected";
    }
    else
    {
      data = "No Motion Detected";
    }
    server.send(200, "text/html", data);
  });
  

server.on("/", [](){
    page += "<h1>PIR Sensor Status</h1><h1>Detected:</h1><hl id=\"data\">""</h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval (function() {loadData('data.txt', updateData)}, 1000);\r\n";
    page += "function loadData(url, callback) {\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function() {\r\n";
    page += "if(this.readyState == 4 && this.status == 200) {\r\n";
    page += "callback.apply(xhttp);\r\n";
    page += "}\r\n";
    page += "};\r\n";
    page += "xhttp.open('GET', url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData() {\r\n";
    page += " document.getElementById('data').innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send( 200, "text/html", page);
  });

  server.begin();
}

void loop() {
  server.handleClient();

  if(digitalRead(PIR_pin)==HIGH)
    x = "Motion Detected";
   else
    x = "No Motion Detected";
   Serial.println(x);
   delay(500);
}
