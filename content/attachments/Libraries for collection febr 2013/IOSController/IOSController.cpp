/*
 *
 * IOSController library (“The Software”) and the related documentation (“The Documentation”) are supplied to you 
 * by the Author in consideration of your agreement to the following terms, and your use or installation of The Software and the use of The Documentation 
 * constitutes acceptance of these terms.  
 * If you do not agree with these terms, please do not use or install The Software.
 * The Author grants you a personal, non-exclusive license, under author's copyrights in this original software, to use The Software. 
 * Except as expressly stated in this notice, no other rights or licenses, express or implied, are granted by the Author, including but not limited to any 
 * patent rights that may be infringed by your derivative works or by other works in which The Software may be incorporated.
 * The Software and the Documentation are provided by the Author on an "AS IS" basis.  THE AUTHOR MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION THE IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, REGARDING THE SOFTWARE OR ITS USE AND OPERATION 
 * ALONE OR IN COMBINATION WITH YOUR PRODUCTS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, 
 * REPRODUCTION AND MODIFICATION OF THE SOFTWARE AND OR OF THE DOCUMENTATION, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), 
 * STRICT LIABILITY OR OTHERWISE, EVEN IF THE AUTHOR HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Author: Fabrizio Boco - fabboco@gmail.com
 *
 * All rights reserved
 *
 */

#include "IOSController.h"
#include <avr/eeprom.h>


#define ALARMCHECKDELAY 		  64000
#define ALARMCHECKDELAY_CONNECTED 50

#define LEAP_YEAR(Y)     ( ((1970+Y)>0) && !((1970+Y)%4) && ( ((1970+Y)%100) || !((1970+Y)%400) ) )

static  const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0

#ifdef ALARMS_SUPPORT
IOSController::IOSController(EthernetServer *server, 
                             void (*doWork)(void), 
                             void (*doSync)(char *variable),
                             void (*processIncomingMessages)(char *variable, char *value),
                             void (*processOutgoingMessages)(void),
                             void (*processAlarms)(char *alarm),
                             void (*deviceConnected)(void),
							 void (*deviceDisconnected)(void)
                             )
{
	_var = true;
    _idx = 0;
    _server = server;
    _doWork = doWork;
    _doSync = doSync;
    _processIncomingMessages = processIncomingMessages;
    _processOutgoingMessages = processOutgoingMessages;
    _processAlarms = processAlarms;
    _deviceConnected = deviceConnected;
    _deviceDisconnected = deviceDisconnected;
    
    _variable[0] = '\0';
    _value[0]    = '\0';
        
    
    _timeServerAddress = IPAddress(64,90,182,55);  // New York City, NY NTP Server
    _startTime = 0;
    _sendNtpRequest=false;
    _fireAlarmDelay = 0;
    
	this->inizializeAlarms();
}
#endif 


IOSController::IOSController(EthernetServer *server, 
                             void (*doWork)(void), 
                             void (*doSync)(char *variable),
                             void (*processIncomingMessages)(char *variable, char *value),
                             void (*processOutgoingMessages)(void),
                             void (*deviceConnected)(void),
							 void (*deviceDisconnected)(void)
                             )
{
	_var = true;
    _idx = 0;
    _server = server;
    _doWork = doWork;
    _doSync = doSync;
    _processIncomingMessages = processIncomingMessages;
    _processOutgoingMessages = processOutgoingMessages;
    _deviceConnected = deviceConnected;
    _deviceDisconnected = deviceDisconnected;
    
    _variable[0] = '\0';
    _value[0]    = '\0';
}                             

void IOSController::loop() {
	this->loop(500);
}

