#include <WebServer.h>
#include <WiFiClient.h>
#include <WiFi.h>
#define BUZZER_PIN 18
#define LED_PIN 15

const char *ssid = "Galaxy M319E1D";
const char *password = "gewi4493";

WiFiServer server(80);

String page = "";
String data = "";

void setup()
{
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
 /* pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);*/

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  data = "";

  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
  //  server.handleClient();
  WiFiClient client = server.available();
  data = "";
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.print(c);
        if (c == '\n')
        {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (data.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
//            client.println("Connection: close");
            // HTML CODE
          //  client.println("<h1><a href=\"/LH\">LED HIGH</a></h1><br>");
          //  client.println("<h1><a href=\"/LL\">LED LOW</a></h1><br>");
            client.println("<h1><button><a href=\"/BH\">BUZZ H</a></button></h1><br>");
            client.println("<h1><button><a href=\"/BL\">BUZZ LOW</a></button></h1><br>");
            //            client.println("Connection: close");
            client.println();
            break;
          }
          else
          {
            data = "";
          }
        }
        else if(c!='\r')
        {
          data += c;
          /*if (data.endsWith("GET /LL"))
            {
              digitalWrite(LED_PIN, LOW);
            }
            if (data.endsWith("GET /LH"))
            {
              digitalWrite(LED_PIN, HIGH);
            }*/
            if (data.endsWith("GET /BL"))
            {
              digitalWrite(BUZZER_PIN, HIGH);
            }
            if (data.endsWith("GET /BH"))
            {
              digitalWrite(BUZZER_PIN, LOW);
            }
        }
      }
    }
  }
}
