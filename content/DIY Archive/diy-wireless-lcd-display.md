---
title: "Arduino Wireless LCD Display"
date: "2012-12-03"
author: Alexander
---

The data from the energy monitor Arduino is published online with PVOutput.org, but you have to be online to view the data. I wanted to see the data in our living room without using a PC or smartphone. So, I built an Arduino-based wireless LCD display that can send and receive data using the RFM12b 868 MHz transceiver.

Unfortunately, you need a power supply, so at least one wire is necessary.   
(In my previous versions, I used cheap 434 MHz receivers with the Virtual Wire library. I've upgraded my setup to all RFM12b transceivers, so I can send & receive data and use the Jeelib library. An additional benefit is that I can easily use an ATtiny84 for sensors like TinyTX.)

### The Wireless LCD Display Uses the Following Components:
- Arduino Nano (Atmega328)
- 20x4 LCD Display
- 868 MHz RFM12b Transceiver
- DS1307 RTC (Real-Time Clock)
- DHT22 Temperature & Humidity Sensor
- Power Supply (7-12 volts)
- Photo frame as housing

Its main purpose is to display data that is received wirelessly over 868 MHz from the Domotica Gateway. The Domotica Gateway can forward data received over LAN, the Internet, or send data it has generated itself (e.g., switch statuses).

### Data Received Includes:
- Energy statistics like actual solar power, energy consumption, gas usage, energy import & export, etc. The data is sent over LAN from the Energy Monitor to the Domotica Gateway and then forwarded wirelessly over 868 MHz to the wireless LCD display.
- Sunrise, sunset, moonrise, and moonset times. Times are calculated on the Raspberry Pi, sent over LAN to the Domotica Gateway, and then forwarded over 868 MHz to the wireless LCD display.
- Switch status of garden lights (from Raspberry Pi) and indoor lights (on Domotica Gateway itself).
- UNIX timestamp to update the real-time clock periodically.
- Temperature and humidity from two TinyTX-based sensors.

To enhance the display, a DHT22 temperature and humidity sensor is attached. A real-time clock is also included to show the current date and time.

### Data Format:
The RF12 library from Jeelib can send up to 66 bytes. We can use a struct to define a collection of variables to send and receive. Have a look at the source code and read some manuals about the RF12 library. The struct contains all the data I want to display on the LCD. Data can be sent from several devices. Primarily, it is sent by the Domotica Gateway, but data can also be received from other devices using the RFM12b (e.g., one of my outdoor temperature sensors based on TinyTX).

### 868 MHz Transceiver:
Data is received using a cheap RFM12b 868 MHz transceiver. The library used is RF12 from Jeelib. The benefit of using the RFM12b is that it is a transceiver, capable of both sending and receiving data. Primarily, the display receives data from the Domotica Gateway, such as energy usage and the status of some lights. Since the Wireless LCD Display also contains a DHT22 temperature/humidity sensor, I've added code to send those values to my sensor box. Now, the Wireless LCD Display has become an additional sensor too! That's the benefit of being able to send data as well.

### DS1307 RTC:
The real-time clock module holds the time and date when no power supply is connected. In this post, I explain how I've implemented a time-sync mechanism with the Domotica box and the Raspberry Pi so that the time is synchronized periodically.

### DHT22:
For about $6, you get a calibrated temperature and humidity sensor. Search on eBay for it. The DHT11 is cheaper but less accurate. I tried it first, but switched it for a DHT22.

### Libraries Used:
Several libraries are used, available on the internet. See this page for the libraries used in my projects. Credits go to the people who created those libraries, as they save us loads of work! ;-)


![[attachments/Arduino Collection RFM12b - Febr 2013.zip]]
![[attachments/Libraries for collection febr 2013.zip]]

You will receive the whole package: Energy Meter, Domotica Gateway, SensorBox, and Wireless LCD Display, so all versions work together. I've packed all libraries as they are on my disk now. These might not be the most recent versions, but they should work with the sources. 

Unfortunately, the sources are not "monkey proof," so you'll need to dig into the code and change it to suit your situation and needs.
