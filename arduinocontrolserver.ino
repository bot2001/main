// Load Wi-Fi library
#include <WiFi.h>

void cl(char* htmlcode){
    client.println("%s", htmlcode);
  }
// Replace with your network credentials
const char* ssid     = "";
const char* password = "";

//Ports GPIO
struct gpio{
  int port1, port2; //Pino a controlar (Caso pin simples, usar port1 só, caso motor, usar port1 e port2
  char* desc; //Descrição User Friendly 
  char* value; //Valor do Pino
}
//End GPIO Ports

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void setup() {
  // Connect to Wi-Fi network with SSID and password
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT); //TO DO Escrever PinModes para cada pino 
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW); //TO DO Escrever DigitalWrite para cada pino (0 / LOW)
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
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

void loop(){
  sensors.requestTemperatures();

  struct gpio gpio34{34,,"Sensor de Temperatura", sensors.getTempCByIndex(1)};
  struct gpio gpio36{36,,"Sensor de Luz #1", analogRead(36)};
  struct gpio gpio39{39,,"Sensor de Luz #2", analogRead(39)};
  struct gpio gpio32{32,33,"Motor 1", 0};
  struct gpio gpio14{14,12,"Motor 2", 0};
  struct gpio gpio15{15,2,"Motor 3", 0};
  struct gpio gpio4{4,,"Servo 1", 0};
  struct gpio gpio16{6,,"Servo 2", 0};
  struct gpio gpio17{17,,"Servo 3", 0};
  struct gpio gpio5{5,,"Servo 4", 0};
  struct gpio gpio18{18,,"Servo 5", 0};
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
            // turns the GPIOs on and off  //TO DO Escrever os indexes de mudança de cada um dos pinos, cant be arsed
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output27, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output27, LOW);
            }
            //Parte Engraçada
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta http-equiv='refresh' content='5'/><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            cl("<title>BOT 2001 Control Page</title>");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            cl("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css'>");
            cl("<script src='https://code.jquery.com/jquery-3.1.1.slim.min.js'></script>");
            cl("<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js'></script>");
            cl("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js'></script>");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            cl("<style>body{margin:0; padding:0;}</style>");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body style'background-color: #282c34'><h1>BOT 2001</h1>");
            cl("<table width:'100%'>");
            cl("<tr>");
            cl("<td>");
            cl("Temperatura");
            cl("</td>");
            cl("<td>");
            cl("<input type='range' min="15" max="35" value="25" class="slider" id="tempRange">");
            cl("</td>");
            cl("</tr>");
              cl("<tr>");
                cl("<th>");
                  cl("Informação dos Sensores");
                cl("</th>");
                cl("<th>");
                  cl("Controlo de Atuadores");
                cl("</th>");
              cl("</tr>");
              cl("<tr>");
                cl("<td>");
                cl("<td>GPIO 34 - %s: %s",gpio34.desc, gpio34.value);
                cl("</td>");
                cl("<td>GPIO 32 - %s: %s",gpio32.desc, gpio32.value);
                cl("</td>");
                cl("<td>");
                if (gpio32.value==0) {
                  client.println("<p><a href=\"/32/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/32/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                if(gpio32.value!=0){ //Se o 32 estiver ativo, mostra o 14 (e o 36?)
                  cl("<tr>");
                  cl("<td>");
                  cl("<td>GPIO 36 - %s: %s",gpio36.desc, gpio36.value);
                  cl("</td>");
                  cl("<td>GPIO 14 - %s: %s",gpio14.desc, gpio14.value);
                  cl("</td>");
                  cl("<td>");
                  if (gpio14.value==0) {
                    client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
                  } else {
                    client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
                  } 
                  cl("</td>");
                  cl("</tr>");
                }
                cl("<tr>");
                 cl("<td>");
                cl("<td>GPIO 39 - %s: %s",gpio39.desc, gpio39.value);
                cl("</td>");
                cl("<td>GPIO 15 - %s: %s",gpio34.desc, gpio34.value);
                cl("</td>");
                cl("<td>");
                if (gpio15.value==0) {
                  client.println("<p><a href=\"/15/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/15/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                cl("<tr>");
                cl("<td>GPIO 4 - %s: %s",gpio4.desc, gpio4.value);
                cl("</td>");
                cl("<td>");
                if (gpio4.value==0) {
                  client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                cl("<tr>");
                cl("<td>GPIO 16 - %s: %s",gpio16.desc, gpio16.value);
                cl("</td>");
                cl("<td>");
                if (gpio34.value==0) {
                  client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                cl("<tr>");
                cl("<td>GPIO 17 - %s: %s",gpio17.desc, gpio17.value);
                cl("</td>");
                cl("<td>");
                if (gpio34.value==0) {
                  client.println("<p><a href=\"/17/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/17/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                cl("<tr>");
                cl("<td>GPIO 5 - %s: %s",gpio5.desc, gpio5.value);
                cl("</td>");
                cl("<td>");
                if (gpio34.value==0) {
                  client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/18/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
                cl("<tr>");
                cl("<td>GPIO 18 - %s: %s",gpio18.desc, gpio18.value);
                cl("</td>");
                cl("<td>");
                if (gpio34.value==0) {
                  client.println("<p><a href=\"/18/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/18/off\"><button class=\"button button2\">OFF</button></a></p>");
                } 
                cl("</td>");
                cl("</tr>");
            cl("</table>");
            // Display current state, and ON/OFF buttons for GPIO 26  
            // If the output26State is off, it displays the ON button       
               
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
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
