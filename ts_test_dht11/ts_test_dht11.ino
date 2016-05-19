#include <HttpClient.h>
#include <Bridge.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 8

DHT dht(DHTPIN, DHTTYPE);

String thingSpeakAddress = "http://api.thingspeak.com/update?";
String writeAPIKey = "key=Ajouter votre clé ici"; // 
String tsfield1Name = "&field1=";
String tsfield2Name = "&field2=";

void setup()
{
  Bridge.begin();
  dht.begin();
  delay(1000);
}

void loop()
{
  HttpClient client;  

  // lecture de l'humidité et de la température
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // creation d'une requette pour le serveur ThingSpeak 
  String request_string = thingSpeakAddress + writeAPIKey + tsfield1Name +String(t, DEC) + tsfield2Name + String(h, DEC);
  
  // envoi de la requette
  client.get(request_string);
  
  // délais de rafrichissement du serveur
  delay(15000);
}
