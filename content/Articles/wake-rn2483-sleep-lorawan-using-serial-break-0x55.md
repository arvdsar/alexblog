---
title: Wake RN2483 from Sleep (LoraWAN) using Serial Break and 0x55
date: 2017-04-02
categories:
  - arduino
  - lora
  - tech
tags:
  - lorawan
---

I finally found some time again to build some LoraWAN Arduino toys for TheThingsNetwork.

Basically it's just a temperature sensor measuring outdoor water temperature and sending it once in a couple of hours via TTN to my Node-Red install.

I've used the [RN2483 library](https://github.com/jpmeijers/RN2483-Arduino-Library) from JP Meijers which works great.

I use an Arduino Pro Mini 3.3volt with the RN2483 and they will be powered by a 18650 Battery. I'll probably have it solar charged with a small 5V solarpanel too. To save energy the Arduino and the RN2483 will put to sleep after sending the temperature. Energy consumption is in sleep about 1.55 mA

You can put the RN2482 to sleep by using this statement and it will sleep for 20.000.000 milliseconds myLora.sleep(20000000);

The Arduino can be put to sleep for max 8 seconds by using the LowPower library and next statement: LowPower.powerDown(SLEEP\_8S, ADC\_OFF, BOD\_OFF); Using a while loop and a counter you can put it to sleep every 8 seconds again until the total sleep time has expired.

It's quite 'hard' to wake the RN2483 and Arduino at the same time because the timing is not perfect and you'll probably wake your RN2483 too early which will use power until the Arduino wakes up too.

The RN2483 manual says you can wake the RN2483 from sleep by sending a Serial Break and 0x55 character. This is working fine with the software serial library. I've not tested it with the hardware serial but I guess it will work too.

//Wake the RN2483 from its long sleep by sending a serial break and 0x55 character. A Serial break is just sending a bunch of 0's. (which is the same as pulling the TX pin to HIGH for a couple of milliseconds).

```
//Pin 11 is the TX pin of SoftwareSerial:
SoftwareSerial mySerial(10, 11); // RX, TX

void sendbreak()  
{  
digitalWrite(11, LOW); // Set pin to serial “idle” state.  
//endSerial(); //necessary in case of hard-serial  
pinMode(11, OUTPUT);  
digitalWrite(11, HIGH); // Send BREAK  
delay(20); // for 10ms  
mySerial.begin(9600);  
mySerial.write(0x55);  
//serial.Begin(BITRATE); // back to serial mode (hardware serial)  
}
```

I decided to put the RN2483 to sleep for very long (20.000.000 milliseconds) and wake it using the sendbreak() function from the Arduino. Now the RN2483 will be awake only when the Arduino is too, saving some energy.

My main loop is:

```
void loop()  
{  
//Do something like sending data 😉  
myLora.sleep(20000000); //Put the RN2483 to sleep for x – milliseconds.  
while(sleepcounter < 225){ //not very accurate, but 225 x 8 Seconds sleep time = 30-40 min sleeping  
LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); // put the Arduino to sleep for x-seconds.  
sleepcounter++;  
}  
sleepcounter = 0;  
sendbreak(); // wake the RN2483  
myLora.autobaud(); //seems to be necessary to get the RN2482 running properly  
}
```
