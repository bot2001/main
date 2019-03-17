#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 34 // temperaturas

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

const int m1a = 32; // motor 1 - porta Hall Sala
const int m1b = 33;
const int m2a = 14; // motor 2 - porta Sala Cozinha
const int m2b = 12;
const int m3a = 15; // motor 3 - cortinas
const int m3b = 2;
  
const int r1 = 25;  // placa de Peltier
const int r2 = 26;  // resistência do quarto
const int r3 = 27;  // resistência da casa de banho

const int l1 = 36;  // 1º sensor de luz
const int l2 = 39;  // 2º sensor de luz

#include <ESP32Servo.h>
Servo entrada;
const int servoPin1 = 4;
Servo cozinha;
const int servoPin2 = 16;
Servo quarto;
const int servoPin3 = 17;
Servo casaBanho;
const int servoPin4 = 5;
Servo casaBanho2;
const int servoPin5 = 18;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello");

  sensors.begin();
  
  pinMode(l1, INPUT);
  pinMode(l2, INPUT);

  entrada.attach(servoPin1);
  cozinha.attach(servoPin2);
  quarto.attach(servoPin3);
  casaBanho.attach(servoPin4);
  casaBanho2.attach(servoPin5);

  pinMode(m1a, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2a, OUTPUT);
  pinMode(m2b, OUTPUT);
  pinMode(m3a, OUTPUT);
  pinMode(m3b, OUTPUT);

  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
}

void loop() {
}
