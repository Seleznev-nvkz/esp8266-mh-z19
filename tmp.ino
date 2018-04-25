#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Sensors.h"
#include "WiFiCredentials.h"

Sensors* sensors;

IPAddress ip(192, 168, 1, 148);
ESP8266WebServer server(80);

void handleRoot() {
  String msg = "<meta http-equiv=\"refresh\" content=\"10\"><h3>ESP8266 + MH-Z19</h3><p>temp - ";
  msg += String(sensors->get_temp());
  msg += " C</p><p>humidity - ";
  msg += String(sensors->get_hum());
  msg += " %</p><p>CO2 - ";
  msg += String(sensors->get_co2());
  msg += " ppm</p>";
  server.send(200, "text/html", msg);
}

void jsonRoot() {
  String msg = "{\"temp\":";
  msg += String(sensors->get_temp());
  msg += ",\"co2\":";
  msg += String(sensors->get_co2());
  msg += ",\"hum\":";
  msg += String(sensors->get_hum());
  msg += "}";
  server.send(200, "application/json", msg);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start Setup");

  sensors = new Sensors();

  WiFi.config(IPAddress(192, 168, 88, 192), IPAddress(192, 168, 88, 1), IPAddress(255, 255, 255, 0));
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Try to connect");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/json", jsonRoot);
  server.begin();
  Serial.println("Finished Setup");
}

void loop() {
  server.handleClient();
}

