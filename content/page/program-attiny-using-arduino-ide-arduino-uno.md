---
title: "Program Attiny using Arduino IDE & Arduino UNO"
date: "2012-12-26"
author: Alexander

---

There are many articles written about Programmingen Attiny using Arduino IDE &amp; Arduino UNO. My post is more to keep an overview for my own reference and hopefully you can benefit from it too!
The Attiny is a small version of the microcontrollers used in the Arduino's which are Atmega's. The Attiny is still very powerful but has a limited amount of pins therefore you are limited in the number of in- and outputs. &nbsp;They are limited in size and in power consumption, so ideal to use them in situations where you rely on batteries.
You can program the Attiny's using C, just like you could with the Atmega's but why not use the Arduino IDE which makes programming those devices simpler.First you need a programmer because the Attiny does not have a USB connection ;-). You can use an Arduino Uno for this and that is what I've done. (buy one on ebay for about 10-15 euro's).
In my example I will use the Attiny84 which has 14 pins. Hook it up to the Arduino Uno by connecting the pins below using some wires and a breadboard. You can find the appropriate pins of other Attiny's in the datasheets or check out this link to a collection of reference sheets. Also put a 10uF elco (electrolytic capacitor) over reset and Gnd on the Arduino to prevent it from resetting (do it after you've loaded the arduinoISP sketch below).
Attiny 84Arduino Uno&nbsp;VCC = 15VoltReset = 4Digital 10MOSI = 7Digital 11MISO = 8Digital 12SCK = 9Digital 13GND = 14GND
Before you can use the Arduino Uno as a programmer you have to load a sketch onto the Arduino: ArduinoISP which is in File, Examples, ArduinoISP (just in the Arduino menu). Load it and program your Arduino as usually. Now you have a programmer.
The Arduino IDE does not support the Attiny's by default, you have to load the attiny core into the Arduino IDE. I've used the core on this page. Extract it and copy to a folder 'hardware' &nbsp;under your regular sketch directory. After a restart of the Arduino IDE you will find new cores in the menu under 'Extra, Boards'. You'll notice that there are several clockspeeds mentioned with the boards. I have not completely figured it out but for now I know this:
Select the Attiny you have and the clockspeed you want to use. Now select in menu 'Extra, &nbsp;Programmer, Arduino as ISP', choose the right serial port also in the extra menu and click Bootloader. It does not really 'burn' a bootloader on the Attiny but it will set some fuses to configure the Attiny chip. Now you are ready to go.
Write some code (or use the blink example, do set the ledpin in source code to 0 instead of 13. There is no digital pin 13 on the attiny84), compile and 'upload using programmer' to the attiny.&nbsp;I got the following error twice, but it seems to be normal. It just works ;-) "avrdude: please define PAGEL and BS2 signals in the configuration file for part ATtiny84".
First it took me a while to get it working, caused by bad connections on the breadboard. So don't doubt the software, check you connections and settings!Also remember that if you have burned the bootloader (set the fuses) to 8Mhz, you should program the Attiny using the same speed. So if you want to switcht to 1 Mhz, select that speed, burn bootloader and then program the sketch. Otherwise it won't work properly.
