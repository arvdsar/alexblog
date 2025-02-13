//********* RF12 transceiver code *****
void Process_RF12(){
  
  if(millis() > (BlueLed_Milli + 500))  //Processing received data goes to fast to really show blue led. Now the led is reset to yellow after 500 millis in next cycle
    RGBLed(yellow);
    
   if (rf12_recvDone() && rf12_crc == 0){ // && rf12_len == sizeof inData_3) {
         nodeID = rf12_hdr & 0x1F;  // get node ID from header
        
        RGBLed(blue); //Blue led at receiving data
        BlueLed_Milli = millis();
        procesInData(); //check which struct is being received, do the memcpy to struct and process data. then return.
        
        // optional: rf12_recvDone(); // re-enable reception right away
    }

    if (sendTimer.poll(100))
  
   if(pendingOutput == 0); //if no data to be send, don't do anything and therefore skip next 'else if'  statements.
/*
    //send Payload 1 which is SolarMonitor data
  else if (pendingOutput  == SOLAR_STRUCT && rf12_canSend()) {  //pendingOutput is set in: getdatafromarray() and defines the structtype used
     //  Serial.println("RF12 sends Struct type 1");
       rf12_sendStart(0, &outData_1, sizeof outData_1); //0 is header. anders eens 2 proberen.
       // optional: rf12_sendWait(2); // wait for send to finish
       pendingOutput = 0;
    }
  
    //send Payload 2 which is Sun/Moon times data
    else if (pendingOutput == SUNTIMES_STRUCT && rf12_canSend()) {
//       Serial.println("RF12 sends Struct type 2");
       rf12_sendStart(0, &outData_2, sizeof outData_2); //0 is header. anders eens 2 proberen.
       // optional: rf12_sendWait(2); // wait for send to finish
       pendingOutput = 0;
    }
    */
    //just repeat else if statements above to add more structs (and add return type in getdatafromarray() function
}  
  
  
  // ****** end RF12 transceiver code *****
  
 void procesInData(){
     
  //Identify type of struct:
  byte WhichStruct = rf12_data[0]; //first byte in rf12 data (which is part of struct) identifies struct type
  
  Serial.println();
  Serial.print(F("RF12 data received, Struct: "));
  Serial.println(WhichStruct);
  if(connectFlag){
      telnetserver.print(F("RF12 data received, Struct: "));
      telnetserver.println(WhichStruct); 
  }   
  switch (WhichStruct){
   //add more cases when you want to process more incoming data types
    
     case SOLAR_STRUCT:
        memcpy(&inData_1, (byte*) rf12_data, sizeof inData_1);
       
       //int's can be used directly in sendbuffer using %d. Floats need to be converted to char array strings.
        EnergyLastUpdate = millis();
        actual = inData_1.actual;
        peak = inData_1.peak;
        Nactual = inData_1.Nactual;
        NactualReturn = inData_1.NactualReturn;
        TotalActual = inData_1.TotalActual;
        today = inData_1.today;
        total = inData_1.total;
        dtostrf(float(inData_1.GasUsage)/1000,2,3,GasUsage);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        if(inData_1.Doorbell)
          Doorbell = 1;
        NetToday = inData_1.NetToday;
        TotalToday = inData_1.TotalToday;
        
        Serial.print("Domo status: ");
        Serial.println(inData_1.DomoStatus);
        Serial.print("today: ");
        Serial.println(today);
        Serial.print("Nettoday: ");
        Serial.println(NetToday);
        Serial.print("TotalToday: ");
        Serial.println(TotalToday);
        Serial.println("_________________________");
        Serial.println();
        
        if(connectFlag){ //send to telnet when client is connected
          telnetserver.print("Domo status: ");
          telnetserver.println(inData_1.DomoStatus);
          telnetserver.println("_________________________");
          telnetserver.println();
        }
        
        break; //end of solar struct case
   
    case  ALARM_STRUCT:
       memcpy(&inData_7, (byte*) rf12_data, sizeof inData_7);
      Serial.print("Alarm: ");
      Serial.println(inData_7.alarm);
      Serial.println();
      break;
   
    case TEMP_STRUCT: //Struct of sensor
      
      
      memcpy(&inData_3, (byte*) rf12_data, sizeof inData_3);
      Serial.print("Header nodeID: ");
      Serial.println(nodeID);
      Serial.print("which_Struct: ");
      Serial.println(inData_3.which_Struct);
      Serial.print("NodeID: ");
      Serial.println(inData_3.NodeID);
      Serial.print("Var1: ");
      Serial.println(float(inData_3.var_1)/100);
      Serial.print("Var2: ");
      Serial.println(float(inData_3.var_2)/100);
      Serial.print("Var3: ");
      Serial.println(float(inData_3.var_3)/100);
      Serial.print("Var4: ");
      Serial.println(float(inData_3.var_4)/100);
      Serial.print("Var5: ");
      Serial.println(float(inData_3.var_5)/100);
      Serial.print("Voltage: ");
      Serial.print(float(inData_3.supplyV)/1000);
      Serial.println("V");
      Serial.print("Sendcounter: ");
      Serial.println(inData_3.sendcounter);
      Serial.println("_________________________");
      Serial.println();
     
      if(connectFlag){ //send to telnet when client is connected
        telnetserver.print("Header nodeID: ");
        telnetserver.println(nodeID);
        telnetserver.print("which_Struct: ");
        telnetserver.println(inData_3.which_Struct);
        telnetserver.print("NodeID: ");
        telnetserver.println(inData_3.NodeID);
        telnetserver.print("Var1: ");
        telnetserver.println(float(inData_3.var_1)/100);
        telnetserver.print("Var2: ");
        telnetserver.println(float(inData_3.var_2)/100);
        telnetserver.print("Var3: ");
        telnetserver.println(float(inData_3.var_3)/100);
        telnetserver.print("Var4: ");
        telnetserver.println(float(inData_3.var_4)/100);
        telnetserver.print("Var5: ");
        telnetserver.println(float(inData_3.var_5)/100);
        telnetserver.print("Voltage: ");
        telnetserver.print(float(inData_3.supplyV)/1000);
        telnetserver.println("V");
        telnetserver.print("Sendcounter: ");
        telnetserver.println(inData_3.sendcounter);
        telnetserver.println("_________________________");
        telnetserver.println();
        
      }
    
      
      var_1_Arr[nodeID-1] = inData_3.var_1;
      var_2_Arr[nodeID-1] = inData_3.var_2;
      var_3_Arr[nodeID-1] = inData_3.var_3;
      var_4_Arr[nodeID-1] = inData_3.var_4;
      var_5_Arr[nodeID-1] = inData_3.var_5; 
      VoltArr[nodeID-1] = inData_3.supplyV;
      UpdateArr[nodeID-1] = millis(); //store current time to check if sensor has updated lately ;-)
      
      break;
    
    default:
      break;
  } //end switch
  
  
 }
 
 
