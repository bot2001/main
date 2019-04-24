#include <Arduino.h>

#include <kittycat.h>

#include <WiFiGeneric.h>
#include <WebServer.h>
#include <WiFiAP.h>

#include <web.h>

WebServer server(80);

char* ssid = "minedu";
char* password = "Nova2015";

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
  server.begin();
  Serial.println("HTTP server ok");
  toDo();

  server.on("/", handleRoot);
}

void loop() {
  toRefresh();
  server.handleClient();
}