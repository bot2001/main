int input;

#include <DallasTemperature.h>
#include <ESP32Servo.h>
#include <ShiftRegister74HC595.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double temp;  // temperatura ideal
double temp0; // baseline exterior
double temp1; // sala
double temp2; // quarto
double temp3; // casa de banho

const int m1a = 32;
const int m1b = 33;
const int m2a = 14;
const int m2b = 12;
const int m7a = 22;
const int m7b = 23;

Servo servo0;
const int servo0pin = 4;
Servo servo3;
const int servo3pin = 16;
Servo servo4;
const int servo4pin = 17;
Servo servo5;
const int servo5pin = 5;
Servo servo6;
const int servo6pin = 18;

const int relay1 = 2;
const int relay2 = 19;
const int relay3 = 21;

const int l0 = 36;
int light0;
const int l1 = 39;
int light1;

ShiftRegister74HC595 shift(1, 26, 27, 25);

const int fire = 13;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(600000);

  Serial.println("Hello world");
  sensors.begin();

  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m7a, OUTPUT);
  pinMode(m7b, OUTPUT);

  servo0.attach(servo0pin);
  servo3.attach(servo3pin);
  servo4.attach(servo4pin);
  servo5.attach(servo5pin);
  servo6.attach(servo6pin);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);

  pinMode(fire, OUTPUT);

  printOptions();

  digitalWrite(m1a, LOW);
  digitalWrite(m1b, LOW);
  digitalWrite(m2a, LOW);
  digitalWrite(m2b, LOW);
  digitalWrite(m7a, LOW);
  digitalWrite(m7b, LOW);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.parseInt();
    Serial.println(input);
    serialFlush();
    switch (input) {
      case 0:
        printOptions();
        break;
      case 1:
        sensors.requestTemperatures();
        Serial.println(sensors.getTempCByIndex(0));
        Serial.println(sensors.getTempCByIndex(1));
        Serial.println(sensors.getTempCByIndex(2));
        Serial.println(sensors.getTempCByIndex(3));
        break;
      case 2:
        Serial.println(analogRead(l0));
        break;
      case 3:
        Serial.println(analogRead(l1));
        break;
      case 4:
        digitalWrite(relay1, LOW);
        break;
      case 5:
        digitalWrite(relay1, HIGH);
        break;
      case 6:
        digitalWrite(relay2, LOW);
        break;
      case 7:
        digitalWrite(relay2, HIGH);
        break;
      case 8:
        digitalWrite(relay3, LOW);
        break;
      case 9:
        digitalWrite(relay3, HIGH);
        break;
      case 10:
        servo0.write(70);
        break;
      case 11:
        servo0.write(160);
        break;
      case 12:
        digitalWrite(m1a, HIGH);
        delay(3500);
        digitalWrite(m1a, LOW);
        break;
      case 13:
        digitalWrite(m1b, HIGH);
        delay(3500);
        digitalWrite(m1b, LOW);
        break;
      case 14:
        digitalWrite(m2a, HIGH);
        delay(4300);
        digitalWrite(m2a, LOW);
        break;
      case 15:
        digitalWrite(m2b, HIGH);
        delay(5000);
        digitalWrite(m2b, LOW);
        break;
      case 16:
        servo3.write(55);
        break;
      case 17:
        servo3.write(150);
        break;
      case 18:
        servo4.write(25);
        break;
      case 19:
        servo4.write(133);
        break;
      case 20:
        servo5.write(131);
        break;
      case 21:
        servo5.write(40);
        break;
      case 22:
        servo6.write(55);
        break;
      case 23:
        servo6.write(150);
        break;
      case 24:
        shift.set(0, HIGH);
        break;
      case 25:
        shift.set(0, LOW);
        break;
      case 26:
        shift.set(1, HIGH);
        break;
      case 27:
        shift.set(1, LOW);
        break;
      case 28:
        shift.set(2, HIGH);
        break;
      case 29:
        shift.set(2, LOW);
        break;
      case 30:
        shift.set(3, HIGH);
        break;
      case 31:
        shift.set(3, LOW);
        break;
      case 32:
        shift.set(4, HIGH);
        break;
      case 33:
        shift.set(4, LOW);
        break;
      case 34:
        shift.set(5, HIGH);
        break;
      case 35:
        shift.set(5, LOW);
        break;
      case 36:
        shift.set(6, HIGH);
        break;
      case 37:
        shift.set(6, LOW);
        break;
      case 38:
        shift.set(7, HIGH);
        break;
      case 39:
        shift.set(7, LOW);
        break;
      case 40:
        digitalWrite(m7b, HIGH);
        delay(4000);
        digitalWrite(m7b, LOW);
        break;
      case 41:
        digitalWrite(m7a, HIGH);
        delay(3500);
        digitalWrite(m7a, LOW);
        break;
      case 42:
        digitalWrite(fire, HIGH);
        break;
      case 43:
        digitalWrite(fire, LOW);
        break;
    }
  }
}

void printOptions() {
  Serial.println("Olá");
  Serial.println("1 - temperaturas");
  Serial.println("2 - luz 0");
  Serial.println("3 - luz 1");
  Serial.println("4 - ligar placa de Peltier");
  Serial.println("5 - desligar placa de Peltier");
  Serial.println("6 - ligar resistência do quarto");
  Serial.println("7 - desligar resistência do quarto");
  Serial.println("8 - ligar resistência da casa de banho");
  Serial.println("9 - desligar resistência da casa de banho");
  Serial.println("10 - abrir porta de entrada");
  Serial.println("11 - fechar porta de entrada");
  Serial.println("12 - abrir porta da sala");
  Serial.println("13 - fechar porta da sala");
  Serial.println("14 - abrir porta da sala/cozinha");
  Serial.println("15 - fechar porta da sala/cozinha");
  Serial.println("16 - abrir porta da cozinha");
  Serial.println("17 - fechar porta da cozinha");
  Serial.println("18 - abrir porta do quarto");
  Serial.println("19 - fechar porta do quarto");
  Serial.println("20 - abrir porta do quarto/casa de banho");
  Serial.println("21 - fechar porta do quarto/casa de banho");
  Serial.println("22 - abrir porta da casa de banho");
  Serial.println("23 - fechar porta da casa de banho");
  Serial.println("24 - ligar luz do hall");
  Serial.println("25 - desligar luz do hall");
  Serial.println("26 - ligar luz da sala de estar");
  Serial.println("27 - desligar luz da sala de estar");
  Serial.println("28 - ligar luz da sala de jantar");
  Serial.println("29 - desligar luz da sala de jantar");
  Serial.println("30 - ligar luz da cozinha");
  Serial.println("31 - desligar luz da cozinha");
  Serial.println("32 - ligar luz do quarto");
  Serial.println("33 - desligar luz do quarto");
  Serial.println("34 - ligar luz da casa de banho");
  Serial.println("35 - desligar luz da casa de banho");
  Serial.println("36 - ligar luz do armário do hall");
  Serial.println("37 - desligar luz do armário do hall");
  Serial.println("38 - ligar luz do guarda-vestidos");
  Serial.println("39 - desligar luz do guarda-vestidos");
  Serial.println("40 - abrir cortinas");
  Serial.println("41 - fechar cortinas");
  Serial.println("42 - ligar lareira");
  Serial.println("43 - desligar lareira");
}

void serialFlush() {
  // chamar esta função SEMPRE no fim do tratamento do input
  while (Serial.available() > 0) {
    char c = Serial.read();
  }
}
