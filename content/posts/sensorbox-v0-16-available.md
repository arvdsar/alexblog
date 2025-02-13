---
title: "SensorBox v0.16 available"
date: "2013-04-07"
categories: 
  - "arduino"
  - "tech"
---

A new version of my SensorBox code for Arduino is available for [download](https://www.vdsar.net/sensorbox-page/ "DIY – SensorBox – Arduino with RFM12b & LAN"). Some of the improvements are:

- Optimized code. A loop is created to upload data of the TinyTX sensors to Open.Sen.Se
- ChannelID's are stored in EEPROM
- ChannelID's configurable via Telnet
- Watchdog timer

Use the code as an example to build your own. There are issues with the watchdog on Arduino Mega with the standard boot loader. Arduino IDE 1.0.4. contains a new bootloader that fixes the issues. (In case watchdog is triggered, the arduino will remain in a loop at boot.).
