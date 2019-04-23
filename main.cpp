#include <Arduino.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <ShiftRegister74HC595.h>
#include <Ticker.h>
#include <WiFiClient.h>
#include <WiFi.h>
#include <WebServer.h>

#define ONE_WIRE_BUS 15

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Colocar as credenciais
char ssid[] = "Ssid";
char password[] = "SuperSecretPassword"; //ninguem sabe esta pass

WiFiServer server(80); ////esta shit nao funciona comigo 
//Ports GPIO
struct gpio{
  int port1, port2; //Pino a controlar (Caso pin simples, usar port1 só, caso motor, usar port1 e port2
  char* desc; //Descrição User Friendly 
  char* value; //Valor do Pino
};
//End GPIO Port

// Variable to store the HTTP request

char header[sizeof(long)];


void setup() {
  // Connect to Wi-Fi network with SSID and password
  Serial.begin(115200);                                         //este void tambem se chama setup foi literalmente copypaste do tutorial ele é necessario portanto chamalhe o que quiseres
  Serial.print("Connecting to ");
  Serial.println(ssid);
  server.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


double temp;  // temperatura ideal
double temp0; // baseline exterior
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

const int light0T = 600;
const int l0 = 36;
int light0;
const int light1T = 500;
const int l1 = 39;
int light1;
int b = 0;

ShiftRegister74HC595 shift(1, 26, 27, 25);

// são estas quatro bools que os botoes do aquecimento afetam
bool livingRoom = false;
bool kitchen = false;
bool bedroom = false;
bool bathroom = false;

// estas não mexes
bool livingRoomStatus = false;
bool kitchenStatus = false;
bool bedroomStatus = false;
bool bathroomStatus = false;

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

}

void checkLights() {
  b =+ 1;
  light0 =+ analogRead(l0);
  light1 =+ analogRead(l1);
  if (b == 1200) {  // de dez em dez minutos
    light0 = light0/b;
    light1 = light1/b;
    b = 0;
    if (light0 > light0T) {
      door(7, true);
      // desligar as luzes
    }
    if (light1 < light1T) {
      door(7, false);
      // ligar as luzes
    }
  }
}

Ticker timerRelay(checkRelay, 1000, 0, MILLIS);
Ticker timerLight(checkLights, 500, 0, MILLIS);

void light(int which, bool state) {
  if (state) {
    shift.set(which, HIGH);
  }
  else {
    shift.set(which, LOW);
  }
}

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

void loop() {
  // Código a chamar sempre que a página html dá refresh
  sensors.requestTemperatures();
  temp0 = sensors.getTempCByIndex(0); // esta temp0 é o valor da temperatura exterior
  checkInput(); // verifica se algum dos estados dos botões está diferente
  // iguala o temp ao valor do slider!
  // não te esqueças de atribuir um valor ao bool correspondente consoante o estado do botão
  if (timerRelay.state() == RUNNING) {
    timerRelay.update();
  }
  if (timerLight.state() == RUNNING) {
    timerLight.update();
  }

  // Código a chamar quando aquecimento automático está on
  timerRelay.start();

  // '' mas off
  timerRelay.stop();

  // Código a chamar quando luzes automáticas está on
  timerLight.start();

  // '' mas off
  timerLight.stop();

  // nos botões em que há override da luz ou portas, tens as funções door() e light()
  // true abrir false fechar
  // podes ver qual é qual no ficheiro excel

  // Código a chamar quando o client disconecta
  timerRelay.stop();
  timerLight.stop();
}

