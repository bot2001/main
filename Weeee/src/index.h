const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html>
<
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
    var div = document.getElementById('salas');
    div.style.display = div.style.display == "none" ? "block" : "none";
    var div2 = 	document.getElementById('salas2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";
    var div3 = 	document.getElementById('salas3');
    div3.style.display = div3.style.display == "block" ? "none" : "block";
    var div4 = 	document.getElementById('salas4');
    div4.style.display = div4.style.display == "block" ? "none" : "block";
    var div5 = 	document.getElementById('salas5');
    div5.style.display = div5.style.display == "block" ? "none" : "block";
    var div6 = 	document.getElementById('salas6');
    div6.style.display = div6.style.display == "block" ? "none" : "block";
    var div7 = document.getElementById('cortinas');
    div7.style.display = div7.style.display == "none" ? "block" : "none";
    var div8 = document.getElementById('cortinas2');
    div8.style.display = div8.style.display == "none" ? "block" : "none";
}
</script>
<script>
function togglediv2() {
	var div = document.getElementById('cozinha');
    div.style.display = div.style.display == "block" ? "none" : "block";
	var div2 = 	document.getElementById('cozinha2');
	div2.style.display = div2.style.display == "block" ? "none" : "block";
    var div3 = document.getElementById('sala1');
    div3.style.display = div3.style.display == "none" ? "block" : "none";
    var div4 = document.getElementById('sala2');
    div4.style.display = div4.style.display == "none" ? "block" : "none";
    var div5 = document.getElementById('sala3');
    div5.style.display = div5.style.display == "none" ? "block" : "none";
    var div6 = document.getElementById('sala4');
    div6.style.display = div6.style.display == "none" ? "block" : "none";
    var div7 = document.getElementById('cozinha3');
    div7.style.display = div7.style.display == "block" ? "none" : "block";
	var div8 = 	document.getElementById('cozinha4');
	div8.style.display = div8.style.display == "block" ? "none" : "block";}
</script>
<script>
function togglediv3() {
	var div = document.getElementById('cozinha3');
    div.style.display = div.style.display == "block" ? "none" : "block";
	var div2 = 	document.getElementById('cozinha4');
	div2.style.display = div2.style.display == "block" ? "none" : "block";}
</script>
<script>
function togglediv4() {
	var div = document.getElementById('quarto');
    div.style.display = div.style.display == "none" ? "block" : "none";
	var div2 = 	document.getElementById('quarto2');
	div2.style.display = div2.style.display == "none" ? "block" : "none";}
</script>
<script>
function togglediv5() {
	var div = document.getElementById('banho');
    div.style.display = div.style.display == "none" ? "block" : "none";
	var div2 = 	document.getElementById('banho1');
	div2.style.display = div2.style.display == "none" ? "block" : "none";}
</script>
<script>
function togglediv6() {
	var div = document.getElementById('sala5');
    div.style.display = div.style.display == "block" ? "none" : "block";
	var div2 = 	document.getElementById('sala6');
	div2.style.display = div2.style.display == "block" ? "none" : "block";
     var div3 = document.getElementById('quarto3');
    div3.style.display = div3.style.display == "block" ? "none" : "block";
    var div4 = document.getElementById('quarto4');
    div4.style.display = div4.style.display == "block" ? "none" : "block";
    var div5 = document.getElementById('banho2');
    div5.style.display = div5.style.display == "block" ? "none" : "block";
    var div6 = document.getElementById('banho3');
    div6.style.display = div6.style.display == "block" ? "none" : "block";
    var div7 = document.getElementById('over');
    div7.style.display = div7.style.display == "block" ? "none" : "block";}
    
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
		<p><button class="button"  onclick="togglediv()" >ON</button></p>
        
	</td>
</tr>
<tr>
	<td>
        <div id="salas">Sala de estar &nbsp;&nbsp;&nbsp;&nbsp;<input style="height: 26px; width:26px; margin-left:0" value="" checked="" type="checkbox"></div>
    </td>
</tr>
<tr>
	<td>
       <div id="salas2"> Sala de jantar&nbsp;&nbsp;&nbsp;&nbsp;<input style="height: 26px; width:26px; margin-left:0" value="" checked="" type="checkbox"></div>
    </td>


