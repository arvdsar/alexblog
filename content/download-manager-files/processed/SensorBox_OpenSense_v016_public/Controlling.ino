// This file contains the statements to switch relays, read data or send wireless transmissions based on 'readString'

void StartSwitching(String readString){
  
  
 
  
        if (readString.startsWith("sensor")){          
          StringParse(readString); //parse received readstring 
          }
          
       else if(readString.startsWith("help")){
          telnetserver.println(VERSION);
          telnetserver.println();
          telnetserver.println(F("Available Commands: "));
          telnetserver.println();
          telnetserver.println(F("sensoradd,SENSORNODE,FEEDID1,FEEDID2,FEEDID3,FEEDID4,FEEDID5,UPDATE_FREQUENCY"));
          telnetserver.println(F("sensorlist   --> Shows EEPROM Dump"));
          telnetserver.println(F("sensorshow,SENSORNODE,  --> Shows FeedID's of SENSORNODE"));
          telnetserver.println(F("sensorcount,5, --> set amount of sensors to 5"));
          telnetserver.println(F("sensordata,on or sensordata,off --> show received data from sensors"));
        }


}
          
                
     
