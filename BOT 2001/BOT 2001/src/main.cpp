#include <Arduino.h>

#include <WebServer.h>
#include <WiFiAP.h>

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include <DallasTemperature.h>
#include <Servo.h>
#include <ShiftRegister74HC595.h>
#include <Ticker.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int temp = 25;  // temperatura ideal
double temp0; // baseline exterior
double temp1; // sala
double temp1Sum;
double temp2; // quarto
double temp2Sum;
double temp3; // casa de banho
double temp3Sum;
int n = 0;

bool open1 = true;
const int m1a = 14;
const int m1b = 12;
bool open2 = true;
const int m2a = 33;
const int m2b = 32;
bool open7 = false;
const int m7a = 23;
const int m7b = 22;

Servo servo0;
const int servo0pin = 4;
bool open0 = false;
Servo servo3;
const int servo3pin = 17;
bool open3 = false;
Servo servo4;
const int servo4pin = 18;
bool open4 = false;
Servo servo5;
const int servo5pin = 5;
bool open5 = false;
Servo servo6;
const int servo6pin = 16;
bool open6 = false;

bool placaOn = false;
bool quartoOn = false;
bool banhoOn = false;

const int relay1 = 21;
const int relay2 = 2;
const int relay3 = 19;

const int fire = 13;

const int light0T = 600;
const int l0 = 36;
int light0 = 0;
const int light1T = 500;
const int l1 = 39;
int light1 = 0;
int b = 0;

bool autoLights = true;
bool autoEstar = true;
bool autoJantar = true;

ShiftRegister74HC595 shift(1, 26, 27, 25);

bool autoHeat = true;
bool livingRoom = false;
bool kitchen = false;
bool bedroom = false;
bool bathroom = false;

bool livingRoomStatus = false;
bool kitchenStatus = false;
bool bedroomStatus = false;
bool bathroomStatus = false;

bool on0 = false;
bool on1 = false;
bool on2 = false;
bool on3 = false;
bool on4 = false;
bool on5 = false;

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
        if (!open0) {
          servo0.write(70);
          open0 = true;
        }
      }
      else {
        if (open0) {
          servo0.write(160);
          open0 = false;
        }
      }
    break;
    case 3:
      if (state) {
        if (!open3) {
          servo3.write(55);
          if (kitchen) { door3.start();
                        Serial.println("A porta da cozinha vai fechar"); }
          open3 = true;
        }
      }
      else {
        if (open3) {
          servo3.write(150);
          if (door3.state() == RUNNING) { door3.stop(); }
          open3 = false;
        }
      }    
    break;
    case 4:
      if (state) {
        if (!open4) {
          servo4.write(23);
          if (bedroom) { door4.start(); 
                        Serial.println("A porta do quarto vai fechar");}
          open4 = true;
        }
      }
      else {
        if (open4) {
          servo4.write(113);
          if (door4.state() == RUNNING) { door4.stop(); }
          open4 = false;
        }
      }
    break;
    case 5:
      if (state) {
        if (!open5) {
          servo5.write(141);
          if (bedroom || bathroom) { door5.start();
                                    Serial.println("A porta do quarto/casa de banho vai fechar"); }
          open5 = true;
        }
      }
      else {
        if (open5) {
          servo5.write(40);
          if (door5.state() == RUNNING) { door5.stop(); }
          open5 = false;
        }
      }
    break;
    case 6:
      if (state) {
        if (!open6) {
          servo6.write(150);
          if (bathroom) { door6.start();
                        Serial.println("A porta da casa de banho vai fechar"); }
          open6 = true;
        }
      }
      else {
        if (open6) {
          servo6.write(55);
          if (door6.state() == RUNNING) { door6.stop(); }
          open6 = false;
        }
      }
    break;
    case 1:
      if (state) {
        if (!open1) {
          digitalWrite(m1a, HIGH);
          delay(5000);
          digitalWrite(m1a, LOW);
          if (livingRoom) { door1.start(); 
                          Serial.println("A porta da sala vai fechar"); }
          open1 = true;
        }
      }
      else {
        if (open1) {
          digitalWrite(m1b, HIGH);
          delay(5000);
          digitalWrite(m1b, LOW);   
          if (door1.state() == RUNNING) { door1.stop(); }
          open1 = false;       
        }
      }
    break;
    case 2:
      if (state) {
        if (!open2) {
          digitalWrite(m2a, HIGH);
          delay(5000);
          digitalWrite(m2a, LOW);
          if (livingRoom && !kitchen) { door2.start();
                                      Serial.println("A porta da sala/cozinha vai fechar"); }
          open2 = true;
        }
      }
      else {
        if (open2) {
          digitalWrite(m2b, HIGH);
          delay(5000);
          digitalWrite(m2b, LOW);
          if (door2.state() == RUNNING) { door2.stop(); }
          open2 = false;          
        }
      }
    break;
    case 7:
      if (state) {
        if (!open7) {
          digitalWrite(m7a, HIGH);
          delay(4000);
          digitalWrite(m7a, LOW);
          open7 = true;
        }
      }
      else {
        if (open7) {
          digitalWrite(m7b, HIGH);
          delay(3500);
          digitalWrite(m7b, LOW);
          open7 = false;          
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
    bathroomStatus = bathroom;
  }
}

