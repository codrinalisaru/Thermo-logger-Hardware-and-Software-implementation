#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#define DHTTYPE DHT22
#define DHTPIN D2 // D3
#define relay D1 // D2
#define tsetID "5e13967b73efc34aeb2be9bf"
DHT dht(DHTPIN, DHTTYPE, 22);
float h, t; // Values read from sensor
#include "UbidotsMicroESP8266.h"
#define TOKEN "<TOKEN>" // Ubidots TOKEN
#define WIFISSID "<SSID>"
#define PASSWORD "<PSW>"
Ubidots client(TOKEN);
unsigned long lastMillis = 0;
float tset = 21.;
int tset3 = 250;
byte tset1, tset2;
float dt = 0.25;
#define adr1 10
#define adr2 11
byte centrala = 0;
float tmin = 17.;
float tmax = 29.;
int relayState;
void setup() {
delay(10);
Serial.begin(9600);
Serial.println("--------------------------");
Serial.println("NodeMCU - IoT");
pinMode(relay, OUTPUT);
digitalWrite(relay, LOW);
dht.begin();
EEPROM.begin(512);
tset1 = EEPROM.read(adr1);
tset2 = EEPROM.read(adr2);
EEPROM.end();
if (tset > tmax) tset = tmax;
if (tset < tmin) tset = tmin;
EEPROM.begin(512);
EEPROM.put(adr2, tset2);
EEPROM.put(adr1, tset1);
EEPROM.commit();
EEPROM.end();
tset3 = tset * 10.;
tset2 = tset3 / 256;
tset1 = tset3 - 256 * tset2;
Serial.print("tset = ");
Serial.println(tset);
Serial.println(" ------------------- ");
h = dht.readHumidity();
t = dht.readTemperature();
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" degrees Celsius Humidity: ");
Serial.println(h);
client.wifiConnection(WIFISSID, PASSWORD);
}
void loop() {
if (millis() - lastMillis > 2000) {
Serial.print("Temperature: ");
Serial.print(t);
Serial.print(" degrees Celsius, Humidity: ");
Serial.println(h);
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
dht.begin();
h = dht.readHumidity();
t = dht.readTemperature(false);
return;
}
lastMillis = millis();
h = dht.readHumidity(); // Read humidity (percent)
t = dht.readTemperature(false); // Read temperature as Celsius
client.add("Temperature", t);
client.add("Humidity", h);
client.add("Centrala", centrala);
client.add("SweetSpot", tset);
client.sendAll(true);
tset = client.getValue(tsetID); //tset ID
tset3 = tset * 10.;
tset2 = tset3 / 256;
tset1 = tset3 - 256 * tset2;
EEPROM.begin(512);
EEPROM.put(adr2, tset2);
EEPROM.put(adr1, tset1);
EEPROM.end();
EEPROM.commit();
Serial.print("Temperatura setata = ");
Serial.println(tset);
}
if (t > tset + dt) {
digitalWrite(relay, LOW); // relay OFF
Serial.println("Prea cald!");
centrala = 0;
} else if (t < tset - dt) {
digitalWrite(relay, HIGH); // relay ON
Serial.println("Prea rece!");
centrala = 1;
}
}