void IOSController::loop(unsigned long _delay) {
  	
#ifdef ALARMS_SUPPORT  	
  	if( (millis()/1000<20 && _startTime==0) || _sendNtpRequest) {
  	
	  	this->syncTime();
  	}
  	
  	if ( _udp.parsePacket() ) {  
  	
  		this->readTime();
  	}
  	
 	if (_processAlarms != NULL) {
		this->checkAndFireAlarms(ALARMCHECKDELAY);
    }
#endif  	
  	
 	_doWork();
 	
	_client = _server->available();
    
  	if (_client) {

    	// Client connected
            
        if (_deviceConnected != NULL) {
        	_deviceConnected();
        	
        	// _sendNtpRequest = true;  // Sync Time
		}
        
    	while(_client.connected()) {
            
            // Read incoming messages if any
            this->readVariable();
            
            if (strcmp(_variable,"Sync") == 0 && strlen(_value)>0) {
                
                // Process sync messages for the variable _value
                _doSync(_value);
            }
            else {
            
#ifdef ALARMS_SUPPORT             	
            	// Manages Alarm creation and update requests
           
            	char id[8];
            	unsigned long time;
            	bool repeat;
            
            	if (strcmp(_variable,"$AlarmId$") == 0 && strlen(_value)>0) {
            		strcpy(id,_value);
            		
            	} else if (strcmp(_variable,"$AlarmT$") == 0 && strlen(_value)>0) {
            		time=atol(_value);
            	}
            	else if (strcmp(_variable,"$AlarmR$") == 0 && strlen(_value)>0) {

					if (time == 0)
						this->removeAlarm(id);
					else
            			this->createUpdateAlarm(id,time,atoi(_value));    
            			
            		#ifdef DEBUG
						this->dumpAlarms();
					#endif      		 
            	}
            	else 
#endif            	
            	if (strlen(_variable)>0 && strlen(_value)>0) {
                
    	            // Process incoming messages
        	        _processIncomingMessages(_variable,_value);
            	} 
            }
            
#ifdef ALARMS_SUPPORT             
            // Check and Fire Alarms
            if (_processAlarms != NULL) {
				this->checkAndFireAlarms(ALARMCHECKDELAY_CONNECTED);
            }
#endif
            
            // Write outgoing messages
            _processOutgoingMessages();
            
#ifdef ALARMS_SUPPORT             
            // Sync local time with NTP Server
            if(_sendNtpRequest) {
  	
	  			this->syncTime();
  			}
  	
		  	if ( _udp.parsePacket() ) {  
  	
  				this->readTime();
  			}
#endif
  			            
            _doWork();
            
            delay(_delay);
        }
        
        // Client disconnected
        _client = NULL;
        
    	if (_deviceDisconnected != NULL)
        	_deviceDisconnected();

        //Serial.println();
        //Serial.println("disconnecting.");
        _client.stop();
    }
    
}

void IOSController::readVariable(void) {
    
	int c=0;

	_variable[0]='\0'; 
	_value[0]='\0';
    
	while (_client.available()) {
        
        char c = _client.read();
        
        if (isprint (c)) {
            
            if ((char)c == '=') {
                
                _variable[_idx]='\0'; 
                _var = false; 
                _idx = 0;
            }
            else {
                
                if ((char)c == '#') {
                    
                    _value[_idx]='\0'; 
                    _var = true; 
                    _idx = 0; 
                    return;
                }
                else {
                    
                    if (_var) {
                        
                        if(_idx==VARIABLELEN) 
	                        _variable[_idx] = '\0';
	                        else
                        	_variable[_idx++] = c;
                    }
                    else {
                        
                        if(_idx==VALUELEN)
                        	_value[_idx] = '\0';
                        	else
                        	_value[_idx++] = c;
                    }
                }
            }
        }
    }
}


void IOSController::writeMessage(char *variable, float value)
{
    char buffer[VARIABLELEN+VALUELEN+3];
    
    if (_client == NULL)
        return;
    
    long temp1 = (value - (long)value) * 1000;
    snprintf(buffer,VARIABLELEN+VALUELEN+3, "%s=%0ld.%ld#", variable, (long)value, temp1);
    
    _client.write((const uint8_t *)buffer, strlen(buffer)*sizeof(char));
}

void IOSController::writeTxtMessage(char *variable, char *value) 
{
//Serial.println("Inizio Inizio scrittura");

    if (_client == NULL)
        return;

//Serial.println("Inizio scrittura");

	int i = 0;
    while(variable[i] != '\0') 
    {
        _client.write(variable[i++]);
    }
    
    _client.write('=');
    
    i = 0;
    while(value[i] != '\0') 
    {
        _client.write(value[i++]);
    }
    
    _client.write('#');
//Serial.println("Fine scrittura");
}

#ifdef SD_SUPPORT
void IOSController::sendFileList(void) 
{
 	File root = SD.open("/");
 	root.rewindDirectory();
    
    File entry =  root.openNextFile();
        
    while(entry) {
    
      	if(!entry.isDirectory())
        	this->writeTxtMessage("SD",entry.name());

		entry.close();
      	entry =  root.openNextFile();
    }
    
    root.close();
    
    this->writeTxtMessage("SD","$EFL$");
}

