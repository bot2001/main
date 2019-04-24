#include <Arduino.h>

#include <WiFiGeneric.h>
#include <WebServer.h>
#include <WiFiAP.h>

#include <index.h>

WebServer server(80);

const char* ssid = "minedu";
const char* password = "Nova2015";

void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server ok");
}



void loop() {
  server.handleClient();
}