void checkRelay() {
  Serial.println("Temperatures");
  sensors.requestTemperatures();
  temp1 = sensors.getTempCByIndex(3);
  temp2 = sensors.getTempCByIndex(2);
  temp3 = sensors.getTempCByIndex(0);

  n = n + 1;
  temp1Sum = temp1Sum + temp1;
  temp2Sum = temp2Sum + temp2;
  temp3Sum = temp3Sum + temp3;
  Serial.println(n);

  if (n == 30) {  // calcula a temperatura média a cada 30 segundos, para evitar flutuações
    String output;
    temp1 = temp1Sum/n;
    output = "Temperatura 1: ";
    output += temp1;
    Serial.println(output);
    temp2 = temp2Sum/n;
    output = "Temperatura 2: ";
    output += temp2;
    Serial.println(output);
    temp3 = temp3Sum/n;
    output = "Temperatura 3: ";
    output += temp3;
    Serial.println(output);
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
    temp1Sum = 0;
    temp2Sum = 0;
    temp3Sum = 0;
  }

}

void checkLights() {
  Serial.println("Lights");
  b = b + 1;
  light0 = light0 + analogRead(l0);
  light1 = light0 + analogRead(l1);
  if (b == 60) {  // minuto a minuto
    String output;
    light0 = light0/b;
    output = "Luz 0: ";
    output += light0;
    Serial.println(output);
    light1 = light1/b;
    output = "Luz 1: ";
    output += light1;
    Serial.println(output);
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
    light0 = 0;
    light1 = 0;
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
        on0 = true;
        break;
      case 1:
        shift.set(6, HIGH);
        on1 = true;
        break;
      case 2:
        shift.set(7, HIGH);
        on2 = true;
        break;
      case 3:
        shift.set(3, HIGH);
        on3 = true;
        break;
      case 4:
        shift.set(4, HIGH);
        on4 = true;
        break;
      case 5:
        shift.set(5, HIGH);
        on5 = true;
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
        on0 = false;
        break;
      case 1:
        shift.set(6, LOW);
        on1 = false;
        break;
      case 2:
        shift.set(7, LOW);
        on2 = false;
        break;
      case 3:
        shift.set(3, LOW);
        on3 = false;
        break;
      case 4:
        shift.set(4, LOW);
        on4 = false;
        break;
      case 5:
        shift.set(5, LOW);
        on5 = false;
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
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);

  pinMode(fire, OUTPUT);
  digitalWrite(fire, LOW);

  timerLight.start();
  timerRelay.start();
}