void IOSController::sendFile(char *fileName) {

	this->writeTxtMessage("SD","$C$");
	
	File dataFile = SD.open(fileName,FILE_READ);
	
	if (dataFile) {
	
		char buffer[64];
		int idx = -1;
	
		while(dataFile.available()) {
		
			char b = dataFile.read();
			idx++;
			
			if (idx == 64) {
				buffer[64] = '\0';
				_client.print(buffer);
				idx = 0;
			}
			buffer[idx]=b;
			//Serial.print(b);
		}
		
		buffer[idx] = '\0';
		_client.print(buffer);
		
		dataFile.close();
		
		this->writeTxtMessage("SD","$E$");
	}	
}
#endif

void IOSController::temporaryDigitalWrite(uint8_t pin, uint8_t value, unsigned long ms) {

	int previousValue = digitalRead(pin);

    digitalWrite(pin, value);
    delay(ms);
    digitalWrite(pin, previousValue);
}


// Time Management 

#ifdef ALARMS_SUPPORT 
void IOSController::setNTPServerAddress(IPAddress address) {

	_timeServerAddress = address;
}

void IOSController::syncTime() {

	// Send Request to NTP Server	

	_sendNtpRequest = false;
  		
  	_udp.begin(8888); // Local Port to listen for UDP packets
  		
  	this->sendNTPpacket(_timeServerAddress, _udp);

#ifdef DEBUG
  	Serial.print("NNP Request Sent to address ");
  	Serial.println(_timeServerAddress);
#endif  	
}

void IOSController::readTime() {

	// Packet Received from NTP Server
    _udp.read(_packetBuffer,48);  // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

	unsigned long highWord = word(_packetBuffer[40], _packetBuffer[41]);
    unsigned long lowWord = word(_packetBuffer[42], _packetBuffer[43]);  
    	
	// combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):    	
    unsigned long secsSince1900 = highWord << 16 | lowWord;  

	// now convert NTP time into everyday time:
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;     
    // subtract seventy years to get Unix time:
    _startTime = secsSince1900 - seventyYears;  
    	
    // subtract current millis to synch with time in Arduino
    _startTime -= millis()/1000;
    	
#ifdef DEBUG
  	Serial.println("NNP Respose");
  	this->printTime(_startTime);
#endif  	
    	
    
}


// send an NTP request to the time server at the given address 
unsigned long IOSController::sendNTPpacket(IPAddress& address, EthernetUDP udp) {
  // set all bytes in the buffer to 0
  memset(_packetBuffer, 0, 48); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  _packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  _packetBuffer[1] = 0;     // Stratum, or type of clock
  _packetBuffer[2] = 6;     // Polling Interval
  _packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  _packetBuffer[12]  = 49; 
  _packetBuffer[13]  = 0x4E;
  _packetBuffer[14]  = 49;
  _packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(_packetBuffer,48);
  udp.endPacket(); 
}

void IOSController::breakTime(unsigned long time, int *seconds, int *minutes, int *hours, int *Wday, long *Year, int *Month, int *Day) {
  // break the given time_t into time components
  // this is a more compact version of the C library localtime function
  // note that year is offset from 1970 !!!

  unsigned long year;
  uint8_t month, monthLength;
  unsigned long days;

  *seconds = time % 60;
  time /= 60; // now it is minutes
  *minutes = time % 60;
  time /= 60; // now it is hours
  *hours = time % 24;
  time /= 24; // now it is days
  *Wday = ((time + 4) % 7) + 1;  // Sunday is day 1 

  year = 1970;  
  days = 0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
  }
  *Year = year; // year is offset from 1970 

  days -= LEAP_YEAR(year) ? 366 : 365;
  time  -= days; // now it is days in this year, starting at 0

  days=0;
  month=0;
  monthLength=0;
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } 
      else {
        monthLength=28;
      }
    } 
    else {
      monthLength = monthDays[month];
    }

    if (time >= monthLength) {
      time -= monthLength;
    } 
    else {
      break;
    }
  }
  *Month = month + 1;  // jan is month 1  
  *Day = time + 1;     // day of month
}


