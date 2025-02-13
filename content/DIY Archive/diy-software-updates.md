---
title: "Arduino - Software updates"
date: "2013-04-02"
categories: 
  - "arduino"
  - "tech"
tags: 
  - "arduino"
  - "domotica"
  - "pushingbox"
  - "software"
  - "wannahaves"
---

At the moment I'm still working to improve the DomoticaBox, SensorBox, Wireless LCD Display software. Once I have a new complete matching set that is suitable for download, I will update the links on this site again. Some improvements are:

- Watchdog to auto reset in case of lockups
- Use EEPROM for storing Open.Sen.Se feedID's for the SensorBox
- Optimized Sensorbox source code
-  DomoticaBox can receive commands via RFM12b (before it was only via Ethernet). Necessary for commands via touchpanel on TFT display
- Wunderground upload added to SensorBox

I'm also developing software to use 3.5" TFT Display with touchscreen wirelessly just like the Wireless LCD Display. It should become also compatible with a 7" TFT display.

There are some compatiblity issues with the RFM12b transceiver together with the touch panel on the TFT display. Should work but it doesn't. Also the RFM12b cannot be directly used with the Arduino Due or Raspberry Pi (yet). There is a board available based on the Attiny84 to interface with the RFM12b transceiver and the Raspberry Pi but I found the Attiny84 to limited for how I want to use it. Therefore I developed a prototype of an Atmega328p with a RFM12b that forward the data to and from the serial port. This solves three cases: compatible with the specific display shield, the Raspberry Pi and the new and fast Arduino Due.

I hope I can design a nice PCB for it so all things fit nicely. It's just a matter of time until that is ready.

Arduino has released version 1.0.4 of it's IDE. I found it to work properly once I modified the w5100.h file again for using the RFM12b together with ethernet shield (same modification as for the other 1.0.x versions. Additonally the Arduino Mega2560 bootloader has been updated to fix watchdog related issues and it was just in time for the watchdog in my boxes.

No promises, but I think new versions are ready for download by the end of april 2013.
