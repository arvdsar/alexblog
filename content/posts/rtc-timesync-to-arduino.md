---
title: "RTC timesync to Arduino"
date: "2013-02-18"
categories: 
  - "arduino"
  - "tech"
tags: 
  - "arduino"
  - "domotica"
  - "raspberry-pi"
  - "timesync"
---

I've added some new code to the wireless LCD Display and my Raspberry PI to set the time on the wireless LCD display correctly and regularly.

The wireless LCD Display has a DS1307 RTC connected but it is not the most accurate so time will shift after a while. The Arduino time library has an example on how to set the time using the serial port (usb) of the Arduino. That is to much hassle to do each time.

I use the Raspberry Pi with a Python script to calculate the UNIX time and send it over LAN to my Domotica Gateway. The Domotica Gateway can communicate over wireless with the wireless LCD Display. The UNIX time string is send to the wireless LCD display which will update the time on the DS1307 RTC. The python script runs every hour using the crontab. (could be much less but it won't hurt)

Although my setup is very specific, you might find the python code useful. \[fusion\_builder\_container hundred\_percent="yes" overflow="visible"\]\[fusion\_builder\_row\]\[fusion\_builder\_column type="1\_1" background\_position="left top" background\_color="" border\_size="" border\_color="" border\_style="solid" spacing="yes" background\_image="" background\_repeat="no-repeat" padding="" margin\_top="0px" margin\_bottom="0px" class="" id="" animation\_type="" animation\_speed="0.3" animation\_direction="left" hide\_on\_mobile="no" center\_content="no" min\_height="none"\]\[wpdm\_file id=3\]

I use [THIS library](http://playground.arduino.cc/Code/Time) for time on the wireless LCD display. The specific Arduino code to update the RTC and set the time: RTC.set(inData\_8.time);  //inData\_8.time is the value send by the domotica gateway _setTime(inData\_8.time);_

 \[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
