#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTPIN 2 //GPIO2 or D4

const char* server = "api.thingspeak.com";
const char *ssid =  "SONU_HOME";
const char *pass =  "08121999";

String Write_apiKey = "BBL7F2486J9RY603";
String Read_apikey = "QLH0FHBUQ2T7YAH9";
 
DHT dht_sensor(DHTPIN,DHT11);
WiFiClient client;
void setup() 
{
       Serial.begin(115200);
       delay(20);
       dht_sensor.begin();
       WiFi.begin(ssid, pass);
}
 
void loop() 
{
      float h = dht_sensor.readHumidity();
      float t = dht_sensor.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("PLEASE CHEAK THE CONNECTION OF YOUR SENSOR AGAIN!");
                      return;
                 }
                         if (client.connect(server,80))
                      {  
                             String postStr = Write_apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
                              //data is sending to the thinkspeak server
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+Write_apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             //Printing on serial montor
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
  
  delay(1000);
}
