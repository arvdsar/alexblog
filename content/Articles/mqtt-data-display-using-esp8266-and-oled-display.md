---
title: "MQTT Data display using ESP8266 and OLED display"
date: "2015-07-20"
categories: 
  - "arduino"
  - "esp8266"
tags: 
  - "esp8266"
  - "lua"
  - "mqtt"
  - "nodemcu"
  - "nodered"
  - "oled"
coverImage: "IMG_4035-e1437418587142.jpg"
---

![[attachments/IMG_4035-e1437418587142.jpg]]
Finally I made some time to play a couple of hours with a new type of microcontroller that offers a lot of possibilities. Especially for Internet of Things purposes!

I'm talking about the ESP8266 which, at the time of introduction, was used often as a very cheap WIFI adapter for i.e. Arduino's. The ESP8266 costs a couple of dollars. Meanwhile the community discovered that the chip contains a capable microcontroller with GPIO ports and it has WIFI onboard. Beside cheap it's very small too! I'm not going to write a lot about what the ESP8266 is. You can find enough information using Google. I will write about what I've build with the device.

It's been a while (2012/2013) since I've developed the Wireless LCD Display, Domotica Gateway, Energy Monitor, and so on. I made some changes lately by using [Node-Red](http://nodered.org) and [MQTT](http://mqtt.org) for controlling devices and connecting things together.  You should check [TheThingBox.io](http://thethingbox.io) which offers a ready to go Raspberry Pi image  if you want to start playing with Node-Red and/or MQTT.

This post is about an ESP8266 (Type ESP12) with a 0.96" OLED Display (with SSD1306 driver chip) receiving data via WiFi. The data is exchanged using MQTT. This application subscribes to multiple MQTT Topics and displays the data on the OLED screen. The ESP8266 is using [NodeMCU](http://nodemcu.com) firmware. (You can buy an ESP8266 with NodeMCU and FTDI on a board for less than 10 dollar on Ebay!! The Oled is available on Ebay too, search for "Oled 1306" and you'll find something). The pins are defined in the sourcecode which you can download below.

I found a big part of the code in [this post](http://www.esp8266.com/viewtopic.php?p=13247#p12289) written by Mikejstb which I modified to how I wanted to use it.

Download the sourcecode below. Use Esplorer to upload the content as init.lua. Before trying this code, connect your NodeMCU ESP8266 to WiFi first.

Below download my init.lua (remove the .txt extension)

![[attachments/init.lua.txt]]

Check the following useful links to start with:

- [ESPlorer](http://esp8266.ru/esplorer/)
- [Getting Started With The ESPlorer IDE](http://esp8266.ru/download/esp8266-doc/Getting%20Started%20with%20the%20ESPlorer%20IDE%20-%20Rui%20Santos.pdf) (Download free PDF)
- [Home Automation Using ESP8266](http://randomnerdtutorials.com/home-automation-using-esp8266/)
