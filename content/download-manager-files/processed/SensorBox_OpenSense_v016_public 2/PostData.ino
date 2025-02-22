 void PostDataToSense(){
  currentMillis = millis(); //current time


  Serial.println(F("Start uploading values to OpenSenSe."));
  if(connectFlag)
      telnetserver.println(F("Start uploading values to OpenSenSe."));
  RGBLed(green); //Green led at sending
   

/*
EEPROM Storage:
Each node has 6 arrays (var1 to var5 and voltageArray)
each value in the array is of type LONG and takes 4 bytes each

To calculate the memory address to use: Arrayposition x numberofarrays x numberofbytes + varposition
this becomes: (v*6*4)+1 --> (v*28)+1 (where 1 is var1, 2 is var2, 3 is var3)
i.e. nodeID1 is stored in array[0] --> (0*28)+1 --> var1 of nodeID 1 is stored on position 1
(1*28)+3 = 27 --> var3 of NodeID 2 is stored on position 27 (it's a long so 27,28,29, 30 are used for this long)
*/

//memory blocks, each blok is 4 bytes. So address is 1, 5, 9, 13, 17, 21, 25 for var1, var2, var3, var4, var5, var6, updatefrequency
//update frequency deterimes how often a value will be uploaded. If frequency is 5, it will be uploaded a 0:05, 0:10, and so on.

  for(int v=0;v < NO_OF_SENSORS; v++){
     Serial.print("Minute: ");
     Serial.println(minute());
          Serial.print("Freq: ");
     Serial.println(EEPROM.readLong(OffSet+(v*28)+25));
   if(minute() % EEPROM.readLong(OffSet+(v*28)+25)==0){ //Modulo van minute() % frequentie van upload in EEPROM

 
     if((UpdateArr[v]+120000) > currentMillis){ //UpdateArr is set for one sensorNode. so one check per loop is sufficient.
      Serial.println("UPLOADING");
      if(var_1_Arr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+1) != 0)){ // if EEPROM does not contain valid FeedID, skip (0 is not valid)
      //  ftoa(buffer,float(var_1_Arr[v])/100,2);
        dtostrf(float(var_1_Arr[v])/100,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+1), buffer);
        }
       
      if(var_2_Arr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+5) != 0)){
      //  ftoa(buffer,float(var_2_Arr[v])/100,2);
        dtostrf(float(var_2_Arr[v])/100,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+5), buffer);
        }
 
      if(var_3_Arr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+9) != 0)){
        //ftoa(buffer,float(var_3_Arr[v])/100,2);
        dtostrf(float(var_3_Arr[v])/100,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+9), buffer);
        }
   
      if(var_4_Arr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+13) != 0)){
     //   ftoa(buffer,float(var_4_Arr[v])/100,2);
        dtostrf(float(var_4_Arr[v])/100,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+13), buffer);
        }
   
      if(var_5_Arr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+17) != 0)){
       // ftoa(buffer,float(var_5_Arr[v])/100,2);
        dtostrf(float(var_5_Arr[v])/100,2,1,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+17), buffer);
        }     
       
      if(VoltArr[v] != -999 && (EEPROM.readLong(OffSet+(v*28)+21) != 0)){
       // ftoa(buffer,float(VoltArr[v])/1000,2);
        dtostrf(float(VoltArr[v])/1000,2,2,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
        pf.postSense(EEPROM.readLong(OffSet+(v*28)+21), buffer);
        }
        
    } //end of if UpdateArr 
   }  // end of if updateCnt
  } //end of update loop  
  
 
  
//********** SPECIAL DATA UPDATES ********

