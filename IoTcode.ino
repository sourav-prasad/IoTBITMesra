#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
 
//Replace your wifi credentials here
const char* ssid     = "NYU";
const char* password = "bimstec1";
 
//change your channel number here
unsigned long channel = 756465;
 
//1,2 and 3 are channel fields. You don't need to change if you are following this tutorial. However, you can modify it according to your application
unsigned int led1 = 1; 
unsigned int led2 = 2; 

WiFiClient  client;
 
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  digitalWrite(D1, 1);
  digitalWrite(D2, 1);

  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);
 
}

 
void loop() {

  //get the last data of the fields
  int led_1 = ThingSpeak.readFloatField(channel, led1);
  int led_2 = ThingSpeak.readFloatField(channel, led2);

  if(led_1 == 0){
    digitalWrite(D1, 1);
    Serial.println("D1 is Off..!");
  }
  else if(led_1 == 1){
    digitalWrite(D1, 0);
    Serial.println("D1 is ON..!");
  }
  if(led_2 == 0){
    digitalWrite(D2, 1);
    Serial.println("D2 is Off..!");
  }
  else if(led_2 == 1){
    digitalWrite(D2, 0);
    Serial.println("D2 is ON..!");
  }
    
  Serial.println(led_1);
  Serial.println(led_2);
  delay(5000);
}
