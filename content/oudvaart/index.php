<?php 

$url = 'https://home.vdsar.net/api/vaartapi';
$ch = curl_init($url);
$apiKey = 'Hd230a$6732%$^2';
$headers = array( 'Authorization: '.$apiKey,'Page: oudvaart');

curl_setopt($ch, CURLOPT_HTTPGET, true);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

$response_json = curl_exec($ch);
curl_close($ch);

$response=json_decode($response_json, true);
if($response == false){
    echo"De server met de meetgegevens is momenteel niet beschikbaar!<br>";
    echo"Dit duurt meestal niet al te lang. <br>";
    echo"De beheerder is geinformeerd. Probeer het later nog een keer!";
    mail("alexander@vdsar.net","Vaart API error","Vaart API ligt eruit! (home.vdsar.net/vaartapi)","From: itmonitor@vdsar.eu");

}
?>



<head>
	<!-- Global site tag (gtag.js) - Google Analytics -->
	<script async src="https://www.googletagmanager.com/gtag/js?id=UA-19404218-1"></script>
	<script>
 	 window.dataLayer = window.dataLayer || [];
 	 function gtag(){dataLayer.push(arguments);}
 	 gtag('js', new Date());

 	 gtag('config', 'UA-19404218-1');
	</script>

    <title>Oudvaart water temperatuur</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon">
	<link rel="icon" href="/favicon.ico" type="image/x-icon">
</head>
<body>

<img src = "toplogo.png" width = "400">
<p>
<table border=1>
    <tr><td>Oppervlakte</td><td><?php echo $response["oppervlak"]?>° C</td></tr>
    <tr><td>Bodem</td><td><?php echo $response["bodem"]?>° C</td></tr>
    <tr><td>+/- 1 meter boven water niveau in gesloten behuizing</td><td><?php echo $response["device"]?>° C</td></tr>
    <tr><td>Meting van</td><td><?php if($response["timestamp"] == "") echo"Sensor gegevens tijdelijk niet beschikbaar. Probeer over 1,5 uur nogmaals."; echo $response["timestamp"]?></td></tr>
</table>
Meting elke +/- 1,5 uur. <p><p>


<?php 
if($response["timestamp"] == ""){
        echo"<img src='smileyoops.jpg' alt='Foutje!' height='150' >";

}
else if((float)$response["oppervlak"] > 20){
         echo"<img src='smallbluesmiley.jpg' alt='Kans op blauwalg!' height='150' width='150'>";
         echo"<br>Boven de 20 graden is er verhoogde kans op blauwalg!<br>";
	}
 	else if((float)$response["oppervlak"] <= 10)
        echo"<img src='smallijskoudsmiley.png' alt='koud hoor!' height='150' width='150'>";
    	else
    	    echo"<img src='smileyswim.jpg' alt='lekker zwemmen!' height='150' width='150'>";
        ?>
<p>De informatie is nu ook beschikbaar als <a href="https://telegram.org" target="_blank">Telegram Bot.</a><br>In de Telegram App voeg je toe:</br>
<b>@OudvaartBot</b></br>

<p>
<a href="https://vdsar.net/aldfeart">Nei Fryske pagina</a><p>
<i>Connected by <a href="https://www.thethingsnetwork.org" target="-blank">The Things Network</a></i>
</body>
