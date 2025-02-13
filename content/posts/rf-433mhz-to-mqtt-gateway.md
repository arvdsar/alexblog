---
title: "RF 433Mhz to MQTT Gateway"
date: "2016-01-02"
categories: 
  - "arduino"
  - "tech"
tags: 
  - "arduino"
  - "domotica"
  - "raspberry-pi"
---

I've upgraded my domotica setup with a [Philips Hue](http://www.meethue.com). Before I switched the lights using a remote control or via Node-Red and using the cheap 433 Mhz wall outlet switches of Elro, Klik Aan/Klik Uit, Action, and so on. Since the install of the Hue I was missing the remote control to easily switch the lights. Every time I had to get my phone to control the lights.

Today I created a simple 433 Mhz receiver gateway that receives the commands or codes from the cheap remote control that belongs together with the cheap wall outlets which I don't (at least not for my home lighting) anymore. The gateway receives the codes and publishes those in a MQTT Topic. [Node-Red](http://thethingbox.io) is reading the topic and will perform actions based on the codes. So now I can use that cheap remote controller again and trigger predefined tasks within Node-Red. Node-Red controls all of my domotica at home.

You need an Arduino Uno (or Mega), an W5100 Ethernet shield and a cheap [RF433 Receiver](https://www.google.nl/search?q=xymk5v) which you can find on ebay for a dollar or so. Connect the receiver data pin to either Digital Pin 2 (INT 0) or Digital Pin 3 (INT 1) on the Arduino and of course the VCC to 5v and GND to... GND!.

RemoteReceiver::init(1, 3, showCode); // The first parameter is the INTerrupt. 1 means Pin3, 0 means Pin 2.

Download the source and change your IP, Username and Password related to the MQTT Broker. You also need the [RemoteSwitch](https://github.com/hjgode/homewatch/tree/master/arduino/libraries/RemoteSwitch) and [PubSubClient](https://github.com/knolleary/pubsubclient) library for Arduino (running on 1.6.5)

\[fusion\_builder\_container hundred\_percent="yes" overflow="visible"\]\[fusion\_builder\_row\]\[fusion\_builder\_column type="1\_1" background\_position="left top" background\_color="" border\_size="" border\_color="" border\_style="solid" spacing="yes" background\_image="" background\_repeat="no-repeat" padding="" margin\_top="0px" margin\_bottom="0px" class="" id="" animation\_type="" animation\_speed="0.3" animation\_direction="left" hide\_on\_mobile="no" center\_content="no" min\_height="none"\]\[wpdm\_package id='1864'\]

Have Fun!\[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
