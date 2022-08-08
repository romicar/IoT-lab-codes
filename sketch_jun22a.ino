#include "WiFi.h"
#include "HTTPClient.h"
#include "time.h"
#include <ArduinoJson.h>
#include "DHT.h"

#define DHT_PIN 27
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

char* ssid = "Galaxy F42 5G5634";
char* pass = "rxof7629";
String cse_ip = "192.168.189.193"; // YOUR IP from ipconfig/ifconfig
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "dht__";
String cnt = "node1";

void createCi(String val)
{
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");

  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");
  Serial.println(code);
  if (code == -1)
  {
    Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }

  http.end();
}

void setup()
{
    Serial.begin(9600);
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Connecting to WiFi...");
      delay(1000);
    }
    Serial.println("WiFi Connected!");
    
  dht.begin();
}

void loop()
{
  float temperature_reading = dht.readTemperature();
  Serial.println(temperature_reading);
//  createCI(temperature_reading);
if (!isnan(temperature_reading))createCi(String(temperature_reading));
  delay(3000);
}
