#include <Arduino.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ShiftRegister74HC595.h>
#include <Ticker.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double temp = 25;  // temperatura ideal
int temp0; // baseline exterior
double temp1; // sala
double temp1Sum;
double temp2; // quarto
double temp2Sum;
double temp3; // casa de banho
double temp3Sum;
int n = 0;

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

const int fire = 13;

const int light0T = 600;
const int l0 = 36;
int light0;
const int light1T = 500;
const int l1 = 39;
int light1;
int b = 0;

bool autoEstar = true;
bool autoJantar = true;

ShiftRegister74HC595 shift(1, 26, 27, 25);

bool livingRoom = false;
bool kitchen = false;
bool bedroom = false;
bool bathroom = false;

bool livingRoomStatus = false;
bool kitchenStatus = false;
bool bedroomStatus = false;
bool bathroomStatus = false;

void door1F();
void door2F();
void door3F();
void door4F();
void door5F();
void door6F();

Ticker door1(door1F, 60000, 1, MILLIS);
Ticker door2(door2F, 60000, 1, MILLIS);
Ticker door3(door3F, 60000, 1, MILLIS);
Ticker door4(door4F, 60000, 1, MILLIS);
Ticker door5(door5F, 60000, 1, MILLIS);
Ticker door6(door6F, 60000, 1, MILLIS);

