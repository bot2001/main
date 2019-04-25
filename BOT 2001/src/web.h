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
var x = document.getElementById('autolight').style.display
var y = document.getElementById('autolight2').style.display
function receberluzes() {
  localStorage.setItem("estadoluzon", x);
  localStorage.setItem("estadoluzoff", y);
  }
</script>
<script>
var x = document.getElementById('autoheating').style.display
var y = document.getElementById('autoheating2').style.display
function receberaquec() {
  localStorage.setItem("estadoaquecon", x);
  localStorage.setItem("estadoaquecoff", y);
  }
</script>
<script>
function enviarestados()
document.getElementById('autolight').style.display=localStorage.getItem("estadoluzon");
document.getElementById('autolight2').style.display=localStorage.getItem("estadoluzoff");
document.getElementById('autoheating').style.display=localStorage.getItem("estadoaquecon");
document.getElementById('autoheating2').style.display=localStorage.getItem("estadoaquecon");
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
		Luzes Automáticas
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
		Aquecimento Automático
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
    	<p><a href="/temp"><button class="button button5" onclick="notifier()" >Get Temperature</button></a>
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
		<p><a href="/salaON"><button class="button" >ON</button></a>
    	<a href="/salaOFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
	</th>
    <td>
		<p><a href="/cozinhaON"><button class="button" >ON</button></a>
    	<a href="/cozinhaOFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Quarto
	</th>
	<td>
		<p><a href="/quartoON"><button class="button" >ON</button></a>
    	<a href="/quartoOFF"><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
	</th>
	<td>
		<p><a href="/banhoON"><button class="button" >ON</button></a>
    	<a href="/banhoOFF"><button class="button button2">OFF</button></a></p>
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
  <strong>Atenção!</strong>A luz irá desligar-se dentro de 30 segundos. 
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
  <strong>Atenção!</strong>A luz irá desligar-se dentro de 30 segundos. 
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
		<p><a href="/d2ON""><button class="button">OPEN</button></a>
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
