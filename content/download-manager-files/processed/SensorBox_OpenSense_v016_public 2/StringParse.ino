void StringParse(String inputString){
 
    char msg[inputString.length()+1];
    inputString.trim();
    inputString.toCharArray(msg,inputString.length()+1);

    int j=0;
    for(int i=0;i<inputString.length() && j<11;i++){
      
      if(msg[i] != ',')
        Text[j] += msg[i];
      else if(msg[i] == ','){
        Text[j] += '\0';
        j++;
      }
    }        
      GetDataFromArray(); //Get data from the array and process data
      
      for(int y=0;y<11;y++){ // erase array after processing with GetDataFromArray()
        Text[y]="";
      }
    
 
     
 }
 
 
byte GetDataFromArray(){ //add more IF statements (and enlarge Text Array when more variables are to be processed)
                         //this function only process the data from array and store in struct variables. 
   int SensorID;
   long FeedID;
   
    if(Text[0] == "sensoradd"){
       
      char value[Text[1].length()+1];  //SensorNode
      Text[1].toCharArray(value,Text[1].length()+1);
      SensorID=atoi(value);
      SensorID = SensorID - 1;
      
      int eepromPosition=1;
      for(int y=2; y<9; y++){
           Text[y].toCharArray(value,Text[y].length()+1);
           FeedID=atol(value);  
           EEPROM.updateLong(OffSet+(SensorID*28)+eepromPosition, FeedID);
           eepromPosition = eepromPosition + 4;
        }
       // display updated values. 
      telnetserver.print(F("Updated SensorNode ="));
      telnetserver.println(SensorID+1);
      eepromPosition=1;
      for(int y=2; y<9; y++){
          // Text[y].toCharArray(value,Text[y].length()+1);
           telnetserver.print(F("Value "));
           telnetserver.print(y-1);
           telnetserver.print(F(":  "));
           telnetserver.println(EEPROM.readLong(OffSet+(SensorID*28)+eepromPosition));
           eepromPosition = eepromPosition + 4;    
      }
      telnetserver.println(F("**** Ready ****"));

        
    } //end if sensoradd
    
    else  if(Text[0] == "sensorlist"){
         telnetserver.print(F("No of Sensors: "));
         telnetserver.println(EEPROM.readLong(1400));
         for(int w=1+OffSet; w < 1000 + OffSet; w=w+4){
          telnetserver.print(F("Address: "));
          telnetserver.print(w);
          telnetserver.print(F("  Value: "));
          telnetserver.println(EEPROM.readLong(w));
         }
         telnetserver.println(F("**** Ready ****"));
  }  
    
  else if(Text[0] == "sensorcount"){
          Text[1].toCharArray(value,Text[1].length()+1);
          SensorID=atoi(value);  
          EEPROM.updateInt(1400, SensorID); //SensorID is number of sensors in this case
          telnetserver.print(F("Number of Sensors is now: "));
          NO_OF_SENSORS = EEPROM.readInt(1400);
          telnetserver.println(NO_OF_SENSORS);
          telnetserver.println(F("Number of Sensors is now loaded!"));
          telnetserver.println(F("**** Ready ****"));

          
   }
   
  else if(Text[0] == "sensorshow" && Text[1] > "0"){
     // char value[Text[1].length()+1];  //SensorNode
      Text[1].toCharArray(value,Text[1].length()+1);
      SensorID=atoi(value);
      telnetserver.print(F("SensorNode ="));
      telnetserver.println(SensorID);
      SensorID = SensorID - 1; //sensorID used in EEPROM readlong below (starts at 0 instead of 1)
      int eepromPosition=1;
      for(int y=2; y<9; y++){
          // Text[y].toCharArray(value,Text[y].length()+1);
           telnetserver.print(F("Value "));
           telnetserver.print(y-1);
           telnetserver.print(F(":  "));
           telnetserver.println(EEPROM.readLong(OffSet+(SensorID*28)+eepromPosition));
           eepromPosition = eepromPosition + 4;    
      }
      telnetserver.println(F("**** Ready ****"));

   }  
   
  else if(Text[0] == "sensordata" && Text[1] == "on") //when set on, data is send to telnet output too
        connectFlag = 1;
  
  
    else if(Text[0] == "sensordata" && Text[1] == "off")
        connectFlag = 0;
    
} // end GetDataFromArray()
    
    
  



 
