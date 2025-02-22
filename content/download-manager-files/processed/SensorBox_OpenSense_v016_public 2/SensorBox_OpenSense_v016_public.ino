

/*
Sensor Box based upon the sources of Open.Sen.Se and extended with additional code for receiving wireless sensors.
Written by Alexander van der Sar and ofcourse some reuse of code from others found on the web.
http://www.vdsar.net 


v0.1 - prototype 
v0.2 - tried to make it generic for all sensors
v0.3 - revert 0.2. Make specific temperature sensor struct (remain with original idea) and optimze code
v0.4 - working with solar monitor values
v0.5 - added Domo received values. Bug found with using the array so duplicate values are uploaded. to be fixed
v0.6 - Rewritten to use arrays of INT's instead of 2D Char Arrays which were causing many headaches.
v0.6a - enlarged buffer[30] to 80. Size was to small for some texts.
v0.6b - enlarged buffer to 100 and changed Domo Light strings from letter to words
v0.6c - RGB led for status added
v0.6d - with sensor node 4 added
v0.7d - as v0.6d with upload to wunderground.com added (outdoor temp & humidity) Also added FlashMini.h for << in wunderground code
v0.7e - disabled daylight saving time and time offset. System running on UTC so time can be used to Wunderground.com directly
v0.7f - Calculated DewPoint added
v0.8 - same as v0.7f but needed version baseline
v0.8a - removed code that specified which sensors have humidity data. humidity is -999 when not existing on TinyTX so just store
        this value and do a check when uploading data to opensense (or leave out uploading). 
v0.8b - added simple telnet server
v0.8c - added nice telnet server with disconnect and help. Incl. timeout of connection 
v0.8d - added check in postdata IF statements to only update recent data (currentMillis)
v0.8e - added RGB.h
v0.8f - humidity > 99,6% is not uploaded to wunderground.com
v0.10 - based on v0.8f, prototype to make nodes more universal and storing FeedID's in EEPROM and PostData is looping an array instead
        of each post defined individual.
v0.11 - Added OffSet for EEPROM addresses to reserve some memory (set default at 100 so data is written starting at 101)
        also put serial speed to 115200 which might fix ethernet lockups
v0.12 - added doorbell registration.
v0.13 - added TotalToday & NetToday in data feed
v0.14 - Each light (lampA) has individual feed
v0.14a - FTOA function used before is buggy. 3.07 becomes 3.7 Not even thought about negative numbers.
         replaced by using: dtostrf(inputfloat,1,0,buffer);  // dtostrf=(x,W,P,x) Width= Characters including dot & minus sign. Precision= Characters after decimal point.     
v0.15 - added update frequency to EEPROM, watchdog and upload boottime to openSense
v0.16 - added telnet config for update EEPROM values.


EEPROM Information:
NO_OF_SENSORS is set on address 1000 (so INT is using 1000 & 1001).
Sensor FeedID's are stored in EEPROM starting on position 1 as LONG (so 4 bytes). So they are stored at position:
1, 5, 9, 13, etc.. (1+4)



******************************************************************************************************************
PLEASE NOTE: TIME IS IN UTC. wunderground.com expects timestamp in UTC and not local time. Keep this in mind!
If you do need local time, convert it in the program or modify file 'time' and uncomment the daylight saving stuff. 
But in that case, do something to use correct time to wunderground.com
******************************************************************************************************************
*/

#define VERSIONNR "v0.16"
#define VERSION "V0.16 - Sensor Box to Open.Sen.Se & Wunderground.com & Telnet - www.vdsar.net "


#include <SensuinoEth.h>
#include <SensuinoSerial.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <FlashMini.h>
#include <EEPROMEx.h> //eeprom extended library
#include <avr/wdt.h>
#include <MsTimer2.h>

#include <SPI.h>
#include <JeeLib.h>
#include <Time.h>
#include "RGB.h"

#include "Userdefs.h"
#include <DataStructure.h>

SensuinoEth pf;
EthernetUDP Udp;
EthernetServer telnetserver(23); //telnetserver port
//EthernetClient client;  // instantiate a client based on server(23)

char   webData[70];
String readString;
String Text[11]={"","","","","","","","","","",""};


