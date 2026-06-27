/*  DATASTRUCTURE  --- Version 0.5  -- 19 february 2013  --- www.vdsar.net
This file contains the data structures used in "my" sensors and receivers. By using this file I'm sure I always use the same 
structures in every device. 
I believe there is no need to comment out any of those. The structs are initialized in the source code of the application.

*/
typedef struct { //currently 22 bytes of size
  	byte which_Struct;
  	byte NodeID;
  	unsigned int actual;  
  	unsigned int today; 
  	unsigned int peak; 
  	unsigned long total; 
  	unsigned int TotalActual;
  	unsigned int Nactual;  
  	unsigned int NactualReturn; 
  	unsigned int GasUsage; 
  	unsigned int NetToday;
  	long DomoStatus;
  	byte Doorbell;
  } Payload_1; //struct for solarmonitor & domoticaSwitches


typedef struct { 
 	byte which_Struct;
  	byte NodeID;
  	char sunrise[6];
  	char sunset[6];
  	char moonrise[6];
  	char moonset[6];
  } Payload_2; // struct for Sunrise/set and Moonrise/set times
  
  
typedef struct {
  byte which_Struct;
  byte NodeID;
  int humidity; 
  int temp; 
  int light; //added new
  int supplyV; 
  unsigned long sendcounter;
  } Payload_3; //struct for sensor 
  
  
typedef struct {
  	byte which_Struct;
  	byte NodeID;
  	int SensorType;
  	float Value1;
  	float Value2;
  	float Value3;
  	int Voltage;
  } Payload_4; //struct for sensor 
 
 
 typedef struct { //RGB led
    byte which_Struct;
    int red;              // sensor value
    int green;
    int blue;
    int supplyV;          // tx voltage
 } Payload_5;


typedef struct { //doorbell and domostatus NOT IN USE. Still using Domo & doorbell in Struct 1.
  	byte which_Struct;
 	byte NodeID;	
  	long DomoStatus;
  	byte Doorbell;
 } Payload_6;
 
 
 typedef struct {
      byte which_Struct;
      byte NodeID;	  
      int alarm;	// alarm status
     int supplyV;	// Supply voltage
 } Payload_7;
 
 
 typedef struct { //time sync
   byte which_Struct;
   unsigned long time;
 } Payload_8;
 
  
 #define SOLAR_STRUCT 1  //this defines the struct. Used in RF12, Getdatafromarray() to identify pendingoutput en ID the structure to be send
 #define SUNTIMES_STRUCT 2
 #define TEMP_STRUCT 3
 #define SENSOR_STRUCT 4
 #define RGB_STRUCT 5
 #define DOMO_STRUCT 6
 #define ALARM_STRUCT 7
 #define TIME_STRUCT 8
  
 
