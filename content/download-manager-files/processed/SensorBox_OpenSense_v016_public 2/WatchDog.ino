byte busyState;
int busyCounter;

#define TIMEOUT 30 // * 2000ms = 1 minute


void SetupWatchdog()
{
    // set watchdog timeout to 4 seconds
    wdt_enable(WDTO_4S);
	// initialize counters
    busyCounter = 0;
    busyState = 0;
}

void busy(byte function)
{
    wdt_reset();
    if(function == 0)
      busyCounter = 0;
      
    if(busyState!=function)
    {
        busyState = function;
    }
}

// this is called every 5ms to keep the watchdog from resetting the board
void CheckWatchdog()
{
	// increment the counter as long as we are executing a function
  busyCounter++;
 
    // keep resetting the watchdog until busycounter gets really big
    // 30 * 2000ms  = 60 seconds of inactivity before a reset occurs
    // A .connect() function can take up to 15 seconds because of DNS
    // so a normal watchdog would not be long enough.
    if(busyCounter<TIMEOUT)
    {
          // reset watchdog counter  
          wdt_reset();        
    }
    else
    {

        RGBLed(red);      
        // wait for the reset to come
        while(1); 
    }
}

