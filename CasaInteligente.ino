#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4

#define ON   0
#define OFF  1

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int servoPinQ = 5;
Servo quarto;
const int servoPinCB = 6;
Servo casaBanho;
const int servoPinHC = 7;
Servo hallCozinha;
const int servoPinHS = 8;
Servo hallSala;
const int servoPinSC = 9;
Servo salaCozinha;

const int relay1 = 10;
const int relay2 = 11;
const int relay3 = 12;
const int relay4 = 13;

boolean placaOn = false;
boolean resQuartoOn = false;
boolean resBanhoOn = false;

const int tempValue = 25;

const int lightPin = 0;
int light;

boolean control = true;

int input = 0;

boolean Fopen = false;

boolean autoLights = false;

void setup() {
  door('a', false);
  door('b', false);
  door('c', false);
  door('d', false);
  door('e', false);

  pinMode(4, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  relayStatus(1, OFF);
  relayStatus(2, OFF);
  relayStatus(3, OFF);
  relayStatus(4, OFF);

  quarto.attach(servoPinQ);
  casaBanho.attach(servoPinCB);
  hallCozinha.attach(servoPinHC);
  hallSala.attach(servoPinHS);
  salaCozinha.attach(servoPinSC);

  // IMPORTANTE NÃO APAGAR
  // 9600 para pc
  Serial.begin(9600);
  Serial.setTimeout(600000);

  sensors.begin();

  printMenu();
  Serial.println();
  Serial.println("10 - verificar a temperatura");
  Serial.println("11 - reset/ shut down");
  Serial.println("12 - temperatura exterior");
  Serial.println("13 - luzes modo automático");
  Serial.println("14 - luzes modo manual");
  Serial.println();
  Serial.println("20 - abrir a porta A");
  Serial.println("21 - fechar a porta A");
  Serial.println("22 - abrir a porta B");
  Serial.println("23 - fechar a porta B");
  Serial.println("24 - abrir a porta C");
  Serial.println("25 - fechar a porta C");
  Serial.println("26 - abrir a porta D");
  Serial.println("27 - fechar a porta D");
  Serial.println("28 - abrir a porta E");
  Serial.println("29 - fechar a porta E");
  Serial.println();
  Serial.println("30 - ligar a Placa de Peltier");
  Serial.println("31 - desligar a Placa de Peltier");
  Serial.println("32 - ligar a resistência do quarto");
  Serial.println("33 - desligar a resistência do quarto");
  Serial.println("34 - ligar a resistência da casa de banho");
  Serial.println("35 - desligar a resistência da casa de banho");
  Serial.println();
  Serial.println("36 - abrir a cortina");
  Serial.println("37 - fechar a cortina");
  Serial.println("38 - ligar as luzes");
  Serial.println("39 - desligar as luzes");
  Serial.println();
}

void door(char door, boolean state) {
  switch (door) {
    case 'a':
      if (state) {
        salaCozinha.write(180);
      }
      else {
        salaCozinha.write(95);
      }
      break;
    case 'b':
      if (state) {
        hallSala.write(80);
      }
      else {
        hallSala.write(180);
      }
      break;
    case 'c':
      if (state) {
        hallCozinha.write(90);
      }
      else {
        hallCozinha.write(170);
      }
      break;
    case 'd':
      if (state) {
        quarto.write(0);
      }
      else {
        quarto.write(85);
      }
      break;
    case 'e':
      if (state) {
        casaBanho.write(180);
      }
      else {
        casaBanho.write(88);
      }
      break;
    case 'f':
      if (state) {
        if (Fopen != true) {
          // abrir a porta F
          digitalWrite(3, HIGH);
          delay(2000);
          digitalWrite(3, LOW);
          Fopen = true;
        }
      }
      else {
        if (Fopen) {
          // fechar a porta F
          digitalWrite(2, HIGH);
          delay(1500);
          digitalWrite(2, LOW);
          Fopen = false;
        }
      }
      break;
  }
}

void checkPlaca(boolean state) {
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(1);
  if ((state == true) and (temp < tempValue)) {
    relayStatus(4, ON);
  }
  else {
    relayStatus(4, OFF);
  }
}

void checkQuarto(boolean state) {
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(0);
  if ((state == true) and (temp < tempValue)) {
    relayStatus(3, ON);
  }
  else {
    relayStatus(3, OFF);
  }
}

void checkBanho(boolean state) {
  sensors.requestTemperatures();
  double temp = sensors.getTempCByIndex(2);
  if ((state == true) and (temp < tempValue)) {
    relayStatus(2, ON);
  }
  else {
    relayStatus(2, OFF);
  }
}

void checkLight() {
  if (autoLights) {
    light = analogRead(lightPin);
    //Serial.println(light);
    if (light <= 60) {
      relayStatus(1, ON);
      door('f', false);
    }
    else {
      relayStatus(1, OFF);
      door('f', true);
    }
  }
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

void printMenu() {
  Serial.println("Opções: ");
  Serial.println("1 - aquecer apenas a sala");
  Serial.println("2 - aquecer a sala e a cozinha");
  Serial.println("3 - aquecer a sala e o quarto");
  Serial.println("4 - aquecer a sala, cozinha e quarto");
  Serial.println("5 - aquecer o quarto");
  Serial.println("6 - aquecer a casa de banho");
  Serial.println("7 - desligar aquecimento sala");
  Serial.println("8 - desligar aquecimento quarto");
  Serial.println("9 - desligar aquecimento casa de banho");
}

void loop() {
  while (control) {
    checkPlaca(placaOn);
    checkQuarto(resQuartoOn);
    checkBanho(resBanhoOn);
    checkLight();
    if (Serial.available() > 0) {
      control = false;
    }
  }
  input = Serial.parseInt();
  serialFlush();
  control = true;
  switch (input) {
    case 0:
      printMenu();
      break;
    case 1:
      door('a', false);
      door('b', false);
      placaOn = true;
      Serial.println("Aquecer apenas a sala");
      break;
    case 2:
      door('a', true);
      door('b', false);
      door('c', false);
      placaOn = true;
      Serial.println("Aquecer a sala e a cozinha");
      break;
    case 3:
      door('a', false);
      door('b', true);
      door('c', false);
      door('d', true);
      door('e', false);
      placaOn = true;
      resQuartoOn = true;
      Serial.println("Aquecer a sala e o quarto");
      break;
    case 4:
      door('a', true);
      door('b', true);
      door('c', true);
      door('d', true);
      door('e', false);
      placaOn = true;
      resQuartoOn = true;
      Serial.println("Aquecer a sala, cozinha e quarto");
      break;
    case 5:
      door('d', false);
      resQuartoOn = true;
      Serial.println("Aquecer o quarto");
      break;
    case 6:
      door('e', false);
      resBanhoOn = true;
      Serial.println("Aquecer a casa de banho");
      break;
    case 7:
      placaOn = false;
      Serial.println("Desligar aquecimento sala");
      break;
    case 8:
      resQuartoOn = false;
      Serial.println("Desligar aquecimento quarto");
      break;
    case 9:
      resBanhoOn = false;
      Serial.println("Desligar aquecimento casa de banho");
      break;
    case 10:
      sensors.requestTemperatures();
      Serial.print("Exterior ");
      Serial.println(sensors.getTempCByIndex(3));
      Serial.print("Sala ");
      Serial.println(sensors.getTempCByIndex(1));
      Serial.print("Quarto ");
      Serial.println(sensors.getTempCByIndex(0));
      Serial.print("Casa de banho ");
      Serial.println(sensors.getTempCByIndex(2));
      Serial.println();
      break;
    case 11:
      door('a', false);
      door('b', false);
      door('c', false);
      door('d', false);
      door('e', false);
      //door('f', false);
      placaOn = false;
      resQuartoOn = false;
      resBanhoOn = false;
      relayStatus(1, OFF);
      break;
    case 12:
      sensors.requestTemperatures();
      Serial.print("Temperatura exterior: ");
      Serial.println(sensors.getTempCByIndex(3));
      break;
    case 13:
      autoLights = true;
      Serial.println("As luzes estão em modo automático.");
      break;
    case 14:
      autoLights = false;
      Serial.println("As luzes estão em modo manual.");
      break;
    case 20:
      door('a', true);
      break;
    case 21:
      door('a', false);
      break;
    case 22:
      door('b', true);
      break;
    case 23:
      door('b', false);
      break;
    case 24:
      door('c', true);
      break;
    case 25:
      door('c', false);
      break;
    case 26:
      door('d', true);
      break;
    case 27:
      door('d', false);
      break;
    case 28:
      door('e', true);
      break;
    case 29:
      door('e', false);
      break;
    case 30:
      placaOn = true;
      break;
    case 31:
      placaOn = false;
      break;
    case 32:
      resQuartoOn = true;
      break;
    case 33:
      resQuartoOn = false;
      break;
    case 34:
      resBanhoOn = true;
      break;
    case 35:
      resBanhoOn = false;
      break;
    case 36:
      door('f', true);
      break;
    case 37:
      door('f', false);
      break;
    case 38:
      relayStatus(1, ON);
      break;
    case 39:
      relayStatus(1, OFF);
      break;
    default:
      Serial.println("Erro");
      printMenu();
      break;
  }
}

void relayStatus(int whichOne, unsigned char what) {
  switch (whichOne) {
    case 1:
      digitalWrite(relay1, what);
      break;
    case 2:
      digitalWrite(relay2, what);
      break;
    case 3:
      digitalWrite(relay3, what);
      break;
    case 4:
      digitalWrite(relay4, what);
      break;
  }
}
