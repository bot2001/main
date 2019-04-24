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
function togglediv() {
    var div = document.getElementById("autolights");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("autolights2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv1() {
    var div = document.getElementById("autoheating");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("autoheating2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv2() {
    var div = document.getElementById("sala");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("sala2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv3() {
    var div = document.getElementById("cozinha");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("cozinha2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv4() {
    var div = document.getElementById("quarto");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("quarto2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv5() {
    var div = document.getElementById("banho");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("banho2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv6() {
    var div = document.getElementById("hall");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("hall2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv7() {
    var div = document.getElementById("estar");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("estar2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv8() {
    var div = document.getElementById("jantar");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("jantar2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv9() {
    var div = document.getElementById("cozinha3");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("cozinha4");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv10() {
    var div = document.getElementById("quarto3");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("quarto4");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv11() {
    var div = document.getElementById("banho3");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("banho4");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv12() {
    var div = document.getElementById("armario");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("armario2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv13() {
    var div = document.getElementById("guardavestidos");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("guardavestidos2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv14() {
    var div = document.getElementById("cortina");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("cortina2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv15() {
    var div = document.getElementById("entrada");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("entrada2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv16() {
    var div = document.getElementById("sala3");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("sala4");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv17() {
    var div = document.getElementById("salacozinha");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("salacozinha2");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv18() {
    var div = document.getElementById("cozinha5");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("cozinha6");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv19() {
    var div = document.getElementById("quarto5");
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById("quarto6");
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv20() {
    var div = document.getElementById('quartobanho');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('quartobanho2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv21() {
    var div = document.getElementById('banho5');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('banho6');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv22() {
    var div = document.getElementById('saladejantar');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('saladejantar2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv23() {
    var div = document.getElementById('saladeestar');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('saladeestar2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
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
	width: 160px;
    height: 70px;
    text-align: center;
	text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}
.button2{background-color: #555555;}
.slider{
  -webkit-appearance: none;
  width: 80%;
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
		<div id="autolights"><p><a href="/luzON"><button onclick="togglediv()" class="button">ON</button></a></p></div>
    	<div id="autolights2" style="display:none"><p><a href="/luzOFF"><button onclick="togglediv()" class="button button2">OFF</button></a></p></div>
        
	</td>
</tr>
<tr>
	<td>
        <div id="saladeestar">Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;<a href="/estarON"><button onclick="togglediv23()" class="button button3">ON</button></a></div>
       <div id="saladeestar2" style="display:none">Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;<a href="/estarOFF"><button onclick="togglediv23()" class="button button4">OFF</button></a></div>
    </td>
</tr>
<tr>
	<td>
    	<div id="saladejantar">Sala de jantar &nbsp;&nbsp;&nbsp;<a href="/jantarON"><button onclick="togglediv22()" class="button button3">ON</button></a></div>
       <div id="saladejantar2" style="display:none">Sala de jantar &nbsp;&nbsp;&nbsp;<a href="/jantarOFF"><button onclick="togglediv22()" class="button button4">OFF</button></a></div>
    </td>
 </tr>
 <tr>
	<th>
		Aquecimento Automático
	</th>
	<td>
		<div id="autoheating"><p><a href="/aquecON"><button onclick="togglediv1()" class="button">ON</button></a></p></div>
    	<div id="autoheating2" style="display:none"><p><a href="/aquecOFF"><button onclick="togglediv1()" class="button button2">OFF</button></a></p></div>
        
	</td>
</tr>
<tr>
	<th>
		Temperatura Exterior
    </th>
    <td>
    	"Colocar Valor do Sensor"
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
		<input type="range" min="20" max="30" value="25" step="0.5" class="slider" onchange="showValue(this.value)" />
			<span id="range">25</span>
				<script type="text/javascript">
					function showValue(newValue)
					{
					document.getElementById("range").innerHTML=newValue;
					}
				</script>
                ºC
	</td>
</tr>
<th colspan="3">Aquecimento</th>
<tr>
	<th>
    	Sala
    </th>
	<td>
		<div id="sala" style="display:none"><p><a href="/salaON"><button onclick="togglediv2()" class="button">ON</button></a></p></div>
    	<div id="sala2"><p><a href="/salaOFF"><button onclick="togglediv2()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
	</th>
    <td>
		<div id="cozinha" style="display:none"><p><a href="/cozinhaON"><button onclick="togglediv3()" class="button">ON</button></a></p></div>
    	<div id="cozinha2"><p><a href="/cozinhaOFF"><button onclick="togglediv3()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Quarto
	</th>
	<td>
		<div id="quarto" style="display:none"><p><a href="/quartoON"><button onclick="togglediv4()" class="button">ON</button></a></p></div>
    	<div id="quarto2"><p><a href="/quartoOFF"><button onclick="togglediv4()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
	</th>
	<td>
		<div id="banho" style="display:none"><p><a href="/banhoON"><button onclick="togglediv5()" class="button">ON</button></a></p></div>
    	<div id="banho2"><p><a href="/banhoOFF"><button onclick="togglediv5()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<th colspan="3">Luzes</th>
<tr>
	<th>
    	Hall de entrada
    </th>
	<td>
		<div id="hall" style="display:none"><p><a href="/l0ON"><button onclick="togglediv6()" class="button">ON</button></a></p></div>
    	<div id="hall2"><p><a href="/l0OFF"><button onclick="togglediv6()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	<div  id="salas5">Sala de estar</div>
    </th>
	<td>
		<div id="estar" style="display:none"><p><a href="/l1ON"><button onclick="togglediv7()" class="button">ON</button></a></p></div>
    	<div id="estar2"><p><a href="/l1OFF"><button onclick="togglediv7()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Sala de jantar
    </th>
	<td>
		<div id="jantar" style="display:none"><p><a href="/l2ON"><button onclick="togglediv8()" class="button">ON</button></a></p></div>
    	<div id="jantar2"><p><a href="/l2OFF"><button onclick="togglediv8()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
    </th>
	<td>
		<div id="cozinha3" style="display:none"><p><a href="/l3ON"><button onclick="togglediv9()" class="button">ON</button></a></p></div>
    	<div id="cozinha4"><p><a href="/l3OFF"><button onclick="togglediv9()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Quarto
    </th>
	<td>
		<div id="quarto3" style="display:none"><p><a href="/l4ON"><button onclick="togglediv10()" class="button">ON</button></a></p></div>
    	<div id="quarto4"><p><a href="/l4OFF"><button onclick="togglediv10()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
    </th>
	<td>
		<div id="banho3" style="display:none"><p><a href="/l5ON"><button onclick="togglediv11()" class="button">ON</button></a></p></div>
    	<div id="banho4"><p><a href="/l5OFF"><button onclick="togglediv11()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Armário Hall
    </th>
	<td>
		<div id="armario" style="display:none"><p><a href="/l6ON"><button onclick="togglediv12()" class="button">ON</button></a></p></div>
    	<div id="armario2"><p><a href="/l6OFF"><button onclick="togglediv12()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Guarda-vestidos
    </th>
	<td>
		<div id="guardavestidos" style="display:none"><p><a href="/l7ON"><button onclick="togglediv13()" class="button">ON</button></a></p></div>
    	<div id="guardavestidos2"><p><a href="/l7OFF"><button onclick="togglediv13()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th colspan="3"><div id="cortinas">Cortina</div></th>
</tr>
<tr>
	<th colspan="3">
    <div id="cortina" style="display:none"><p><a href="/cortinaON"><button onclick="togglediv14()" class="button">OPEN</button></a></p></div>
    	<div id="cortina2"><p><a href="/cortinaOFF"><button onclick="togglediv14()" class="button button2">CLOSED</button></a></p></div>
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
		<div id="entrada" style="display:none"><p><a href="/d0ON"><button onclick="togglediv15()" class="button">OPEN</button></a></p></div>
    	<div id="entrada2"><p><a href="/d0OFF"><button onclick="togglediv15()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Sala 
    </th>
	<td>
		<div id="sala3"><p><a href="/d1ON"><button onclick="togglediv16()" class="button">OPEN</button></a></p></div>
        <div id="sala4" style="display:none"><p><a href="/d1OFF"><button onclick="togglediv16()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Sala-cozinha
    </th>
	<td>
		<div id="salacozinha"><p><a href="/d2ON"><button onclick="togglediv17()" class="button">OPEN</button></a></p></div>
        <div id="salacozinha2" style="display:none"><p><a href="/d2OFF"><button onclick="togglediv17()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Cozinha
    </th>
	<td>
    	<div id="cozinha5" style="display:none"><p><a href="/d3ON"><button onclick="togglediv18()" class="button">OPEN</button></a></p></div>
    	<div id="cozinha6"><p><a href="/d3OFF"><button onclick="togglediv18()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Quarto
    </th>
	<td>
		<div id="quarto5" style="display:none"><p><a href="/d4ON"><button onclick="togglediv19()" class="button">OPEN</button></a></p></div>
        <div id="quarto6"><p><a href="/d4OFF"><button onclick="togglediv19()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Quarto-casa de banho
    </th>
	<td>
		<div id="quartobanho" style="display:none"><p><a href="/d5ON"><button onclick="togglediv20()" class="button">OPEN</button></a></p></div>
        <div id="quartobanho2"><p><a href="/d5OFF"><button onclick="togglediv20()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Casa de banho
    </th>
	<td>
		<div id="banho5" style="display:none"><p><a href="/d6ON"><button onclick="togglediv21()" class="button">OPEN</button></a></p></div>
        <div id="banho6"><p><a href="/d6OFF"><button onclick="togglediv21()" class="button button2">CLOSED</button></a></p></div>
	</td>
</tr>
</table>
</body>
</html>

)=====";
