void sendToWunderground(){
  Serial.println(F("connecting to Wunderground.com..."));
  if(connectFlag) //send to telnet when client is connected
      telnetserver.println(F("\nconnecting to Wunderground.com..."));
      
    RGBLed(mint); //mint green led at sending

EthernetClient WundergroundClient; //Wunderground client connection

   
        
  double DewPnt = dewPoint(double (var_1_Arr[1])/100, double(var_2_Arr[1])/100); //DewPoint in Celcius
  DewPnt = 1.8 * DewPnt + 32; //create DewPnt in Fahrenheit
  
  if (WundergroundClient.connect("weatherstation.wunderground.com", 80) && (var_1_Arr[1] != -999)) {
    Serial.println(F("connected to Wunderground and uploading"));

    WundergroundClient << F("GET /weatherstation/updateweatherstation.php?ID=");
    WundergroundClient << YOURID;
    WundergroundClient << F("&PASSWORD=");
    WundergroundClient << YOURPASSWORD;
    sprintf(webData, "&dateutc=%04d-%02d-%02d %02d:%02d:%02d", year(),month(),day(), hour(),minute(),second());
    WundergroundClient << webData;
    WundergroundClient << "&tempf=";    

      float fahrenheit = float(var_1_Arr[1])/100;
     fahrenheit = 1.8 * fahrenheit + 32;

    dtostrf(fahrenheit,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     

    WundergroundClient << buffer;
    if(var_2_Arr[1] < 9960 && var_2_Arr[1] != -999){ //Humidity greater than 99,6% is probably not valid so only upload when humid is lower.
      WundergroundClient << "&humidity=";
      dtostrf(float(var_2_Arr[1])/100,1,0,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     

      WundergroundClient << buffer;
      WundergroundClient << "&dewptf=";
      WundergroundClient << DewPnt;
    }
    WundergroundClient << "&softwaretype=SensorBox_";
    WundergroundClient << VERSIONNR;

    WundergroundClient << "&action=updateraw";
    WundergroundClient << " HTTP/1.1" << endl;  //changed from 1.0
    WundergroundClient << "Host: weatherstation.wunderground.com" << endl;
    WundergroundClient << "Connection: close" << endl;

    WundergroundClient << "Accept: text/html" << endl;
    WundergroundClient << endl;
  
    Serial.println("Weather data send");
    if(connectFlag) //send to telnet when client is connected
      telnetserver.println("Weather data send");
      
    delay(100); //give some time to send data
     while(WundergroundClient.available())
        {
            char c = WundergroundClient.read();
            Serial.print(c);
        }
        
    WundergroundClient.stop();
    Serial.println(F("Disconnected from Wunderground."));
    if(connectFlag) //send to telnet when client is connected
      telnetserver.println(F("Disconnected from Wunderground.\n"));
      
    RGBLed(yellow); //Yellow Led at idle     

  }
  else {
    RGBLed(red); //Red led at connection error
    Serial.println(F("connection to Wunderground failed!"));
    if(connectFlag) //send to telnet when client is connected
      telnetserver.println(F("connection to Wunderground failed! - Network Re-init"));
    byte err;
    pf.init(&err, 1, MACADDRESS); //reinit network interface
    Serial.println(F("Network reinitialized"));
    RGBLed(yellow); //Yellow Led at idle     

  }
}

double dewPoint(double celsius, double humidity)
{
	double A0= 373.15/(273.15 + celsius);
	double SUM = -7.90298 * (A0-1);
	SUM += 5.02808 * log10(A0);
	SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
	SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
	SUM += log10(1013.246);
	double VP = pow(10, SUM-3) * humidity;
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558-T);
}