boolean connectFlag = 0; //a flag to turn on/off sensor data via telnet

unsigned long currentMillis; 

const long int device_id = OpenSenseDeviceID; // This is your device's ID (change in userdefs.h)

unsigned long timeRef;
unsigned long BlueLed_Milli;
int lastMinute;


unsigned int actual=0;
unsigned int peak=0;
unsigned int Nactual=0;
unsigned int NactualReturn=0;
unsigned int TotalActual=0;
unsigned int today=0; 
unsigned long total=0;
char GasUsage[10]="0.0";
int NetToday=0;
int TotalToday=0;
unsigned long EnergyLastUpdate =0L;
byte Doorbell=0;

 Payload_1 inData_1; //Solarmonitor & Domotica Switches
 Payload_3 inData_3; //tempsensor data
 Payload_7 inData_7;

MilliTimer sendTimer;  //related to RF12
byte pendingOutput=0; //related to RF12
int nodeID;    //node ID of tx, extracted from RF datapacket. Not transmitted as part of structure


//480 bytes memory in use for all those arrays.
int var_1_Arr[30];
int var_2_Arr[30];
int var_3_Arr[30];
int var_4_Arr[30];
int var_5_Arr[30];
int VoltArr[30];
unsigned long UpdateArr[30]; // used to check if sensor has been updated lately

int val = 0;
char buffer[100]; //was 30
char value[20];

//char variable for my specific situation in which I store the status of my lights (Lamp means Light)
char LampA_Status = ' ';
char LampB_Status = ' ';
char LampC_Status = ' ';
char LampD_Status = ' ';
char LampE_Status = ' ';
char LampF_Status = ' ';
char TuinVoor_Status = ' ';
char TuinMidden_Status = ' ';
char DeurLinks_Status = ' ';
char DeurRechts_Status = ' ';
char DeurAchter_Status = ' ';
char TuinAchter_Status = ' ';
long Prev_DomoStatus = 0;


int NO_OF_SENSORS; //number of sensor nodes (set in EEPROM)
int OffSet = 200; //EEPROM memory address offset. Meaning first data is stored at address 201 for FeedIDs. 

//************************* SETUP *********************


void setup() {
  Serial.begin(115200);  
  
  pinMode(4, OUTPUT);      // sets the digital pin as output 
  digitalWrite(4, HIGH);   // Disable SDCard on EthernetShield
 
  RGBLed(white); //White light at boot
  
  Serial.print(F("Starting "));
  Serial.println(VERSION);
  Serial.print(F("Data upload every "));
  Serial.print(updateOpenSenseInterval/1000);
  Serial.println(F(" seconds."));
  
  EEPROM.setMemPool(0, 1410);

  NO_OF_SENSORS = EEPROM.readInt(1400); //get number of sensors from EEPROM at address 1400 (and 1401)
  Serial.print("NO_OF_SENSORS: ");
  Serial.println(NO_OF_SENSORS);
  
  
   //initialize RFM12b transceiver. Before network init for compatibility reasons
  rf12_initialize(NODEID, FREQBAND, NETGROUP);  
  
    byte err;
  // Use the following if you don't want to use DHCP
  // pf.init(&err, 0, "aa:bb:cc:dd:ee:ff", "192.168.1.150", "192.168.1.1");// First IP is for the Arduino, second IP is for the gateway
  pf.init(&err, 1, MACADDRESS);

  delay(1000);
  
  pf.setSenseKey(OpenSenseAPIKEY);// This is your sense key
  
  Serial.println(F("LAN Init done"));

  // For each output feed, get the last value and trigger the right PIN on the arduino
  //We listen for incoming events on the device (uncomment when you want incoming events
  //open.sen.se related and does not work very well. 
  //pf.longPollSense(device_id);
  
  // Init timeRef
  timeRef = millis();
  
  //initialize array with -999 a never existing value.
  for(int x=0;x < NO_OF_SENSORS;x++){
     var_1_Arr[x]=-999;
     var_2_Arr[x]=-999;
     var_3_Arr[x]=-999;
     var_4_Arr[x]=-999;
     var_5_Arr[x]=-999;
     VoltArr[x]=-999;
  }

     
     
  Serial.println(F("Total Init done"));
  
  SetupWatchdog();
  
  // start the timer interrupt for watchdog
  MsTimer2::set(2000, Every2000ms); // 2000ms period
  MsTimer2::start();
  
  Serial.println(F("WatchDog initialized"));
  
  RGBLed(magenta); //magenta light at start NTP request

  Udp.begin(8888);
  // wait until time is set
  Serial.println(F("UTC request time using NTP")); //if you want local time, enable DST in file 'time' 
  while(!UpdateTime());
  Serial.println(F("UTC Time is set"));
    
  sprintf(webData, "SensorBox " VERSIONNR " boottime: %02d-%02d-%04d %02d:%02d:%02d (UTC)", day(),month(),year(), hour(),minute(),second());
  Serial.println(webData);
  pf.postSense(SensorBoxBoot_Feed,webData); //post boottime to OpenSenSe
  
  lastMinute = minute();

  RGBLed(yellow); //Yellow in Idle status
  
  Serial.println("DUMP OF DATA IN EEPROM:");
  Serial.print("Number of Sensors: ");
  Serial.println(EEPROM.readInt(1400));
  for(int w=OffSet+1; w < OffSet+(NO_OF_SENSORS*28); w=w+4){
    Serial.print("Address: ");
    Serial.print(w);
    Serial.print("  Value: ");
    Serial.println(EEPROM.readLong(w));
  }
    
}// end of setup


