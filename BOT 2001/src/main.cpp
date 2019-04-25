#include <Arduino.h>

#include <Handles.h>

#include <WebServer.h>
#include <WiFiAP.h>

#include <web.h>

WebServer server(80);

char* ssid = "minedu";
char* password = "Nova2015";

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void notFound() {
  server.send(404, "text/plain", "oops");
}

void handleTemp() {
  sensors.requestTemperatures();
  temp0 = sensors.getTempCByIndex(0);
  char thing[] = "mete o codigo html para o notifier aqui";
  server.send(200, "text/html", thing);
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
  server.on("/temp", handleTemp);
  server.on("/luzON", autoLightsON);
  server.on("/luzOFF", autoLightsOFF);
  server.on("/estarON", autoEstarON);
  server.on("/estarOFF", autoEstarOFF);
  server.on("/jantarON", autoJantarON);
  server.on("/jantarOFF", autoJantarOFF);
  server.on("/aquecON", autoHeatON);
  server.on("/aquecOFF", autoHeatOFF);
  server.on("/20", newTemp20);
  server.on("/21", newTemp21);
  server.on("/22", newTemp22);
  server.on("/23", newTemp23);
  server.on("/24", newTemp24);
  server.on("/25", newTemp25);
  server.on("/26", newTemp26);
  server.on("/27", newTemp27);
  server.on("/28", newTemp28);
  server.on("/29", newTemp29);
  server.on("/30", newTemp30);
  server.on("/salaON", salaON);
  server.on("/salaOFF", salaOFF);
  server.on("/cozinhaON", cozinhaON);
  server.on("/cozinhaOFF", cozinhaOFF);
  server.on("/quartoON", quartoON);
  server.on("/quartoOFF", quartoOFF);
  server.on("/banhoON", banhoON);
  server.on("/banhoOFF", banhoOFF);
  server.on("/l0ON", l0ON);
  server.on("/l0OFF", l0OFF);
  server.on("/l1ON", l1ON);
  server.on("/l1OFF", l1OFF);
  server.on("/l2ON", l2ON);
  server.on("/l2OFF", l2OFF);
  server.on("/l3ON", l3ON);
  server.on("/l3OFF", l3OFF);
  server.on("/l4ON", l4ON);
  server.on("/l4OFF", l4OFF);
  server.on("/l5ON", l5ON);
  server.on("/l5OFF", l5OFF);
  server.on("/l6ON", l6ON);
  server.on("/l6OFF", l6OFF);
  server.on("/l7ON", l7ON);
  server.on("/l7OFF", l7OFF);
  server.on("/cortinaOFF", cortinaOFF);
  server.on("/cortinaON", cortinaON);
  server.on("/d0ON", d0ON);
  server.on("/d0OFF", d0OFF);
  server.on("/d1ON", d1ON);
  server.on("/d1OFF", d1OFF);
  server.on("/d2ON", d2ON);
  server.on("/d2OFF", d2OFF);
  server.on("/d3ON", d3ON);
  server.on("/d3OFF", d3OFF);
  server.on("/d4ON", d4ON);
  server.on("/d4OFF", d4OFF);
  server.on("/d5ON", d5ON);
  server.on("/d5OFF", d5OFF);
  server.on("/d6ON", d6ON);
  server.on("/d6OFF", d6OFF);
  server.onNotFound(notFound);
}

void loop() {
  toRefresh();
  server.handleClient();
  if (server.client() == "") {
    placaOn = false;
    quartoOn = false;
    banhoOn = false;
    autoEstar = true;
    autoJantar = true;
    livingRoom = false;
    kitchen = false;
    bedroom = false;
    bathroom = false;
    temp = 25;
  }
}