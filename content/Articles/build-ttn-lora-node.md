---
title: "Build (TTN) LoRaWan Node"
date: "2016-02-25"
categories: 
  - "arduino"
  - "lora"
tags: 
  - "arduino"
  - "lora"
  - "lorawan"
  - "node"
  - "sensor"
  - "ttn"
coverImage: "2016-01-18T22-31-19.613Z-RN2483_V2.png.2560x2560_q85.png"
---

Many people want to build a node to test their own TTN (The Things Network) gateway and build new use cases. It's not that hard to build a node when you know which components to buy. With this post I've collected some information which might save you time in getting the things together.

Building a node is the easiest using a RN2483 module which can be controlled using text commands via a serial interface.

Shopping list:

- [Breakout board](https://www.tindie.com/products/DrAzzy/rn2483-breakout-bare-board/) which makes prototyping easy with the RN2483.
- Microchip RN2483. Use google to find a supplier and buy the appropriate frequency.
- [Antenna Connector](http://r.ebay.com/6Q8rfb) (it's a link to ebay).  
    You slide this connector on the print so the print should fit between the bottom and middle pins. You solder all 5 pins to the print.
- [868 Mhz Antenna](http://r.ebay.com/lSrO7J) (ebay link).
- [bigger Antenna](http://r.ebay.com/Ij5Rea) (ebay link, not yet received)

Next, the RN2483 is 3.3volts. It seems you can add a voltage regulator to the board. I didn't tried that yet. I just connected VCC to 3.3 volt output pin on my Arduino Uno. I used a [3.3Volt Logic Level module](http://r.ebay.com/oUeyiZ) to connect the 5 volt output pins from the Arduino savely to the RN2483.

You can find a lot of info on the forum of TheThingsNetwork in the [TTN UNO BETA](http://forum.thethingsnetwork.org/t/ttn-uno-beta-release-documentation/290/13) topic.

There is an [Arduino Library available on GitHub](https://github.com/jpmeijers/ttnmapperarduino). An example sketch is included and you can find the configuration parameters in the rn2483.cpp file. This file contains the serial commands send to the RN2483 module. Check the [RN2483 LoRa Technology Module Command Reference User's Guide](http://ww1.microchip.com/downloads/en/DeviceDoc/40001784E.pdf) for explanation of these commands.

With the above post I hope to save you some time searching for the parts needed so you can start building your own instead of searching through many forum posts.

HAVE FUN!!
