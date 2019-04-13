#include <Arduino.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <Shifty.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double temp0; // baseline exterior
double temp1; // sala
double temp2; // quarto
double temp3; // casa de banho

bool open1 = false;
const int m1a = 32;
const int m1b = 33;
bool open2 = false;
const int m2a = 14;
const int m2b = 12;
bool open7 = false;
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

const int l1 = 36;
float lightO;
const int l2 = 39;
float lightI;

Shifty shift;

void setup() {
  Serial.begin(115200);
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

  shift.setBitCount(8);
  // Set the clock, data, and latch pins
  shift.setPins(27, 25, 26);

}

void loop() {

}

void door(int door, bool state) {
  switch (door) {
    case 0:
      if (state) {
        servo0.write(90);
      }
      else {
        servo0.write(0);
      }
    break;
    case 3:
      if (state) {
        servo3.write(90);
      }
      else {
        servo3.write(0);
      }    
    break;
    case 4:
      if (state) {
        servo4.write(90);
      }
      else {
        servo4.write(0);
      }
    break;
    case 5:
      if (state) {
        servo5.write(90);
      }
      else {
        servo5.write(0);
      }
    break;
    case 6:
      if (state) {
        servo6.write(90);
      }
      else {
        servo6.write(0);
      }
    break;
    case 1:
      if (state) {
        if (!open1) {
          digitalWrite(m1a, HIGH);
          delay(3500);
          digitalWrite(m1a, LOW);
        }
      }
      else {
        if (open1) {
          digitalWrite(m1b, HIGH);
          delay(3500);
          digitalWrite(m1b, LOW);          
        }
      }
    break;
    case 2:
      if (state) {
        if (!open2) {
          digitalWrite(m2a, HIGH);
          delay(3500);
          digitalWrite(m2a, LOW);
        }
      }
      else {
        if (open2) {
          digitalWrite(m2b, HIGH);
          delay(3500);
          digitalWrite(m2b, LOW);          
        }
      }
    break;
    case 7:
      if (state) {
        if (!open7) {
          digitalWrite(m7a, HIGH);
          delay(3500);
          digitalWrite(m7a, LOW);
        }
      }
      else {
        if (open7) {
          digitalWrite(m7b, HIGH);
          delay(3500);
          digitalWrite(m7b, LOW);          
        }
      }
    break;
  }
}

void printTemperatures() {
  sensors.requestTemperatures();
  temp0 = sensors.getTempCByIndex(0);
  temp1 = sensors.getTempCByIndex(1);
  temp2 = sensors.getTempCByIndex(2);
  temp3 = sensors.getTempCByIndex(3);
  Serial.println("Temperatures:");
  Serial.println(temp0);
  Serial.println(temp1);
  Serial.println(temp2);
  Serial.println(temp3);
}