void Every2000ms(){

    CheckWatchdog();
}

//*********************** LOOP **************************

void loop() {
      busy(1);
      delay(100); //you might try to remove this line. If watchdog triggers accidently. Keep it in here!
      
      Process_RF12(); //continiously check for incomming RF12 data and send data when it is available

/* commented out because there is no need for the sensorbox to check for incomming events!
  byte _check = pf.longPollCheck();
    if(_check == 0) {
      pf.longPollSense(device_id);
      
      unsigned long int feed_id = pf.getLastFeedId();
      char *str = pf.getLastValue();
            
    } else if(_check == 2) {
      pf.longPollSense(device_id);
    }
  */
  
    // Send the values from input feeds every minute or so
    if (millis() - timeRef > updateOpenSenseInterval) { 
      busy(2);
      PostDataToSense(); //upload data to openSense, because of the many statements this is moved to seperate file
                         // it might be a good idea to split the uploading in multiple parts when it becomes very long.
      busy(3);
      sendToWunderground(); 
      timeRef = millis();
    }
    
    /* if((lastMinute%5)==0)  //uncomment when you want to upload wunderground data only once per 5 minutes. (and comment sendToUnderground above )
        {
        Serial.println(F("Start uploading data to Wunderground"));
  
        sendToWunderground();
        lastMinute = minute();
        Serial.println(F("Finished uploading Data to Wunderground"));

        }*/
   
  // look to see if a new connection is created,
  // print welcome message, set connected flag
  busy(4);

  EthernetClient myclient = telnetserver.available();
    
  if (myclient){
    //Serial.print("Connected myclient on port: ");
    //Serial.println(MyServer_Port);
    
    while (myclient.available()) { //as long as data is available to read
        char c = myclient.read();
        //Serial.print(c,DEC); to debug ascii codes received 
        //Serial.print(" ");
        if (c == -1 || c == -20){ //ascii -1 and -20 are send when closing telnet app. just dump the characters
          //do not add characters to readString to prevent a closing telnet sesion to reserve a very large readString buffer
        }
        else
          readString += c;
     }
     
       busy(14);
       readString.trim(); //remove whitespaces from created readString. 
       Serial.print("readString == ");
       Serial.println(readString); //for debugging
       busy(15);
       StartSwitching(readString);
   
       readString = ""; //clean readString to receive new command via network
       busy(16); 
   
       if (!myclient.connected()) {
            myclient.stop();  
            //Serial.print("Disconnected myclient on port: ");
            //Serial.println(MyServer_Port);
          }
     
  }
     
  busy(0); //resets watchdog total timer. When removed watchdog will always be triggered 
}


int freeRam() 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