void printTemperatures() {  // apenas para teste
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

void loop2(){
  sensors.requestTemperatures();

  struct gpio gpio34{34,0,"Sensor de Temperatura", sensors.getTempCByIndex(1)};
  struct gpio gpio36{36,0,"Sensor de Luz #1", analogRead(36)};                            //Don't know se é preciso mas checka o tutorial e faz o que achares melhor
  struct gpio gpio39{39,0,"Sensor de Luz #2", analogRead(39)};
  struct gpio gpio32{32,33,"Motor 1", 0};
  struct gpio gpio14{14,12,"Motor 2", 0};
  struct gpio gpio15{15,2,"Motor 3", 0};
  struct gpio gpio4{4,0,"Servo 1", 0};
  struct gpio gpio16{6,0,"Servo 2", 0};
  struct gpio gpio17{17,0,"Servo 3", 0};
  struct gpio gpio5{5,0,"Servo 4", 0};
  struct gpio gpio18{18,0,"Servo 5", 0};
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            // turns the GPIOs on and off  //TO DO Escrever os indexes de mudança de cada um dos pinos, cant be arsed - trocar outputs por bools correspondentes
            if (header.indexOf("GET /32/on") >= 0) {
              Serial.println("GPIO 32 On");
              door(0,true);
            } else if (header.indexOf("GET /33/off") >= 0) {  // isto tava no tutorial da esp32 webserver da random nerd tutorials 
              Serial.println("GPIO 33 off");                  // nao sei se o que está ai ta certo
              door(0,false);                                  // porque eles mexem direto nos pinos e nao em funçoes       
            } else if (header.indexOf("GET /4/on") >= 0) {    // still a arte do index é necessaria para meter dentro dos botoes do html tens lá uns exemplos genericos parecidos iguas ...
              Serial.println("GPIO 4 on");                    //aos do tutorial para substituires com o que colocares
              door(0,true);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              door(0,false);
              else if (header.indexOf("GET /4/off") >= 0) {
            
            
            //Parte Engraçada
            // Display the HTML web page
            client.println("<!DOCTYPE html>");
            client.println("<html><head>");
            client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<title>BOT 2001 Control Page</title>");
            client.println("<link rel='icon' href='data:,'>");
            client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css'>");
            client.println("<script src='https://code.jquery.com/jquery-3.1.1.slim.min.js'></script>");
            client.println("<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js'></script>");
            client.println("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js'></script>");
            client.println("<script>function togglediv() {var div = document.getElementById('salas');div.style.display = div.style.display == 'none' ? 'block' : 'none';var div2 = 	document.getElementById('salas2');div2.style.display = div2.style.display == 'none' ? 'block' : 'none';var div3 = 	document.getElementById('salas3');div3.style.display = div3.style.display == 'block' ? 'none' : 'block';var div4 = 	document.getElementById('salas4');div4.style.display = div4.style.display == 'block' ? 'none' : 'block';var div5 = 	document.getElementById('salas5');div5.style.display = div5.style.display == 'block' ? 'none' : 'block';var div6 = 	document.getElementById('salas6');div6.style.display = div6.style.display == 'block' ? 'none' : 'block';var div7 = document.getElementById('cortinas');div7.style.display = div7.style.display == 'none' ? 'block' : 'none';var div8 = document.getElementById('cortinas2');div8.style.display = div8.style.display == 'none' ? 'block' : 'none';}</script>");
            client.println("<script>function togglediv2() {var div = document.getElementById('cozinha');div.style.display = div.style.display == 'block' ? 'none' : 'block';var div2 = 	document.getElementById('cozinha2');div2.style.display = div2.style.display == 'block' ? 'none' : 'block';var div3 = document.getElementById('sala1');div3.style.display = div3.style.display == 'none' ? 'block' : 'none';var div4 = document.getElementById('sala2');div4.style.display = div4.style.display == 'none' ? 'block' : 'none';var div5 = document.getElementById('sala3');div5.style.display = div5.style.display == 'none' ? 'block' : 'none';var div6 = document.getElementById('sala4');div6.style.display = div6.style.display == 'none' ? 'block' : 'none';var div7 = document.getElementById('cozinha3');div7.style.display = div7.style.display == 'block' ? 'none' : 'block';var div8 = 	document.getElementById('cozinha4');div8.style.display = div8.style.display == 'block' ? 'none' : 'block';}</script>");
            client.println("<script>function togglediv3() {var div = document.getElementById('cozinha3');div.style.display = div.style.display == 'block' ? 'none' : 'block';var div2 = 	document.getElementById('cozinha4');div2.style.display = div2.style.display == 'block' ? 'none' : 'block';}</script>");
            client.println("<script>function togglediv4() {var div = document.getElementById('quarto');div.style.display = div.style.display == 'none' ? 'block' : 'none';var div2 = 	document.getElementById('quarto2');div2.style.display = div2.style.display == 'none' ? 'block' : 'none';}</script>");
            client.println("<script>function togglediv5() {var div = document.getElementById('banho');div.style.display = div.style.display == 'none' ? 'block' : 'none';var div2 = 	document.getElementById('banho1');div2.style.display = div2.style.display == 'none' ? 'block' : 'none';}</script>");
            client.println("<script>function togglediv6() {var div = document.getElementById('sala5');div.style.display = div.style.display == 'block' ? 'none' : 'block';var div2 = 	document.getElementById('sala6');div2.style.display = div2.style.display == 'block' ? 'none' : 'block'; var div3 = document.getElementById('quarto3');div3.style.display = div3.style.display == 'block' ? 'none' : 'block';var div4 = document.getElementById('quarto4');div4.style.display = div4.style.display == 'block' ? 'none' : 'block';var div5 = document.getElementById('banho2');div5.style.display = div5.style.display == 'block' ? 'none' : 'block';var div6 = document.getElementById('banho3');div6.style.display = div6.style.display == 'block' ? 'none' : 'block';var div7 = document.getElementById('over');div7.style.display = div7.style.display == 'block' ? 'none' : 'block';}</script>");
            client.println("<style>");
            client.println("html{font-family: Helvetica;display: inline-block;margin: 0px auto;text-align: center;}");  
            client.println("body{margin:0;padding:0;color: #FFFFFF}");
            client.println(".button{background-color: #4CAF50;border: none;color: white;width: 160px;height: 70px;text-align: center;text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println( ".button2{background-color: #555555;}");
            client.println(".slider{-webkit-appearance: none;width: 80%;height: 15px;border-radius: 5px;   background: #d3d3d3;outline: none;opacity: 0.7;-webkit-transition: .2s;transition: opacity .2s;}");
            client.println(".slider::-webkit-slider-thumb {-webkit-appearance: none;appearance: none;width: 25px;height: 25px;border-radius: 50%; background: #4CAF50;cursor: pointer;}");
            client.println(".slider::-moz-range-thumb {width: 25px;height: 25px;border-radius: 50%;background: #4CAF50;cursor: pointer;}");
            client.println("th{font-size: 24px;font-weight: bold;text-align: center;}");
            client.println("td{text-align: center;font-size: 18px}");
            client.println("table{float:center;width:100%;}");
            client.println("</style></head>");
            client.println("<body style='background-color: #282c34'>");
            client.println("<h1>BOT 2001</h1>");
            client.println("<table>");
            client.println("<tr><th>Luzes Automáticas</th><td>");
            if{
              client.println("<p><a \"/33/on\"><button class=\"button\"  onclick='togglediv()' >ON</button></a></p>"); //botao para as luzes automaticas ligadas
            } else{
              client.println("<p><a \"/33/on\"><button class=\"button button2\"  onclick='togglediv()' >OFF</button></a></p>"); //botao para as luzes automaticas ligadas
            }
            client.println("</td></tr>");
            client.println("<tr><td><div id='salas'>Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;<input style='height: 26px; width:26px; margin-left:0' value='' checked='' type='checkbox'></div></td></tr>");
            client.println("<tr><td><div id='salas2'> Sala de jantar&nbsp;&nbsp;&nbsp;&nbsp;<input style='height: 26px; width:26px; margin-left:0' value='' checked='' type='checkbox'></div></td></tr>");
            client.println("<tr><th>Aquecimento Automático</th><td>");
            if{
              client.println("<p><a \"/33/on\"><button onclick='togglediv6()' class=\"button\">ON</button></a></p>"); //botao para o aquecimento automatico ligado
            } else{
              client.println("<p><a \"/33/on\"><button onclick='togglediv6()' class=\"button button2\">OFF</button></a></p>"); //botao para o aquecimento automatico ligado
            } 
            client.println("</td></tr>");           
            client.println("<tr><th>Temperatura Exterior</th><td>'Colocar Valor do Sensor'</td></tr>");
            client.println("<tr><td><p></td></tr>");
            client.println("<tr><th>Temperatura</th><td><input type='range' min='0' max='30' value='20' step='0.5' class='slider' onchange='showValue(this.value)' /><span id='range'>20</span><script type='text/javascript'>function showValue(newValue){document.getElementById('range').innerHTML=newValue;}</script> ºC</td></tr>");
            client.println("<th colspan='3'>Aquecimento</th>");
            client.println("<tr><th>Sala</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button onclick='togglediv2()' class=\"button\">ON</button></a></p>"); //botao para o aquecimento da sala ligado
            }  else {
              client.println("<p><a \"/33/on\"><button onclick='togglediv2()' class=\"button button2\">OFF</button></a></p>"); //botao para o aquecimento da sala desligado
            }
            client.println("</td></tr>");
            client.println("<tr><th><div style='display:none' id='cozinha'>Cozinha</div></th><td>");
            if{
              client.println("<div style='display:none' id='cozinha2'><p><a \"/33/on\"><button onclick='togglediv3()' class=\"button\">ON</button></a></p></div>"); //botao para o aquecimento da cozinha ligado
            }  else{
              client.println("<div style='display:none' id='cozinha2'><p><a \"/33/on\"><button onclick='togglediv3()' class=\"button button2\">OFF</button></a></p></div>"); //botao para o aquecimento da cozinha desligado
            }
            client.println("</td></tr>");
            client.println("<tr><th>Quarto</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button onclick='togglediv4()' class=\"button\">ON</button></a></p>");  //botao para o aquecimento do quarto ligado
            }  else
              client.println("<p><a \"/33/on\"><button onclick='togglediv4()' class=\"button button2\">OFF</button></a></p>"); //botao para o aquecimento do quarto desligado
            }
            client.println("</td></tr>");
            client.println("<tr><th>Casa de banho</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button onclick='togglediv5()' class=\"button\">ON</button></a></p>"); //botao para o aquecimento da casa de banho ligado
            }  else
              client.println("<p><a \"/33/on\"><button onclick='togglediv5()' class=\"button button2\">OFF</button></a></p>"); //botao para o aquecimento da casa de banho deligado
            }
            client.println("</td></tr>");
            client.println("<th colspan='3'>Luzes</th>");
            client.println("tr><th>Hall de entrada</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz do hall de entrada ligada
            }  else{
              client.println("<p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz do hall de entrada desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div style='display:none' id='salas5'>Sala de estar</div></th><td>");
            if {
              client.println("<div style='display:none' id='salas3'><p><a \"/33/on\"><button class=\"button\">ON</button></a></p></div>"); // botao para a luz da sala de estar ligada
            } else{
              client.println("<div style='display:none' id='salas3'><p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p></div>");  // botao para a luz da sala de estar desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div style='display:none' id='salas6'>Sala de jantar</div></th><td>");
            if {
              client.println("<div style='display:none' id='salas4'><p><a \"/33/on\"><button class=\"button\">ON</button></a></p></div>"); // botao para a luz da sala de jantar ligada
            } else{
              client.println("<div style='display:none' id='salas4'><p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p></div>");  // botao para a luz da sala de jantar desligada  
            }
            client.println("</td></tr>");
            client.println("<tr><th>Cozinha</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz do quarto ligada
            } else
              client.println("<p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz do quarto desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th>Quarto</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz do quarto ligada
            } else
              client.println("<p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz do quarto desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th>Casa de banho</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz da casa de banho ligada
            } else
              client.println("<p><a \"/33/on\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz da casa de banho desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th>Armário Hall</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz do armario hall ligada
            } else
              client.println("<p><a \"/33/off\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz do armario hall desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th>Guarda-vestidos</th><td>");
            if {
              client.println("<p><a \"/33/on\"><button class=\"button\">ON</button></a></p>"); // botao para a luz do guarda vestidos ligada
            } else
              client.println("<p><a \"/33/off\"><button class=\"button button2\">OFF</button></a></p>"); // botao para a luz do guarda vestidos desligada
            }
            client.println("</td></tr>");
            client.println("<tr><th colspan='3'><div id='cortinas'>Cortina</div></th></tr>");
            client.println("<tr>");
            if {
              client.println("<th colspan='3'><div id='cortinas2'><p><a \"/33/on\"><button class=\"button\">OPEN</button></a></p></div></th>"); // botao para a cortina aberta
              else{
              client.println("<th colspan='3'><div id='cortinas2'><p><a \"/33/off\"><button class=\"button button2\">CLOSED</button></a></p></div></th>"); // botao para a cortina fechada
            }
            client.println("</tr>");   
            client.println("<tr><th colspan='3'>Portas</th></tr>");
            client.println("<tr><th>Entrada</th><td>");
            if {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>"); //botao para a porta da entrada aberta
            } else{
                client.println("<p><a href=\"/4/off\"><button class=\"button button2\">CLOSED</button></a></p>"); //botao para a porta da entrada fechada
            }
            client.println("</td></tr>");
            client.println("<th><div id='sala1'>Sala</div> </th><td>");
            if {
              client.println("<div id='sala2'><p><a href=\"/32/on\"><button class=\"button\">OPEN</button></a></p></div>"); //botao para a porta da sala aberta
            } else{
                client.println("<div id='sala2'><p><a href=\"/33/off\"><button class=\"button button2\">CLOSED</button></a></p></div>"); //botao  para a porta da sala fechada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div id='sala3'>Sala-cozinha</div></th><td>");
            if {
              client.println("<div id='sala4'><p><a href=\"/14/on\"><button class=\"button\">OPEN</button></a></p></div>"); //botao para a porta da sala-cozinha aberta
            } else {
                client.println("<div id='sala4'><p><a href=\"/12/off\"><button class=\"button button2\">CLOSED</button></a></p></div>"); //botao  para a porta da sala-cozinha fechada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div style='display:none' id='cozinha3'>Cozinha</div></th><td>");
            if {
              client.println("<div style='display:none' id='cozinha4'><p><a \"/16/on\"><button class=\"button\">OPEN</button></a></p></div>"); //botao para a porta da cozinha aberta
              else{
                client.println("<div style='display:none' id='cozinha4'><p><a \"/16/off\"><button class=\"button button2\">CLOSED</button></a></p></div>"); //botao  para a porta da cozinha fechada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div id='quarto'>Quarto</div></th><td>");
            if 
              client.println("<div id='quarto2'><p><a \"/17/on\"><button class=\"button\">OPEN</button></a></p></div>"); //botao para a porta do quarto aberta
              else{
                client.println("<div id='quarto2'><p><a \"/17/off\"><button class=\"button button2\">CLOSED</button></a></p></div>"); //botao para a porta do quarto fechada
            }
            client.println("</td></tr>");
            
            client.println("<tr><th>Quarto-casa de banho</th><td>");
            if {
              client.println("<p><a \"/17/on\"><button class=\"button\">OPEN</button></a></p>"); //botao para a porta do quarto-casa de banho aberta
              else{
              client.println("<p><a \"/17/off\"><button class=\"button button2\">CLOSED</button></a></p>"); //botao para a porta do quarto-casa de banho fechada
            }
            client.println("</td></tr>");
            client.println("<tr><th><div id='banho'>Casa de banho</div></th><td>");
            if {
              client.println("<div id='banho1'><p><a \"/17/on\"><button class=\"button\">OPEN</button></a></p></div>"); //botao para a porta da casa de banho aberta
              else {
              client.println("<div id='banho1'><p><a \"/17/off\"><button class=\"button button2\">CLOSED</button></a></p></div>"); //botao para a porta da casa de banho fechada
            }
            client.println("</td></tr>");
            client.println("<th colspan='3'> <div style='display:none' id='over'>Override de aquecimento</div></th>");
            client.println("<tr><th><div style='display:none' id='sala5'>Sala</div></th><td>");
            if {
              client.println("<div style='display:none' id='sala6'><p><a \"/17/on\"><button class=\"button\">ON</button></a></p></div>"); //botao para a override de aquecimento da sala on
            } else{
              client.println("<div style='display:none' id='sala6'><p><a \"/17/off\"><button class=\"button button2\">OFF</button></a></p></div>"); //botao para a override de aquecimento da sala off
            }
            client.println("</td></tr>");
            client.println("<tr><th><div style='display:none' id='quarto3'>Quarto</div></th><td>");
            if {
              client.println("<div style='display:none' id='quarto4'><p><a \"/17/on\"><button class=\"button\">ON</button></a></p></div>");  //botao para a override de aquecimento do quarto on
            }  else{
              client.println("<div style='display:none' id='quarto4'><p><a \"/17/on\"><button class=\"button button2\">OFF</button></a></p></div>");  //botao para a override de aquecimento do quarto off
            }
            client.println("</td></tr>");
           
            client.println("<tr><th><div style='display:none' id='banho2'>Casa de banho</div></th><td>");
            if {
              client.println("<div style='display:none' id='banho3'><p><a \"/17/on\"><button class=\"button\">ON</button></a></p></div>");  //botao para a override de aquecimento da casa de banho on
            } else{
              client.println("<div style='display:none' id='banho3'><p><a \"/17/on\"><button class=\"button button2\">OFF</button></a></p></div>"); //botao para a override de aquecimento da casa de banho off
            }  
            client.println("</td></tr>");
            client.println("</table>");
            client.println("</body></html>");


            // The HTTP response ends with another blank line
            client.println();

            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