void door(int door, bool state) {
  switch (door) {
    case 0:
      if (state) {
        if (servo0.read() != 70) {
          servo0.write(70);
        }
      }
      else {
        if (servo0.read() != 160) {
          servo0.write(160);
        }
      }
    break;
    case 3:
      if (state) {
        if (servo3.read() != 55) {
          servo3.write(55);
          if (kitchen) { door3.start(); }
        }
      }
      else {
        if (servo3.read() != 150) {
          servo3.write(150);
          if (door3.state() == RUNNING) { door3.stop(); }
        }
      }    
    break;
    case 4:
      if (state) {
        if (servo4.read() != 25) {
          servo4.write(25);
          if (bedroom) { door4.start(); }
        }
      }
      else {
        if (servo4.read() != 133) {
          servo4.write(133);
          if (door4.state() == RUNNING) { door4.stop(); }
        }
      }
    break;
    case 5:
      if (state) {
        if (servo5.read() != 131) {
          servo5.write(131);
          if (bedroom || bathroom) { door5.start(); }
        }
      }
      else {
        if (servo5.read() != 40) {
          servo5.write(40);
          if (door5.state() == RUNNING) { door5.stop(); }
        }
      }
    break;
    case 6:
      if (state) {
        if (servo6.read() != 55) {
          servo6.write(55);
          if (bathroom) { door6.start(); }
        }
      }
      else {
        if (servo6.read() != 150) {
          servo6.write(150);
          if (door6.state() == RUNNING) { door6.stop(); }
        }
      }
    break;
    case 1:
      if (state) {
        if (!open1) {
          digitalWrite(m1a, HIGH);
          delay(3500);
          digitalWrite(m1a, LOW);
          if (livingRoom) { door1.start(); }
        }
      }
      else {
        if (open1) {
          digitalWrite(m1b, HIGH);
          delay(3500);
          digitalWrite(m1b, LOW);   
          if (door1.state() == RUNNING) { door1.stop(); }       
        }
      }
    break;
    case 2:
      if (state) {
        if (!open2) {
          digitalWrite(m2a, HIGH);
          delay(4300);
          digitalWrite(m2a, LOW);
          if (livingRoom && !kitchen) { door2.start(); }
        }
      }
      else {
        if (open2) {
          digitalWrite(m2b, HIGH);
          delay(5000);
          digitalWrite(m2b, LOW);
          if (door2.state() == RUNNING) { door2.stop(); }          
        }
      }
    break;
    case 7:
      if (state) {
        if (!open7) {
          digitalWrite(m7a, HIGH);
          delay(4000);
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

void door1F() {
  door(1, false);
}
void door2F() {
  door(2, false);
}
void door3F() {
  door(3, false);
}
void door4F() {
  door(4, false);
}
void door5F() {
  door(5, false);
}
void door6F() {
  door(6, false);
}

void checkInput() {
  if (livingRoomStatus != livingRoom) {
    if (livingRoom) {
      placaOn = true;
      digitalWrite(fire, HIGH);
      door(1, false);
    }
    else {
      placaOn = false;
      digitalWrite(fire, LOW);
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

void checkRelay() {
  sensors.requestTemperatures();
  temp1 = sensors.getTempCByIndex(1);
  temp2 = sensors.getTempCByIndex(2);
  temp3 = sensors.getTempCByIndex(3);

  n =+ 1;
  temp1Sum =+ temp1;
  temp2Sum =+ temp2;
  temp3Sum =+ temp3;

  if (n == 30) {  // calcula a temperatura média a cada 30 segundos, para evitar flutuações
    temp1 = temp1Sum/n;
    temp2 = temp2Sum/n;
    temp3 = temp3Sum/n;
    n = 0;
    if (placaOn && temp1<temp) {
      digitalWrite(relay1, LOW);
    }
    else {
      digitalWrite(relay1, HIGH);
    }
    if (quartoOn && temp2<temp) {
      digitalWrite(relay2, LOW);
    }
    else {
      digitalWrite(relay2, HIGH);
    }
    if (banhoOn && temp3<temp) {
      digitalWrite(relay3, LOW);
    }
    else {
      digitalWrite(relay3, HIGH);
    }
  }

}

void checkLights() {
  b =+ 1;
  light0 =+ analogRead(l0);
  light1 =+ analogRead(l1);
  if (b == 60) {  // minuto a minuto
    light0 = light0/b;
    light1 = light1/b;
    b = 0;
    if (light0 > light0T) {
      door(7, true);
      // desligar as luzes
      if (autoEstar) {
        shift.set(6, LOW);
      }
      if (autoJantar) {
        shift.set(7, LOW);
      }
    }
    if (light1 < light1T) {
      door(7, false);
      // ligar as luzes
      if (autoEstar) {
        shift.set(6, HIGH);
      }
      if (autoJantar) {
        shift.set(7, HIGH);
      }
    }
  }
}

void cupboardF() {
  shift.set(2, LOW);
}

void closetF() {
  shift.set(1, LOW);
}

Ticker timerRelay(checkRelay, 1000, 0, MILLIS);
Ticker timerLight(checkLights, 1000, 0, MILLIS);

Ticker cupboard(cupboardF, 60000, 1, MILLIS);
Ticker closet(closetF, 120000, 1, MILLIS);

void light(int which, bool state) {
  if (state) {
    switch (which) {
      case 0:
        shift.set(0, HIGH);
        break;
      case 1:
        shift.set(6, HIGH);
        break;
      case 2:
        shift.set(7, HIGH);
        break;
      case 3:
        shift.set(3, HIGH);
        break;
      case 4:
        shift.set(4, HIGH);
        break;
      case 5:
        shift.set(5, HIGH);
        break;
      case 6:
        shift.set(2, HIGH);
        cupboard.start();
        break;
      case 7:
        shift.set(1, HIGH);
        closet.start();
        break;
    }
  }
  else {
    switch (which) {
      case 0:
        shift.set(0, LOW);
        break;
      case 1:
        shift.set(6, LOW);
        break;
      case 2:
        shift.set(7, LOW);
        break;
      case 3:
        shift.set(3, LOW);
        break;
      case 4:
        shift.set(4, LOW);
        break;
      case 5:
        shift.set(5, LOW);
        break;
      case 6:
        shift.set(2, LOW);
        cupboard.stop();
        break;
      case 7:
        shift.set(1, LOW);
        closet.stop();
        break;
    }
  }
}

void toDo() {
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

  timerLight.start();
  timerRelay.start();
}

void toRefresh() {
  sensors.requestTemperatures();
  temp0 = sensors.getTempCByIndex(0);
  checkInput();
  if (timerRelay.state() == RUNNING) {
    timerRelay.update();
  }
  if (timerLight.state() == RUNNING) {
    timerLight.update();
  }
  if (cupboard.state() == RUNNING) {
    cupboard.update();
  }
  if (closet.state() == RUNNING) {
    closet.update();
  }
  if (door1.state() == RUNNING) {
    door1.update();
  }
  if (door2.state() == RUNNING) {
    door2.update();
  }
  if (door3.state() == RUNNING) {
    door3.update();
  }
  if (door4.state() == RUNNING) {
    door4.update();
  }
  if (door5.state() == RUNNING) {
    door5.update();
  }
  if (door6.state() == RUNNING) {
    door6.update();
  }
}