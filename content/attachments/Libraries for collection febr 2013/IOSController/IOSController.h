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
 * Version: 1.5
 *
 * All rights reserved
 *
 */

#ifndef IOSController_h
#define IOSController_h

#define SD_SUPPORT        // uncomment to enable support for SD Widget
#define ALARMS_SUPPORT    // uncomment to enable support for Alarm Widget
//#define DEBUG           // uncomment to unable debugging - You should not need it !

#include <Ethernet.h>

#ifdef SD_SUPPORT
	#include <SD.h>
#endif 

#ifdef ALARMS_SUPPORT

typedef struct  {
	char 			id[12];  // First character of id is always A
	unsigned long 	time;
	bool			repeat;
} alarm;

#endif

#define VARIABLELEN 14
#define VALUELEN 14


class IOSController {

private:
char			_variable[VARIABLELEN+1];
char 	   		_value[VALUELEN+1];
bool	   		_var;
int       		_idx;
EthernetServer 	*_server;
EthernetClient  _client;

#ifdef ALARMS_SUPPORT
EthernetUDP 	_udp;
IPAddress 		_timeServerAddress;  // NTP Server Address
bool			_sendNtpRequest;
byte 			_packetBuffer[48]; 	// buffer to hold incoming and outgoing packets 
unsigned long   _fireAlarmDelay;
unsigned long	_startTime;
#endif
/**
Pointer to the function where to put code in place of loop()
**/
void (*_doWork)(void); 

/*
Pointer to the function where Switches, Knobs and Leds are syncronized
*/
void (*_doSync)(char *variable);

/*
Pointer to the function where incoming messages are processed
*
* variable
*
* value
*
*/
void (*_processIncomingMessages)(char *variable, char *value);

/*
Pointer to the function where outgoing messages are processed
*
*/
void (*_processOutgoingMessages)(void);

#ifdef ALARMS_SUPPORT
/*
Pointer to the function where alerts are processed
*
*/
void (*_processAlarms)(char *alarm);
#endif

/*
Pointer to the function called when a device connects to Arduino
*
*/
void (*_deviceConnected)(void);

/*
Pointer to the function called when a device disconnects from Arduino
*
*/
void (*_deviceDisconnected)(void);

void readVariable(void);

#ifdef ALARMS_SUPPORT

unsigned long sendNTPpacket(IPAddress& address, EthernetUDP udp);
void breakTime(unsigned long time, int *seconds, int *minutes, int *hours, int *Wday, long *Year, int *Month, int *Day);

void syncTime();
void readTime();

void inizializeAlarms();
void checkAndFireAlarms(unsigned long delay);
void createUpdateAlarm(char *id, unsigned long time, bool repeat);
void removeAlarm(char *id);

#ifdef DEBUG
	void dumpAlarms();
  	void printTime(unsigned long time);
#endif 

#endif

public:

#ifdef ALARMS_SUPPORT
	IOSController(EthernetServer *server, 
								  void (*doWork)(void), void (*doSync)(char *variable), 
								  void (*processIncomingMessages)(char *variable, char *value),
								  void (*processOutgoingMessages)(void),
								  void (*processAlarms)(char *alarm),
								  void (*deviceConnected)(void),
								  void (*deviceDisconnected)(void));
#endif

	IOSController(EthernetServer *server, 
								  void (*doWork)(void), void (*doSync)(char *variable), 
								  void (*processIncomingMessages)(char *variable, char *value),
								  void (*processOutgoingMessages)(void),
								  void (*deviceConnected)(void),
								  void (*deviceDisconnected)(void));
								  
								  
	void loop();
	void loop(unsigned long delay);
	void writeMessage(char *variable, float value);
	void writeTxtMessage(char *variable, char *value);
	
#ifdef SD_SUPPORT	
	void sendFileList(void);
	void sendFile(char *fileName);
#endif
	
	void temporaryDigitalWrite(uint8_t pin, uint8_t value, unsigned long ms);
	
	void setNTPServerAddress(IPAddress address);
};

#endif