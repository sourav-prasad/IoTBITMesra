
/* 
 *  This source code is for IOT based home automation
 *   
 *  Date - 06-04-2019 02:00 PM
 *  @Sourav
 *  @Version 1
 *  Tested
 */
#include "DHT.h"
#define DHTPIN 44
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
float h=0.0,t=0.0,f=0.0;


byte IRS=43;
byte pos = 0;

#include <LiquidCrystal.h>
const int rs = 46, en = 47, d4 = 48, d5 = 49, d6 = 50, d7 = 51;
#define Disp_Switch 52
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


byte  RoomLight= 45,gateLED =53 ,FAN_Switch= 12,RLS=42,RL=0,Fan=0;


void setup()
{
  lcd.begin(16, 2);
  dht.begin(); 
  Serial.begin(9600); 
  pinMode(Disp_Switch, OUTPUT);  pinMode(gateLED, OUTPUT); pinMode(FAN_Switch, OUTPUT);

  pinMode(IRS,INPUT);
  pinMode(RLS,INPUT);
  digitalWrite(RoomLight,HIGH);
  
}



void loop()
{
  if(!digitalRead(IRS))
  {
  digitalWrite(RoomLight,LOW);RL=1;
  digitalWrite(gateLED,HIGH);
  delay(1000);
  digitalWrite(gateLED,LOW);
  check_T_and_H();
  display_TempAndHumidity();
  } 
  
  if(RL==1 && digitalRead(RLS))
  {
  digitalWrite(RoomLight,HIGH);RL=0;
  }
  //Fan control 
  if(Fan)
  {
   check_T_and_H(); 
  }
}

//============================== Functiion for calculating humidity and temperature========================
void check_T_and_H()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) 
    {
      Serial.println(F("Failed to read from DHT sensor!"));
    }

  if(t<25)
    {
      digitalWrite(FAN_Switch,HIGH);//Turns off Fan
      Fan=0;
    }
  if ( t>25)
    {
      digitalWrite(FAN_Switch,LOW);// Turns on Fan
      Fan=1;
    }
}
//=======================================Function for printing Temperature and humidity ================================
void display_TempAndHumidity()
{
  digitalWrite(Disp_Switch,HIGH);
  lcd.clear(); lcd.print("Humidity is"); lcd.setCursor(1, 1); lcd.print("      "); lcd.print(h);
  delay(2000);
  
  // printing tem in celcius
  lcd.clear(); lcd.print("Temp in *c"); lcd.setCursor(1, 1); lcd.print("      "); lcd.print(t);
  delay(2000);
   
  // Read temperature as Fahrenheit 
  lcd.clear();lcd.print("Temp in *F");lcd.setCursor(1, 1);lcd.print("        ");lcd.print(f); 
  delay(2000);
  digitalWrite(Disp_Switch,LOW); lcd.clear();
  
}