void toRefresh() {
  sensors.requestTemperatures();
  temp0 = sensors.getTempCByIndex(1);
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

WebServer server(80);

char* ssid = "MEO-CA2C91";
char* password = "A68245D251";

//char* ssid = "bot2001";
//char* password = "2001bot2001";

String MAINpage = "";

void updateHTML() {
    MAINpage = "<!DOCTYPE html>";
    MAINpage += "<html><head>";
    MAINpage += "<meta name=\'viewport\' content=\'width=device-width, initial-scale=1\'>";
    MAINpage += "<meta http-equiv='refresh'content='30;url=/'>";
    MAINpage += "<title>BOT 2001 Control Page</title>";
    MAINpage += "<link rel=\'icon\' href=\'data:,\'>";
    MAINpage += "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css'>";
    MAINpage += "<script src='https://code.jquery.com/jquery-3.1.1.slim.min.js'></script>";
    MAINpage += "<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js'></script>";
    MAINpage += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js'></script>";
    MAINpage += "<script> ";
    MAINpage += "function alerta(){";
    MAINpage += "document.getElementById('alert').style.display='block'";
    MAINpage += "document.getElementById('alert2').style.display='block'}";
    MAINpage += "</script>";
    MAINpage += "<script> ";
    MAINpage += "function alerta2(){";
    MAINpage += "document.getElementById('alert3').style.display='block'";
    MAINpage += "document.getElementById('alert4').style.display='block'}";
    MAINpage += "</script>";
    MAINpage += "<script  type='text/javascript'> ";
    MAINpage += "function replace() {";
    MAINpage += "var aEl = document.getElementById('replace');";
    MAINpage += "if (document.getElementById('range').textContent == '20'){";
    MAINpage += "aEl.href = '/20';}";
    MAINpage += "else if(document.getElementById('range').textContent == '21'){";
    MAINpage += "aEl.href = '/21';}";
    MAINpage += "else if(document.getElementById('range').textContent == '22'){";
    MAINpage += "aEl.href = '/22';}";
    MAINpage += "else if(document.getElementById('range').textContent == '23'){";
    MAINpage += "aEl.href = '/23';}";
    MAINpage += "else if(document.getElementById('range').textContent == '24'){";
    MAINpage += "aEl.href = '/24';}";
    MAINpage += "else if(document.getElementById('range').textContent == '25'){";
    MAINpage += "aEl.href = '/25';}";
    MAINpage += "else if(document.getElementById('range').textContent == '26'){";
    MAINpage += "aEl.href = '/26';}";
    MAINpage += "else if(document.getElementById('range').textContent == '27'){";
    MAINpage += "aEl.href = '/27';}";
    MAINpage += "else if(document.getElementById('range').textContent == '28'){";
    MAINpage += "aEl.href = '/28';}";
    MAINpage += "else if(document.getElementById('range').textContent == '29'){";
    MAINpage += "aEl.href = '/29';}";
    MAINpage += "else if(document.getElementById('range').textContent == '30'){";
    MAINpage += "aEl.href = '/30';}";
    MAINpage += "}";
    MAINpage += "replace();";
    MAINpage += "</script>";
    MAINpage += "<style>";
    MAINpage += "html{font-family: Helvetica;display: inline-block;margin: 0px auto;text-align: center;}";
    MAINpage += "body{margin:0;padding:0;color: #FFFFFF}";
    MAINpage += ".button{background-color: #4CAF50;border-radius: 5px; border: none;color: white;width: 120px;height: 70px;text-align: center;text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}";
    MAINpage += ".button2{background-color: #555555;border-radius: 5px}";
    MAINpage += ".slider{-webkit-appearance: none;width: 50%;height: 15px;border-radius: 5px;   background: #d3d3d3;outline: none;opacity: 0.7;-webkit-transition: .2s;transition: opacity .2s;}";
    MAINpage += ".slider::-webkit-slider-thumb {-webkit-appearance: none;appearance: none;width: 25px;height: 25px;border-radius: 50%; background: #4CAF50;cursor: pointer;}  ";
    MAINpage += ".slider::-moz-range-thumb {width: 25px;height: 25px;border-radius: 50%;background: #4CAF50;cursor: pointer;}";
    MAINpage += "th{font-size: 24px;font-weight: bold;text-align: center;}";
    MAINpage += "td{text-align: center;font-size: 18px}";
    MAINpage += "table{float:center;width:100%;}";
    MAINpage += ".button3{background:#4caf50;width: 50px;height: 40px;border-radius: 5px;color:#ffffff;display:inline-block;font:normal bold 24px/1 'Calibri', sans-serif;text-align:center;}";
    MAINpage += ".button4{background:#555555;width: 50px;height: 40px;border-radius: 5px;color:#ffffff;display:inline-block;font:normal bold 24px/1 'Calibri', sans-serif;text-align:center;}";
    MAINpage += " .alert {padding: 20px;background-color: #f44336;color: white;}";
    MAINpage += " .closebtn {margin-left: 15px;color: white;font-weight: bold;float: right;font-size: 22px;line-height: 20px;cursor: pointer;transition: 0.3s;}";
    MAINpage += " .closebtn:hover {color: black;}";
    MAINpage += ".button5{background-color: #4CAF50;border: none;color: white;width: 200px;height: 70px;text-align: center;text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}";
    MAINpage += "</style>";
    MAINpage += "</head>";
    MAINpage += "<body style='background-color: #282c34'>";
    MAINpage += "<h1>BOT 2001</h1>";

    MAINpage += "<table>";
    MAINpage += "<tr><th>Luzes Autom&aacute;ticas</th><td>";
    if (autoLights) {
        MAINpage += "<p><a href='/luzOFF'><button class='button'>ON</button></a>";
        MAINpage += "</td></tr>";
        MAINpage += "<tr><td>Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;";        
        if (autoEstar) {
            MAINpage += "<a href='/estarOFF'><button class='button button3'>ON</button></a>";
        }
        else {
            MAINpage += "<a href='/estarON'><button class='button button4'>OFF</button></a>"; 
        }
        MAINpage += "</td></tr>";
        MAINpage += "<tr><td>Sala de jantar&nbsp;&nbsp;&nbsp;&nbsp;";
        if (autoJantar) {
            MAINpage += "<a href='/jantarOFF'><button class='button button3'>ON</button></a>";
        }
        else {
            MAINpage += "<a href='/jantarON'><button class='button button4'>OFF</button></a>";         
        }
        MAINpage += "</td></tr>";   
    }
    else {
        MAINpage += "<p><a href='/luzON'><button class='button button2'>OFF</button></a>";
        MAINpage += "</td></tr>";   
    }

    MAINpage += "<tr><th>Temperatura Exterior</th><td>";
    MAINpage += "Temperatura exterior: ";
    MAINpage += temp0;
    MAINpage += " &#8451;";
    MAINpage += "</td></tr>";
    MAINpage += "<tr><td><p></td></tr>";
    MAINpage += "<tr><th>Temperatura</th><td><input id='slider' type='range' min='20' max='30' value='";
    MAINpage += temp;
    MAINpage += "' step='1' class='slider' onchange='showValue(this.value); replace()'/><span id='range'> ";
    MAINpage += temp;
    MAINpage += "</span><script type='text/javascript'>function showValue(newValue){document.getElementById('range').innerHTML=newValue;}</script>&#8451;&nbsp;&nbsp;<a id='replace' href='/";
    MAINpage += temp;
    MAINpage += "'><button class='button' >Submit</button></a></td></tr>";
    MAINpage += "<th colspan='3'>Aquecimento</th>";

    MAINpage += "<tr><th>Aquecimento Autom&aacute;tico</th><td>";
    if (autoHeat) {
      MAINpage += "<p><a href='/aquecOFF'><button class='button'>ON</button></a>";
      MAINpage += "</td></tr>";
      MAINpage += "<tr><th>Sala</th><td>";
      if (livingRoom) {
        MAINpage += "<p><a href='/salaOFF'><button class='button' >ON</button></a>";
        MAINpage += "</td></tr>";
        MAINpage += "<tr><th>Cozinha</th><td>";       
        if (kitchen) {
          MAINpage += "<p><a href='/cozinhaOFF'><button class='button' >ON</button></a>";
        }
        else {
          MAINpage += "<p><a href='/cozinhaON'><button class='button button2'>OFF</button></a>";    
        }
        MAINpage += "</td></tr>";
      }
      else {
        MAINpage += "<p><a href='/salaON'><button class='button button2'>OFF</button></a>";
        MAINpage += "</td></tr>";
      }
      MAINpage += "<tr><th>Quarto</th><td>";
      if (bedroom) {
        MAINpage += "<p><a href='/quartoOFF'><button class='button' >ON</button></a>";
      }
      else {
        MAINpage += "<p><a href='/quartoON'><button class='button button2'>OFF</button></a>";
      }       
      MAINpage += "</td></tr>";
      MAINpage += "<tr><th>Casa de banho</th><td>";
      if (bathroom) {
        MAINpage += "<p><a href='/banhoOFF'><button class='button' >ON</button></a>";    
      }
      else {
        MAINpage += "<p><a href='/banhoON'><button class='button button2'>OFF</button></a>";
      }
      MAINpage += "</td></tr>";
    }
    else {
      MAINpage += "<p><a href='/aquecON'><button class='button button2'>OFF</button></a>";
      MAINpage += "</td></tr>";
    }

    MAINpage += "<th colspan='3'>Luzes</th>";
    MAINpage += "<tr><th>Hall de entrada</th><td>";
    if (on0) { 
        MAINpage += "<p><a href='/l0OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l0ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Sala de estar</th><td>";
    if (on1) { 
        MAINpage += "<p><a href='/l1OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l1ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Sala de jantar</th><td>";
    if (on2) { 
        MAINpage += "<p><a href='/l2OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l2ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Cozinha</th><td>";
    if (on3) { 
        MAINpage += "<p><a href='/l3OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l3ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Quarto</th><td>";
    if (on4) { 
        MAINpage += "<p><a href='/l4OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l4ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Casa de banho</th><td>";
    if (on5) { 
        MAINpage += "<p><a href='/l5OFF'><button class='button' >ON</button></a>";
    }
    else {
        MAINpage += "<p><a href='/l5ON'><button class='button button2'>OFF</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Arm&aacute;rio Hall</th><td><p><a href='/l6ON'><button class='button' onclick='alerta()' >Turn ON</button></a></td></tr>";
    MAINpage += "<tr><th colspan='3'><div class='alert' id='alert2' style='display:none;'><span class='closebtn' id='alert' style='display:none;' onclick='this.parentElement.style.display='none';'>&times;</span> <strong>Atenção! </strong>A luz irá desligar-se dentro de 1 minuto. </div></th></tr>";
    MAINpage += "<tr><th>Guarda-vestidos</th><td><p><a href='/l7ON'><button onclick='alerta2()' class='button' >Turn ON</button></a></td></tr>";
    MAINpage += "<tr><th colspan='3'><div class='alert' id='alert3' style='display:none;'><span class='closebtn' id='alert4' style='display:none;' onclick='this.parentElement.style.display='none';'>&times;</span> <strong>Atenção! </strong>A luz irá desligar-se dentro de 2 minutos. </div></tr>";
    
    MAINpage += "<tr><th colspan='3'>Cortina</th></tr>";
    MAINpage += "<tr><th colspan='3'>";
    if (open7) {
        MAINpage += "<p><a href='/cortinaOFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/cortinaON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</th></tr>";

    MAINpage += "<tr><th colspan='3'>Portas</th></tr>";
    MAINpage += "<tr><th>Entrada</th><td>";
    MAINpage += "";
    if (open0) {
        MAINpage += "<p><a href='/d0OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/d0ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Sala </th><td>";
    if (open1) {
        MAINpage += "<p><a href='/d1OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/d1ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Sala-cozinha</th><td>";
    if (open2) {
        MAINpage += "<p><a href='/d2OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/d2ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Cozinha</th><td>";
    if (open3) {
        MAINpage += "<p><a href='/d3OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/d3ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Quarto</th><td>";
    if (open4) {
        MAINpage += "<p><a href='/d4OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='/d4ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Quarto-casa de banho</th><td>";
    if (open5) {
        MAINpage += "<p><a href='/d5OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='d5ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";
    MAINpage += "<tr><th>Casa de banho</th><td>";
    if (open6) {
        MAINpage += "<p><a href='/d6OFF'><button class='button'>OPEN</button></a>";
    }
    else {
        MAINpage += "<p><a href='d6ON'><button class='button button2'>CLOSED</button></a>";
    }
    MAINpage += "</td></tr>";

    MAINpage += "</table>";
    MAINpage += "</body>";
    MAINpage += "</html>";

    server.send(200, "text/html", MAINpage);
}

void handleRoot() {
  updateHTML();
}

void notFound() {
  server.send(404, "text/plain", "oops");
}

void shutdown() {
  door(0, false);
  door(1, true);
  door(2, true);
  door(3, false);
  door(4, false);
  door(5, false);
  door(6, false);
  door(7, false);

  light(0, false);
  light(1, false);
  light(2, false);
  light(3, false);
  light(4, false);
  light(5, false);
  light(6, false);
  light(7, false);

  livingRoom = false;
  kitchen = false;
  bedroom = false;
  bathroom = false;

  if (autoLights) { timerLight.stop(); }
  b = 0;
  light0 = 0;
  light1 = 0;
  if (autoHeat) { timerRelay.stop(); }
  n = 0;
  temp1Sum = 0;
  temp2Sum = 0;
  temp3Sum = 0;

  server.send(200, "text/plain", "Goodbye");
}

void autoLightsON() {
    timerLight.start();
    autoLights = true;
    updateHTML();
}

void autoLightsOFF() {
    timerLight.stop();
    b = 0;
    light0 = 0;
    light1 = 0;
    autoLights = false;
    updateHTML();
}

void autoEstarON() {
    autoEstar = true;
    updateHTML();
}

void autoEstarOFF() {
    autoEstar = false;
    updateHTML();
}

void autoJantarON() {
    autoJantar = true;
    updateHTML();
}

void autoJantarOFF() {
    autoJantar = false;
    updateHTML();
}

void autoHeatON() {
    timerRelay.start();
    autoHeat = true;
    updateHTML();
}

void autoHeatOFF() {
    timerRelay.stop();
    n = 0;
    temp1Sum = 0;
    temp2Sum = 0;
    temp3Sum = 0;
    autoHeat = false;
    updateHTML();
}

void newTemp20() {
    temp = 20;
    updateHTML();
}
void newTemp21() {
    temp = 21;
    updateHTML();
}
void newTemp22() {
    temp = 22;
    updateHTML();
}
void newTemp23() {
    temp = 23;
    updateHTML();
}
void newTemp24() {
    temp = 24;
    updateHTML();
}
void newTemp25() {
    temp = 25;
    updateHTML();
}
void newTemp26() {
    temp = 26;
    updateHTML();
}
void newTemp27() {
    temp = 27;
    updateHTML();
}
void newTemp28() {
    temp = 28;
    updateHTML();
}
void newTemp29() {
    temp = 29;
    updateHTML();
}
void newTemp30() {
    temp = 30;
    updateHTML();
}

void salaON() {
    livingRoom = true;
    updateHTML();
}

void salaOFF() {
    livingRoom = false;
    updateHTML();
}

void cozinhaON() {
    kitchen = true;
    updateHTML();
}

void cozinhaOFF() {
    kitchen = false;
    updateHTML();
}

void quartoON() {
    bedroom = true;
    updateHTML();
}

void quartoOFF() {
    bedroom = false;
    updateHTML();
}

void banhoON() {
    bathroom = true;
    updateHTML();
}

void banhoOFF() {
    bathroom = false;
    updateHTML();
}

void l0ON() {
    light(0, true);
    updateHTML();
}

void l0OFF() {
    light(0, false);
    updateHTML();
}

void l1ON() {
    light(1, true);
    updateHTML();
}

void l1OFF() {
    light(1, false);
    updateHTML();
}

void l2ON() {
    light(2, true);
    updateHTML();
}

void l2OFF() {
    light(2, false);
    updateHTML();
}

void l3ON() {
    light(3, true);
    updateHTML();
}

void l3OFF() {
    light(3, false);
    updateHTML();
}

void l4ON() {
    light(4, true);
    updateHTML();
}

void l4OFF() {
    light(4, false);
    updateHTML();
}

void l5ON() {
    light(5, true);
    updateHTML();
}

void l5OFF() {
    light(5, false);
    updateHTML();
}

void l6ON() {
    light(6, true);
    updateHTML();
}

void l6OFF() {
    light(6, false);
    updateHTML();
}

void l7ON() {
    light(7, true);
    updateHTML();
}

void l7OFF() {
    light(7, false);
    updateHTML();
}

void cortinaON() {
    door(7, true);
    updateHTML();
}

void cortinaOFF() {
    door(7, false);
    updateHTML();
}

void d0ON() {
    door(0, true);
    updateHTML();
}

void d0OFF() {
    door(0, false);
    updateHTML();
}

void d1ON() {
    door(1, true);
    updateHTML();
}

void d1OFF() {
    door(1, false);
    updateHTML();
}

void d2ON() {
    door(2, true);
    updateHTML();
}

void d2OFF() {
    door(2, false);
    updateHTML();
}

void d3ON() {
    door(3, true);
    updateHTML();
}

void d3OFF() {
    door(3, false);
    updateHTML();
}

void d4ON() {
    door(4, true);
    updateHTML();
}

void d4OFF() {
    door(4, false);
    updateHTML();
}

void d5ON() {
    door(5, true);
    updateHTML();
}

void d5OFF() {
    door(5, false);
    updateHTML();
}

void d6ON() {
    door(6, true);
    updateHTML();
}

void d6OFF() {
    door(6, false);
    updateHTML();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hi");

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
  Serial.println("HTTP server running");
  toDo();

  server.on("/", handleRoot);
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
  server.on("/shutdown", shutdown);
}

void loop() {
  toRefresh();
  server.handleClient();
}