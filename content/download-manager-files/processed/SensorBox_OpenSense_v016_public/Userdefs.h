#define OpenSenseAPIKEY "OPENSENSEAPIKEY"
#define OpenSenseDeviceID 9542
#define MACADDRESS "D4:28:B2:FE:A5:A5"  //make this address unique in your local network

/*
UpdateOpenSenseInterval should be set to 60000. Each minute PostDatatoSense is called. Based on the update frequency value for each node in eeprom it
is determined if during that call the data has to be updated for that node. i.e.: when frequency is set to 3 this means sensor x is uploaded once in 
3 minutes. 
*/

long updateOpenSenseInterval = 60000;      // Time resolution in milliseconds to update ThingSpeak (only change if you understand the code)

// WUNDERGROUND.COM CREDENTIALS:
#define YOURID "YOURLOGIN"              // this is your wunderground station ID
#define YOURPASSWORD "YourPASSWORD"  //this is you wunderground password

#define SensorBoxBoot_Feed 12345  //create a channel on open.sen.se of type input, string. This will contain the boottime of the sensorbox.


//energy monitor feed defines
 #define ActualFeed 12345
 #define PeakFeed 12345
 #define TodayFeed 12345
 #define TotalFeed 12345
 #define NactualFeed 12345
 #define NactualReturnFeed 12345
 #define TotalActualFeed 12345
 #define GasUsageFeed 12345
 #define NetTodayFeed 12345
 #define TotalTodayFeed 12345
 
 #define IndoorLightingFeed 12345
 #define OutdoorLightingFeed 12345
 
 #define DoorbellFeed 12345


 #define LampA_Feed 12345
 #define LampB_Feed 12345
 #define LampC_Feed 12345
 #define LampD_Feed 12345
 #define LampE_Feed 12345
 #define TuinVoor_Feed 12345
 #define TuinMidden_Feed 12345
 #define TuinAchter_Feed 12345
 #define DeurLinks_Feed 12345
 #define DeurRechts_Feed 12345
 #define DeurAchter_Feed 12345





//*********************************** DEFINE RF12 WIRELESS SETTINGS ******************
// ID 0 is reserved for OOK use
// node ID 31 is special because it will pick up packets for any node (in the same netGroup). 
#define NODEID    31
#define FREQBAND  RF12_868MHZ 
#define NETGROUP    201
#define ALT_NODEID   31 // alternative NODE ID included in Struct (not in header, that is NODEID). To be used when you send data to specific node, then this should contain origination node number
//Ter overdenking: nodeID 31 ontvangt alles. misschien houdt dit toestand wat bezig en kun je beter 29 kiezen en alleen broadcasts ontvangen. Al ontvang 31 alleen maar van NetGroup dus zou het niet uit moeten maken



