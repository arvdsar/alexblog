---
title: "Sensor Box"
date: "2013-01-24"
categories: 
  - "gadgets"
  - "lifehacking-2"
  - "tech"
tags: 
  - "arduino"
  - "attiny"
  - "domotica"
  - "rf12"
  - "sensor"
  - "tinytx"
---

I've been working on replacing the 433Mhz cheap transmitters (send only) by the RFM12b 868 Mhz Transceivers (send & receive) by using the RF12 library from jeelib.

Things are working now, but it's quite a bunch of work to convert all devices ;-).

Also I'm very happy with the Attiny84 microcontrollers which allow some low power sensor nodes. Actually I have not made this up myself, I use the [TinyTX wireless sensors](http://nathan.chantrell.net/tinytx-wireless-sensor/). It's just putting stuff together en modify the data structures to adapt to my situation. Currently I have one TinyTX + DHT22 sensor running on 2 x AA batteries (3volts).

<!--more-->

Now the sensor is running, I wanted to do something with the data. I tried to add ThingSpeak.com to my domotica box to send the temperature and humidity to ThingSpeak.com every minute. Unfortunately, my domotica box is full of network connections to Raspberry Pi, Solar Monitor Arduino, PushingBox and a debug Telnet. So things didn't work out very well.

I've been thinking about connecting another Arduino Nano or Mega via i2c connection but it didn't feel right and became more and more complex. So back to the drawing board!

I had two goals with my TinyTX units.

1. Measure temperature, fire, light, open windows, and so on
2. Control something (RGB Leds, Sound, Heater)

The Domotica Box should remain the controlling unit that controls stuff, so option 2 belongs to the Domotica Box. Option 1 has two purposes. Control things based upon sensor data and publish sensordata online.

I came up with the following solution:

The Domotica Box receives sensor data and controls stuff but it does not get a connection to a 'Internet of Things'-service like Cosm.com or ThingSpeak.com.

The Sensor Box is a new Arduino Mega based device that has one goal: Receive data and send it to 'Internet of things'-service. Both devices can receive the data send by the sensors. Even when the Domotica Gateway sends data to the Wireless LCD Display (which contains Solar Power Generation, energy consumption and so on) this can be received by the Sensor Box and published.

I've created a prototype based upon the code from ThingSpeak.com and this works way better then when it was combined on the Domotica Box. Of course one would like to put everything on one device but I have to live with my programming limitations and now the Sensor Box can be used as single device without any relation to the Domotica Box.

Time to start building more and more sensors ;-).
