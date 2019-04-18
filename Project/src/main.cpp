#include <Arduino.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ShiftRegister74HC595.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double temp;  // temperatura ideal
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

bool placaOn = false;
bool quartoOn = false;
bool banhoOn = false;

const int relay1 = 2;
const int relay2 = 19;
const int relay3 = 21;

const int light = 500;  // valor limiar da luz; pode e deve ser ajustado
const int l0 = 36;
int lightO;
const int l1 = 39;
int lightI;

ShiftRegister74HC595 shift(2, 26, 27, 25);

bool livingRoom = false;
bool livingRoomStatus = false;
bool kitchen = false;
bool kitchenStatus = false;
bool bedroom = false;
bool bedroomStatus = false;
bool bathroom = false;
bool bathroomStatus = false;

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

void checkInput() {
  if (livingRoomStatus != livingRoom) {
    if (livingRoom) {
      placaOn = true;
      door(1, false);
    }
    else {
      placaOn = false;
      door(1, true);
    }
    livingRoomStatus = livingRoom;
  }

  if (kitchenStatus != kitchen) {
    if (kitchen) {
      door(2, true);
      door(3, false);
    }
    else {
      if (livingRoom) {
        door(2, false);
      }
      else {
        door(2, true);
      }
    }
    kitchenStatus = kitchen;
  }

  if (bedroomStatus != bedroom) {
    if (bedroom) {
      quartoOn = true;
      door(3, false);
      door(6, false);
    }
    else {
      quartoOn = false;
    }
    bedroomStatus = bedroom;
  }

  if (bathroomStatus != bathroom) {
    if (bathroom) {
      banhoOn = true;
      door(5, false);
      door(6, false);
    }
    else {
      banhoOn = false;
    }
  }
}

void checkLights() {
  lightO = analogRead(l0);
  lightI = analogRead(l1);
  // comparar os inputs e agir em conformidade
}

void checkRelay() {
  if (placaOn && temp1<temp) {
    digitalWrite(relay1, HIGH);
  }
  else {
    digitalWrite(relay1, LOW);
  }

  if (quartoOn && temp2<temp) {
    digitalWrite(relay2, HIGH);
  }
  else {
    digitalWrite(relay2, LOW);
  }

  if (banhoOn && temp3<temp) {
    digitalWrite(relay3, HIGH);
  }
  else {
    digitalWrite(relay3, LOW);
  }
}

void loop() {
  //checkInput();
  //checkRelay();
  //checkLights();
}

void printTemperatures() {  //só para teste mesmo
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