<tr>
	<th>
		Aquecimento Automático
	</th>
	<td>
		<p><a ><button onclick="togglediv6()" class="button">ON</button></a></p>
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
		<input type="range" min="0" max="30" value="20" step="0.5" class="slider" onchange="showValue(this.value)" />
			<span id="range">20</span>
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
		<p><a ><button onclick="togglediv2()" class="button button2">OFF</button></a></p>
	</td>
</tr>

<tr>
	<th>
    	<div style="display:none" id="cozinha">Cozinha</div>
	</th>
    <td>
		<div style="display:none" id="cozinha2"><p><a ><button onclick="togglediv3()" class="button button2">OFF</button></a></p></div>
	</td>
</tr>

<tr>
	<th>
    	Quarto
	</th>
	<td>
		<p><a ><button onclick="togglediv4()" class="button button2">OFF</button></a></p>
	</td>
</tr>

<tr>
	<th>
    	Casa de banho
	</th>
	<td>
		<p><a ><button onclick="togglediv5()" class="button button2">OFF</button></a></p>
	</td>
</tr>

<th colspan="3">Luzes</th>

<tr>
	<th>
    	Hall de entrada
    </th>
	<td>
		<p><a ><button class='button button2'>OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	<div style="display:none" id="salas5">Sala de estar</div>
    </th>
	<td>
		<div style="display:none" id="salas3"><p><a ><button class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	<div style="display:none" id="salas6">Sala de jantar</div>
    </th>
	<td>
		<div style="display:none" id="salas4"><p><a ><button class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	Cozinha
    </th>
	<td>
		<p><a ><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Quarto
    </th>
	<td>
		<p><a ><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Casa de banho
    </th>
	<td>
		<p><a ><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Armário Hall
    </th>
	<td>
		<p><a ><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th>
    	Guarda-vestidos
    </th>
	<td>
		<p><a ><button class="button button2">OFF</button></a></p>
	</td>
</tr>
<tr>
	<th colspan="3"><div id="cortinas">Cortina</div></th>
</tr>
<tr>
	<th colspan="3">
    <div id="cortinas2"><p><a ><button class="button">OPEN</button></a></p></div>
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
		<p><a ><button class="button">OPEN</button></a></p>
	</td>
</tr><tr>
	<th>
    	<div id="sala1">Sala</div> 
    </th>
	<td>
		<div id="sala2"><p><a ><button class="button">OPEN</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	<div id="sala3">Sala-cozinha</div>
    </th>
	<td>
		<div id="sala4"><p><a ><button class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	<div style="display:none" id="cozinha3">Cozinha</div>
    </th>
	<td>
		<div style="display:none" id="cozinha4"><p><a ><button class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	<div id="quarto">Quarto</div>
    </th>
	<td>
		<div id="quarto2"><p><a ><button class="button button2">CLOSED</button></a></p></div>
	</td>
</tr><tr>
	<th>
    	Quarto-casa de banho
    </th>
	<td>
		<p><a ><button class="button button2">CLOSED</button></a></p>
	</td>
</tr><tr>
	<th>
    	<div id="banho">Casa de banho</div>
    </th>
	<td>
		<div id="banho1"><p><a ><button class="button button2">CLOSED</button></a></p></div>
	</td>
</tr>

<th colspan="3"> <div style="display:none" id="over">Override de aquecimento</div></th>

<tr>
	<th>
    	<div style="display:none" id="sala5">Sala</div>
    </th>
	<td>
		<div style="display:none" id="sala6"><p><a ><button class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	<div style="display:none" id="quarto3">Quarto</div>
    </th>
	<td>
		<div style="display:none" id="quarto4"><p><a ><button class="button button2">OFF</button></a></p></div>
	</td>
</tr>
<tr>
	<th>
    	<div style="display:none" id="banho2">Casa de banho</div>
    </th>
	<td>
		<div style="display:none" id="banho3"><p><a ><button class="button button2">OFF</button></a></p></div>
	</td>
</tr>

</table>

</body>
</html>
<script>

// mete o código aqui

</script>
)=====";