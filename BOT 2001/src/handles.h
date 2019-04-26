#include <Kittycat.h>

void autoLightsON() {
    timerLight.start();
    server.send(200, "text/html", MAIN_page);
}

void autoLightsOFF() {
    timerLight.stop();
    server.send(200, "text/html", MAIN_page);
}

void autoEstarON() {
    autoEstar = true;
    server.send(200, "text/html", MAIN_page);
}

void autoEstarOFF() {
    autoEstar = false;
    server.send(200, "text/html", MAIN_page);
}

void autoJantarON() {
    autoJantar = true;
    server.send(200, "text/html", MAIN_page);
}

void autoJantarOFF() {
    autoJantar = false;
    server.send(200, "text/html", MAIN_page);
}

void autoHeatON() {
    timerRelay.start();
    server.send(200, "text/html", MAIN_page);
}

void autoHeatOFF() {
    timerRelay.stop();
    server.send(200, "text/html", MAIN_page);
}

void newTemp20() {
    temp = 20;
    server.send(200, "text/html", MAIN_page);
}
void newTemp21() {
    temp = 21;
    server.send(200, "text/html", MAIN_page);
}
void newTemp22() {
    temp = 22;
    server.send(200, "text/html", MAIN_page);
}
void newTemp23() {
    temp = 23;
    server.send(200, "text/html", MAIN_page);
}
void newTemp24() {
    temp = 24;
    server.send(200, "text/html", MAIN_page);
}
void newTemp25() {
    temp = 25;
    server.send(200, "text/html", MAIN_page);
}
void newTemp26() {
    temp = 26;
    server.send(200, "text/html", MAIN_page);
}
void newTemp27() {
    temp = 27;
    server.send(200, "text/html", MAIN_page);
}
void newTemp28() {
    temp = 28;
    server.send(200, "text/html", MAIN_page);
}
void newTemp29() {
    temp = 29;
    server.send(200, "text/html", MAIN_page);
}
void newTemp30() {
    temp = 30;
    server.send(200, "text/html", MAIN_page);
}

void salaON() {
    livingRoom = true;
    server.send(200, "text/html", MAIN_page);
}

void salaOFF() {
    livingRoom = false;
    server.send(200, "text/html", MAIN_page);
}

void cozinhaON() {
    kitchen = true;
    server.send(200, "text/html", MAIN_page);
}

void cozinhaOFF() {
    kitchen = false;
    server.send(200, "text/html", MAIN_page);
}

void quartoON() {
    bedroom = true;
    server.send(200, "text/html", MAIN_page);
}

void quartoOFF() {
    bedroom = false;
    server.send(200, "text/html", MAIN_page);
}

void banhoON() {
    bathroom = true;
    server.send(200, "text/html", MAIN_page);
}

void banhoOFF() {
    bathroom = false;
    server.send(200, "text/html", MAIN_page);
}

void l0ON() {
    light(0, true);
    server.send(200, "text/html", MAIN_page);
}

void l0OFF() {
    light(0, false);
    server.send(200, "text/html", MAIN_page);
}

void l1ON() {
    light(1, true);
    server.send(200, "text/html", MAIN_page);
}

void l1OFF() {
    light(1, false);
    server.send(200, "text/html", MAIN_page);
}

void l2ON() {
    light(2, true);
    server.send(200, "text/html", MAIN_page);
}

void l2OFF() {
    light(2, false);
    server.send(200, "text/html", MAIN_page);
}

void l3ON() {
    light(3, true);
    server.send(200, "text/html", MAIN_page);
}

void l3OFF() {
    light(3, false);
    server.send(200, "text/html", MAIN_page);
}

void l4ON() {
    light(4, true);
    server.send(200, "text/html", MAIN_page);
}

void l4OFF() {
    light(4, false);
    server.send(200, "text/html", MAIN_page);
}

void l5ON() {
    light(5, true);
    server.send(200, "text/html", MAIN_page);
}

void l5OFF() {
    light(5, false);
    server.send(200, "text/html", MAIN_page);
}

void l6ON() {
    light(6, true);
    server.send(200, "text/html", MAIN_page);
}

void l6OFF() {
    light(6, false);
    server.send(200, "text/html", MAIN_page);
}

void l7ON() {
    light(7, true);
    server.send(200, "text/html", MAIN_page);
}

void l7OFF() {
    light(7, false);
    server.send(200, "text/html", MAIN_page);
}

void cortinaON() {
    door(7, true);
    server.send(200, "text/html", MAIN_page);
}

void cortinaOFF() {
    door(7, false);
    server.send(200, "text/html", MAIN_page);
}

void d0ON() {
    door(0, true);
    server.send(200, "text/html", MAIN_page);
}

void d0OFF() {
    door(0, false);
    server.send(200, "text/html", MAIN_page);
}

void d1ON() {
    door(1, true);
    server.send(200, "text/html", MAIN_page);
}

void d1OFF() {
    door(1, false);
    server.send(200, "text/html", MAIN_page);
}

void d2ON() {
    door(2, true);
    server.send(200, "text/html", MAIN_page);
}

void d2OFF() {
    door(2, false);
    server.send(200, "text/html", MAIN_page);
}

void d3ON() {
    door(3, true);
    server.send(200, "text/html", MAIN_page);
}

void d3OFF() {
    door(3, false);
    server.send(200, "text/html", MAIN_page);
}

void d4ON() {
    door(4, true);
    server.send(200, "text/html", MAIN_page);
}

void d4OFF() {
    door(4, false);
    server.send(200, "text/html", MAIN_page);
}

void d5ON() {
    door(5, true);
    server.send(200, "text/html", MAIN_page);
}

void d5OFF() {
    door(5, false);
    server.send(200, "text/html", MAIN_page);
}

void d6ON() {
    door(6, true);
    server.send(200, "text/html", MAIN_page);
}

void d6OFF() {
    door(6, false);
    server.send(200, "text/html", MAIN_page);
}