//Energy Monitor values
  if(EnergyLastUpdate + 70000 > currentMillis){  //update only when data is not older than 70 seconds
        sprintf(buffer,"%d", actual);
        pf.postSense(ActualFeed, buffer);
        sprintf(buffer,"%d", peak);
        pf.postSense(PeakFeed, buffer);
        sprintf(buffer,"%d", today);
        pf.postSense(TodayFeed, buffer);
        sprintf(buffer,"%d", total);
        pf.postSense(TotalFeed, buffer);
        sprintf(buffer,"%d", Nactual);
        pf.postSense(NactualFeed, buffer);
        sprintf(buffer,"%d", NactualReturn);
        pf.postSense(NactualReturnFeed, buffer);
        sprintf(buffer,"%d", TotalActual);
        pf.postSense(TotalActualFeed, buffer);
        sprintf(buffer,"%s", GasUsage);
        pf.postSense(GasUsageFeed, buffer);
        sprintf(buffer,"%d", NetToday);
        pf.postSense(NetTodayFeed, buffer);
        sprintf(buffer,"%d", TotalToday);
        pf.postSense(TotalTodayFeed, buffer);     
     
     //Doorbell status, send a 1 when doorbell is pushed.
     if(Doorbell){
        pf.postSense(DoorbellFeed, "1");
        Doorbell = 0;
       }
       
  // Domotica Light status
  //if (inData_1.DomoStatus != Prev_DomoStatus){

  ProcessReceivedDomo(inData_1.DomoStatus); // extract switch statusses from Domo received value
  
  
   //indoorlighting:
   
   strcpy(buffer,"Lights on: ");
   if(LampA_Status == 'A')
     strcat(buffer,"LampA ");
   if(LampB_Status == 'B')
     strcat(buffer,"LampB ");
   if(LampC_Status == 'C') 
     strcat(buffer,"LampC ");
   if(LampD_Status == 'D')
     strcat(buffer,"LampD ");
   if(LampE_Status == 'E')
     strcat(buffer,"LampE ");
   if(LampF_Status == 'F')
     strcat(buffer,"LampF ");
   
   pf.postSense(IndoorLightingFeed, buffer);
   
   strcpy(buffer,"Lights on: ");
   if(TuinVoor_Status == 'V')
     strcat(buffer,"TuinVoor ");
   if(TuinMidden_Status == 'M')
     strcat(buffer,"TuinMidden ");
   if(TuinAchter_Status == 'S') 
     strcat(buffer,"TuinAchter ");
   if(DeurLinks_Status == 'L')
     strcat(buffer,"DeurLinks ");
   if(DeurRechts_Status == 'R')
     strcat(buffer,"DeurRechts ");
   if(DeurAchter_Status == 'A')
     strcat(buffer,"DeurAchter");
   
   pf.postSense(OutdoorLightingFeed, buffer);
}
   
   Serial.println("Uploading individual Light statusses");
  

//******* Each light individually send *******
  if(LampA_Status == 'A')
    pf.postSense(LampA_Feed,"1");
    else
      pf.postSense(LampA_Feed,"0");
      
   if(LampB_Status == 'B')
    pf.postSense(LampB_Feed,"1");
    else
      pf.postSense(LampB_Feed,"0");
 
   if(LampC_Status == 'C')
    pf.postSense(LampC_Feed,"1");
    else
      pf.postSense(LampC_Feed,"0");
     
  if(LampD_Status == 'D')
    pf.postSense(LampD_Feed,"1");
    else
      pf.postSense(LampD_Feed,"0");
  
   if(LampE_Status == 'E')
    pf.postSense(LampE_Feed,"1");
    else
      pf.postSense(LampE_Feed,"0");
     
     
   if(TuinVoor_Status == 'V')
    pf.postSense(TuinVoor_Feed,"1");
    else
      pf.postSense(TuinVoor_Feed,"0");
     
   if(TuinMidden_Status == 'M')
    pf.postSense(TuinMidden_Feed,"1");
    else
      pf.postSense(TuinMidden_Feed,"0");
     
   if(TuinAchter_Status == 'S')
    pf.postSense(TuinAchter_Feed,"1");
    else
      pf.postSense(TuinAchter_Feed,"0");
     
          
  if(DeurLinks_Status == 'L')
    pf.postSense(DeurLinks_Feed,"1");
    else
      pf.postSense(DeurLinks_Feed,"0");
     
   if(DeurRechts_Status == 'R')
    pf.postSense(DeurRechts_Feed,"1");
    else
      pf.postSense(DeurRechts_Feed,"0");
     
    if(DeurAchter_Status == 'A')
    pf.postSense(DeurAchter_Feed,"1");
    else
      pf.postSense(DeurAchter_Feed,"0");
     
      
 Serial.println(F("Finished uploading values to OpenSenSe.")); 
 if(connectFlag)
      telnetserver.println(F("Finished uploading values to OpenSenSe.\n")); 
 RGBLed(yellow); //Yellow Led at idle     
 } //end of PostDataToSense();
 

