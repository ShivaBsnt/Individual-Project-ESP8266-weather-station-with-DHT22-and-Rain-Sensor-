#include "DHTesp.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

const char* ssid = "WirelessNet_ClassicTech";                                  
const char* pass = "c.ron@ldo72056";                              
const char* auth = "PhC70X-ycdO68TEjBICSXy7Gv2wSoT1U";

//Initializing Rain sensor
int sensorPin = A0;    
int outputPin = D3;      
int sensorValue = 0; 

DHTesp dht;
BlynkTimer timer;
void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)");
  pinMode(outputPin, OUTPUT);
  dht.setup(2, DHTesp::DHT22); 
  Blynk.begin(auth,ssid,pass);
  Blynk.notify("weather station ready to go!!!");
  Blynk.syncAll(); // Connect DHT sensor to GPIO 5
 
  timer.setInterval(1000L, myTimerEvent);
}
void loop()
{
  Blynk.run();//  Running Blynk app
  timer.run(); // Initiates BlynkTimer 
}
void myTimerEvent(){
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" celcius, Humidity: ");
  Serial.print(humidity, 1);
  
  sensorValue = analogRead(sensorPin);//Reading data from rain sensor
  Serial.print(" %, Rain: ");
  Serial.println(sensorValue); 
  
if (sensorValue>=700){
digitalWrite(outputPin, LOW);
  }
  else{
  Blynk.notify("Huge rainfall is detected!!!");
  Serial.print("rain is detected");
  digitalWrite(outputPin, HIGH); 
  }
Blynk.virtualWrite(V2, humidity); 
Blynk.virtualWrite(V1, sensorValue);
Blynk.virtualWrite(V3, temperature);
  }
  
