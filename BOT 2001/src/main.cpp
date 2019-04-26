#include <Arduino.h>
#include <kittycat.h>

#include <WebServer.h>
#include <WiFiAP.h>

#include <string>
#include <cstring>
#include <sstream>
#include <iostream>

const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
<title>BOT 2001 Control Page</title>
<link rel=\"icon\" href=\"data:,\">
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css'>
<script src='https://code.jquery.com/jquery-3.1.1.slim.min.js'></script>
<script src='https://cdnjs.cloudflare.com/ajax/libs/tether/1.4.0/js/tether.min.js'></script>
<script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/js/bootstrap.min.js'></script>
<script>
function alerta(){
document.getElementById('alert').style.display='block'
document.getElementById('alert2').style.display='block'}
</script>
<script>
function alerta2(){
document.getElementById('alert3').style.display='block'
document.getElementById('alert4').style.display='block'}
</script>
<script  type="text/javascript">
function replace() {
    var aEl = document.getElementById('replace');
    if (document.getElementById("range").textContent == "20"){
    aEl.href = "/20";}
	else if(document.getElementById("range").textContent == "21"){
    aEl.href = "/21";}
    else if(document.getElementById("range").textContent == "22"){
    aEl.href = "/22";}
    else if(document.getElementById("range").textContent == "23"){
    aEl.href = "/23";}
    else if(document.getElementById("range").textContent == "24"){
    aEl.href = "/24";}
    else if(document.getElementById("range").textContent == "25"){
    aEl.href = "/25";}
    else if(document.getElementById("range").textContent == "26"){
    aEl.href = "/26";}
    else if(document.getElementById("range").textContent == "27"){
    aEl.href = "/27";}
    else if(document.getElementById("range").textContent == "28"){
    aEl.href = "/28";}
    else if(document.getElementById("range").textContent == "29"){
    aEl.href = "/29";}
    else if(document.getElementById("range").textContent == "30"){
    aEl.href = "/30";}
}
replace();
</script>
<script>
function togglediv() {
    var div = document.getElementById('autolight');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('autolight2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv2() {
    var div = document.getElementById('autoheating');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('autoheating2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglesala() {
    var div = document.getElementById('sala');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('sala2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglecozinha() {
    var div = document.getElementById('cozinha');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('cozinha2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglequarto() {
    var div = document.getElementById('quarto');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('quarto2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglebanho() {
    var div = document.getElementById('banho');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('banho2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function receberluzes() {
  localStorage.setItem("estadoluzon", document.getElementById('autolight').style.display);
  localStorage.setItem("estadoluzoff", document.getElementById('autolight2').style.display);
  }
</script>
<script>
function receberaquec() {
  localStorage.setItem("estadoaquecon", document.getElementById('autoheating').style.display);
  localStorage.setItem("estadoaquecoff", document.getElementById('autoheating2').style.display);
  }
</script>
<script>
function receberluzes() {
  localStorage.setItem("estadosalaon", document.getElementById('sala').style.display);
  localStorage.setItem("estadosalaoff", document.getElementById('sala2').style.display);
  }
</script>
<script>
function receberluzes() {
  localStorage.setItem("estadocozinhaon", document.getElementById('cozinha').style.display);
  localStorage.setItem("estadocozinhaoff", document.getElementById('cozinha2').style.display);
  }
</script>
<script>
function receberluzes() {
  localStorage.setItem("estadoquartoon", document.getElementById('quarto').style.display);
  localStorage.setItem("estadoquartooff", document.getElementById('quarto2').style.display);
  }
</script>
<script>
function receberluzes() {
  localStorage.setItem("estadobanhoon", document.getElementById('banho').style.display);
  localStorage.setItem("estadobanhooff", document.getElementById('banho2').style.display);
  }
</script>
<script>
function enviarestados()
document.getElementById('autolight').style.display=localStorage.getItem("estadoluzon");
document.getElementById('autolight2').style.display=localStorage.getItem("estadoluzoff");
document.getElementById('autoheating').style.display=localStorage.getItem("estadoaquecon");
document.getElementById('autoheating2').style.display=localStorage.getItem("estadoaquecon");
document.getElementById('sala').style.display=localStorage.getItem("estadosalaon");
document.getElementById('sala2').style.display=localStorage.getItem("estadosalaoff");
document.getElementById('cozinha').style.display=localStorage.getItem("estadocozinhaon");
document.getElementById('cozinha2').style.display=localStorage.getItem("estadocozinhaoff");
document.getElementById('quarto').style.display=localStorage.getItem("estadoquartoon");
document.getElementById('quarto2').style.display=localStorage.getItem("estadoquartoon");
document.getElementById('banho').style.display=localStorage.getItem("estadobanhoon");
document.getElementById('banho2').style.display=localStorage.getItem("estadobanhooff");
}
</script>
<style>
html{font-family: Helvetica;
	display: inline-block;
	margin: 0px auto;
	text-align: center;}
body{margin:0;
	padding:0;
    color: #FFFFFF}
.button{background-color: #4CAF50;
	border: none;
	color: white;
	width: 120px;
    height: 70px;
    text-align: center;
	text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}
.button2{background-color: #555555;}
.slider{
  -webkit-appearance: none;
  width: 50%;
  height: 15px;
  border-radius: 5px;   
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;}
.slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 25px;
  height: 25px;
  border-radius: 50%; 
  background: #4CAF50;
  cursor: pointer;}  
.slider::-moz-range-thumb {
  width: 25px;
  height: 25px;
  border-radius: 50%;
  background: #4CAF50;
  cursor: pointer;}
th{font-size: 24px;
  font-weight: bold;
  text-align: center;}
td{text-align: center;
  font-size: 18px}
table{
  float:center;
  width:100%;}
.button3{background:#4caf50;
	width: 50px;
    height: 40px;
	border-radius: 5px;
	color:#ffffff;
	display:inline-block;
	font:normal bold 24px/1 "Calibri", sans-serif;
	text-align:center;}
.button4{background:#555555;
	width: 50px;
    height: 40px;
	border-radius: 5px;
	color:#ffffff;
	display:inline-block;
	font:normal bold 24px/1 "Calibri", sans-serif;
	text-align:center;}
 .alert {
  padding: 20px;
  background-color: #f44336;
  color: white;}
  .closebtn {
  margin-left: 15px;
  color: white;
  font-weight: bold;
  float: right;
  font-size: 22px;
  line-height: 20px;
  cursor: pointer;
  transition: 0.3s;}
  .closebtn:hover {
  color: black;}
.button5{background-color: #4CAF50;
	border: none;
	color: white;
	width: 200px;
    height: 70px;
    text-align: center;
	text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}
</style>
</head>
<body style="background-color: #282c34">
<h1>BOT 2001</h1>
<table>
<tr>
	<th>
		Auto-Luzes
	</th>
	<td>
		<div id="autolight"><p><a href="/luzON"><button class="button" onclick="togglediv();receberluzes()">ON</button></a></div>
    	<div id="autolight2" style="display:none"><p><a href="/luzOFF"><button class="button button2" onclick="togglediv()">OFF</button></a></div>
        
	</td>
</tr>
<tr>
	<td>
         Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;<a href="/estarON"><button class="button button3">ON</button></a><a href="/estarOFF"><button class="button button4">OFF</button></a>
    </td>
</tr>
<tr>
	<td>
    	Sala de jantar&nbsp;&nbsp;&nbsp;&nbsp;<a href="/jantarON"><button class="button button3">ON</button></a><a href="/jantarOFF"><button class="button button4">OFF</button></a>
    </td>
 </tr>
 <tr>
	<th>
		Auto-Aquecimento
	</th>
	<td>
		<div id="autoheating"><p><a href="/aquecON"><button class="button" onclick="togglediv2();receberaquec()">ON</button></a></div>
    	<div id="autoheating2" style="display:none"><p><a href="/aquecOFF"><button class="button button2" onclick="togglediv2()">OFF</button></a></div>
        
	</td>
</tr>
<tr>
	<th>
		Temperatura Exterior
    </th>
    <td>
    	<p><a href="/temp"><button class="button button5">Get Temperature</button></a></p>
    </td>
</tr>
<tr>
	<td>
		<p>
	</td>
</tr>
<tr>
	<th>
		Temperatura
	</th>
	<td>
		<input id="slider" type="range" min="20" max="30" value="25" step="1" class="slider" onchange="showValue(this.value); replace()" />
			<span id="range">25</span>
				<script type="text/javascript">
					function showValue(newValue)
					{
					document.getElementById("range").innerHTML=newValue;
					}
				</script>
                ºC&nbsp;&nbsp;<a id="replace" href="/25"><button class="button" >Submit</button></a>
	</td>
</tr>
<th colspan="3">Aquecimento</th>
<tr>
	<th>
    	Sala
    </th>
	<td>
		<div id="sala" style="display:none"><p><a href="/salaON"><button class="button" onclick="togglesala()">ON</button></a></div>
    	<div id="sala2"><p><a href="/salaOFF"><button class="button button2" onclick="togglesala()">OFF</button></a></div>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
	</th>
    <td>
		<div id="cozinha" style="display:none"><p><a href="/cozinhaON"><button class="button" onclick="togglecozinha()">ON</button></a></div>
    	<div id="cozinha2"><p><a href="/cozinhaOFF"><button class="button button2" onclick="togglecozinha()">OFF</button></a></div>
	</td>
</tr>
<tr>
	<th>
    	Quarto
	</th>
	<td>
		<div id="quarto" style="display:none"><p><a href="/quartoON"><button class="button" onclick="togglequarto()">ON</button></a></div>
    	<div id="quarto2"><p><a href="/quartoOFF"><button class="button button2" onclick="togglequarto()">OFF</button></a></div>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
	</th>
	<td>
		<div id="banho" style="display:none"><p><a href="/banhoON"><button class="button" onclick="togglebanho()">ON</button></a></div>
    	<div id="banho2"><p><a href="/banhoOFF"><button class="button button2" onclick="togglebanho()">OFF</button></a></div>
	</td>
</tr>
<th colspan="3">Luzes</th>
<tr>
	<th>
    	Hall de entrada
    </th>
	<td>
		<p><a href="/l0ON"><button class="button" >ON</button></a>
    	<a href="/l0OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	<div  id="salas5">Sala de estar</div>
    </th>
	<td>
		<p><a href="/l1ON"><button class="button" >ON</button></a>
    	<a href="/l1OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Sala de jantar
    </th>
	<td>
		<p><a href="/l2ON"><button class="button" >ON</button></a>
    	<a href="/l2OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
    </th>
	<td>
		<p><a href="/l3ON"><button class="button" >ON</button></a>
    	<a href="/l3OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Quarto
    </th>
	<td>
		<p><a href="/l4ON"><button class="button" >ON</button></a>
    	<a href="/l4OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
    </th>
	<td>
		<p><a href="/l5ON"><button class="button" >ON</button></a>
    	<a href="/l5OFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Armário Hall
    </th>
	<td>
		<p><a href="/l6ON"><button class="button" onclick="alerta()" >ON</button></a>
	</td>
 <tr>   
 <th colspan="3">
 	<div class="alert" id="alert2" style="display:none;">
  <span class="closebtn" id="alert" style="display:none;" onclick="this.parentElement.style.display='none';">&times;</span> 
  <strong>Atenção! </strong>A luz irá desligar-se dentro de 1 minuto. 
</div>
</th>
</tr>
</div>
</tr>
<tr>
	<th>
    	Guarda-vestidos
    </th>
	<td>
		<p><a href="/l7ON"><button onclick="alerta2()" class="button" >ON</button></a>
	</td>
</tr>
<tr>
<th colspan="3">
 	<div class="alert" id="alert3" style="display:none;">
  <span class="closebtn" id="alert4" style="display:none;" onclick="this.parentElement.style.display='none';">&times;</span> 
  <strong>Atenção! </strong>A luz irá desligar-se dentro de 2 minutos. 
</div>
</tr>
<tr>
	<th colspan="3"><div id="cortinas">Cortina</div></th>
</tr>
<tr>
	<th colspan="3">
		<p><a href="/cortinaON"><button class="button">OPEN</button></a>
    <a href="/cortinaOFF"><button class="button button2">CLOSE</button></a></p>
    </th>
</tr>
<tr>
	<th colspan="3">Portas</th>
</tr>
<tr>
	<th>
    	Entrada
    </th>
    <td>
		<p><a href="/d0ON"><button class="button">OPEN</button></a>
    <a href="/d0OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Sala 
    </th>
	<td>
		<p><a href="/d1ON"><button class="button">OPEN</button></a>
    <a href="/d1OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Sala-cozinha
    </th>
	<td>
		<p><a href="/d2ON"><button class="button">OPEN</button></a>
    <a href="/d2OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Cozinha
    </th>
	<td>
		<p><a href="/d3ON"><button class="button">OPEN</button></a>
    <a href="/d3OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Quarto
    </th>
	<td>
		<p><a href="/d4ON"><button class="button">OPEN</button></a>
    <a href="/d4OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Quarto-casa de banho
    </th>
	<td>
		<p><a href="/d5ON"><button class="button">OPEN</button></a>
    <a href="d5OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr><tr>
	<th>
    	Casa de banho
    </th>
	<td>
		<p><a href="/d6ON"><button class="button">OPEN</button></a>
    <a href="d6OFF"><button class="button button2">CLOSE</button></a></p>
	</td>
</tr>
</table>
</body>
</html>

)=====";

WebServer server(80);

char* ssid = "bot2001";
char* password = "2001bot2001";

void handleRoot() {
  server.send(200, "text/html", MAIN_page);
}

void notFound() {
  server.send(404, "text/plain", "oops");
}

void handleTemp() {
  server.send(200, "text/plain", "Temperatura");
  delay(5000);
  server.send(200, "text/html", MAIN_page);
}

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
  Serial.println("HTTP server ok");
  toDo();

  server.on("/", handleRoot);
  server.on("/temp", handleTemp);
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
}

void loop() {
  toRefresh();
  server.handleClient();
}