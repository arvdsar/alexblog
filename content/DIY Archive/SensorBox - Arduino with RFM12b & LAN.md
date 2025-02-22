---
title: "SensorBox - Arduino with RFM12b & LAN"
date: "2013-02-22"
author: Alexander
---

The Sensor Box is a central node that receives data from several (up to 29) wireless sensor nodes using RFM12b transceivers. This data is uploaded once a minute (or less) to an Internet of Things service. In my current version, I upload data to open.sen.se and wunderground.com. Read my [blog post](#) about why I created the Sensor Box.

### The sensor box components are:
- Arduino Mega 2560
- Ethernet Shield
- RFM12b 868MHz transceiver
- RGB Status LED

The Sensor Box uses the RFM12b transceiver to wirelessly receive sensor data and is connected to the SPI bus. In my case, I chose to use 868 MHz, but 434 MHz and 915 MHz modules are also available. The Sensor Box is continuously listening on the frequency for incoming data. It collects the received data and uploads it to open.sen.se once per minute. The Sensor Box has an Ethernet shield attached.

The sensors are based on the TinyTX code by Nathan Chantrell. I've made some minor modifications to the source code, specifically related to the data structure being sent. You should read the TinyTX documentation and you should be able to build the sensors yourself. The TinyTX modules are based on the small microcontroller, the Attiny84. Check out this page to understand how to program them, and use Google too. ;-)

The sensors could be anything. Currently, I use DHT22 temperature and humidity sensors, which run on two AA batteries and are scattered around the house. I've also built an outdoor 'Stevenson screen' to protect one outdoor sensor from direct sunlight and rain. The data from this specific sensor is not only uploaded to open.sen.se but also to wunderground.com as personal weather station data. I still need to paint it white someday. To make it even more exciting, the wunderground data can be imported into the [pvoutput.org](http://pvoutput.org) website, which I use for monitoring my solar panel power generation. I used one of the standard weather stations before, but now I have my own. ;-)

### Future sensor ideas:
- Mailbox opened
- Monitor if somebody passes a line (in our garden)
- Central Heating water temperature
- Temperature inside the fridge
- Light sensors

Just building sensors one by one. ;-)

You can download the source code for the SensorBox. You will need to register on open.sen.se and wunderground.com if you want to upload data to these services.

The latest version is v0.16 and uses a new `datastructure.h` (included in the download).

![[attachments/SensorBox_OpenSense_v016_public.zip]]

I’ve also attached one example of the TinyTX code I use for a DHT22 sensor. Check out the TinyTX website for the most recent updates. Remember to copy `datastructure.h` into a folder in your Arduino library folder to ensure consistency between all sources.

The latest version is v0.2, which works with SensorBox v0.16. You can modify it to suit your needs.

![[attachments/TinyTX_DHT22_v02.zip]]

### My specific changes to the code:
Within the TinyTX code, a `struct` is defined. That `struct` is sent using the RFM12b modules from the sensor node to the SensorBox. The RFM12b does not know what you send, but if you send a bunch of bits and bytes in a `struct` format and put them in the same structure when you receive them, it’s like transferring the struct.

I use several structs. I have a struct for parameters from my solar power monitor, a struct for my Raspberry Pi which sends sun- and moonrise/set times, a struct for the temperature sensors, and more. All these structs are defined in `DataStructure.h`, which you should copy into a folder called `DataStructure` in your `/libraries` folder of the Arduino IDE.

Within the code of TinyTX or the SensorBox, I only instantiate the struct I need for each device. Since I use the `DataStructure.h` file in the library folder, I'm always certain that all my code uses the same structs. Each struct has a field indicating which struct it is, so the SensorBox checks this field first and then decides where to copy the data.

### More details:
I had some RGB LEDs left, so I connected one to the SensorBox on the following pins:

- **Red** = Pin 13 with resistor
- **Green** = Pin 12 with resistor
- **Blue** = Pin 11 with resistor

The RGB LED acts as a status indicator:
- **White** - Device boot
- **Magenta** - NTP Time request
- **Yellow** - Idle, waiting for data
- **Blue** - Incoming sensor data
- **Green** - Uploading data to Open.sen.se
- **Cyan** - Uploading data to Wunderground.com
- **Red** - Cannot connect to Wunderground.com

The RFM12b is connected to pins 50, 51, 52, and 53 of the Arduino Mega. The IRQ line is attached to pin 2.

Starting from version 0.16, I've implemented the use of the Arduino EEPROM to store the FeedIDs (or channel IDs) used to upload data to Open.sen.se. Using telnet commands, you can set the FeedIDs of each value received from the sensors. The SensorBox does not need to know what the value received means (it could be temperature, humidity, water level, etc.). It will simply upload the value to Open.sen.se, where you can give it a name and unit, and it becomes real information.

- `sensoradd,3,1232,1232,5324,2341,6364,5,` - Adds a sensor config for NodeID 3 with values 1 to 5, uploading the data every 5 minutes. Make sure to close the line with a comma!
- `sensorcount,4,` - Tells the SensorBox that you have 4 sensors.
- `sensorshow,3,` - Shows info for NodeID 3.
- `sensorlist` - Shows contents of (a part of) the EEPROM.