#ifdef DEBUG
void IOSController::printTime(unsigned long time) {

    	int seconds;
   		int minutes;
   		int hours;
   		int Wday;
   		long Year;
   		int Month;
   		int Day;
		
		this->breakTime(time, &seconds, &minutes, &hours, &Wday, &Year, &Month, &Day);

	   	Serial.print(Day);
	   	Serial.print("/");
	   	Serial.print(Month);
	   	Serial.print("/");
	   	Serial.print(Year);
	   	Serial.print(" ");
	   	Serial.print(hours);
	   	Serial.print(":");
	   	Serial.print(minutes);
	   	Serial.print(":");
	   	Serial.println(seconds);
}
#endif

void IOSController::createUpdateAlarm(char *id, unsigned long time, bool repeat) {

	char lid[12];
	
	lid[0] = 'A';
	strcpy(&lid[1],id);

	// Update

	for(int i=0; i<5; i++) {
		
		alarm a;
		
		eeprom_read_block((void*)&a, (void*)(i*sizeof(a)), sizeof(a));
		
		if (strcmp(a.id,lid) == 0) {
				a.time = time;
				a.repeat = repeat;
				
				eeprom_write_block((const void*)&a, (void*)(i*sizeof(a)), sizeof(a));
				
				return;
		}		
	}

	// Create

	for(int i=0; i<5; i++) {
	
		alarm a;
		
		eeprom_read_block((void*)&a, (void*)(i*sizeof(a)), sizeof(a));
	
		if(a.id[1]=='\0') {
		
			strcpy(a.id,lid);
			a.time = time;
			a.repeat = repeat;
		
			eeprom_write_block((const void*)&a, (void*)(i*sizeof(a)), sizeof(a));
			
			return;
		}
	}
}

void IOSController::removeAlarm(char *id) {

	char lid[12];
	
	lid[0] = 'A';
	strcpy(&lid[1],id);

	for(int i=0; i<5; i++) {
	
		alarm a;
		
		eeprom_read_block((void*)&a, (void*)(i*sizeof(a)), sizeof(a));
	
		if(strcmp(a.id,lid) == 0) {
		
			a.id[1]='\0';
			a.time = 0;
	        a.repeat = 0;
			
			eeprom_write_block((const void*)&a, (void*)(i*sizeof(a)), sizeof(a));
		}
	}
}

void IOSController::inizializeAlarms() {

	for(int i=0; i<5; i++) {
	
		alarm a;
		
		eeprom_read_block((void*)&a, (void*)(i*sizeof(a)), sizeof(a));
	
		if(a.id[0] != 'A') {
		
			a.id[0]='A';
			a.id[1]='\0';
			a.time=0;
			a.repeat = 0;
			
			eeprom_write_block((const void*)&a, (void*)(i*sizeof(a)), sizeof(a));
		}
	}
}

#ifdef DEBUG
void IOSController::dumpAlarms() {

	Serial.println("\t----Dump Alarms -----"); 
	
	for(int i=0;i<5; i++) {

		alarm al;
					
		eeprom_read_block((void*)&al, (void*)(i*sizeof(al)), sizeof(al));

		Serial.print("\t");
    	Serial.print(al.id); 
    	Serial.print(" "); 
    	Serial.print(al.time);
    	Serial.print(" ");
    	Serial.println(al.repeat);
	}
}
#endif

void IOSController::checkAndFireAlarms(unsigned long delay) {

	if (_fireAlarmDelay < delay) {
		_fireAlarmDelay++;
    }
	else {
    	_fireAlarmDelay=0;

		unsigned long now = _startTime + millis()/1000;

#ifdef DEBUG
		Serial.print("checkAndFireAlarms ");
	    this->printTime(now);
	    this->dumpAlarms();
#endif

	    for(int i=0; i<5; i++) {

			alarm a;

			eeprom_read_block((void*)&a, (void*)(i*sizeof(a)), sizeof(a));

	    	if(a.id[1]!='\0' && a.time<now) {

#ifdef DEBUG
				Serial.println(a.id);
#endif				
				// First character of id is A and has to be removed
            	_processAlarms(&a.id[1]);

	    		if(a.repeat) {
	    	
    	    		a.time += 86400; // Scheduled again tomorrow
    	    		
#ifdef DEBUG
					Serial.print("Alarm rescheduled at ");
	            	this->printTime(a.time);
#endif	            	
            	}
	        	else {
            		//     Alarm removed
            	
	            	a.id[1]='\0';
	            	a.time = 0;
	            	a.repeat = 0;
            	}

				eeprom_write_block((const void*)&a, (void*)(i*sizeof(a)), sizeof(a));
#ifdef DEBUG
				this->dumpAlarms();
#endif        		 
			}
    	}
	}
}
#endif