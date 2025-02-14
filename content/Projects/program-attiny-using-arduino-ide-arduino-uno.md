---
title: "Program ATtiny using Arduino IDE & Arduino UNO"
date: "2012-12-26"
author: Alexander
---

There are many articles written about programming ATtiny using Arduino IDE & Arduino UNO. My post serves as an overview for my own reference, and hopefully, you can benefit from it too!

The ATtiny is a smaller version of the microcontrollers used in Arduinos, which are ATmega chips. The ATtiny is still very powerful but has a limited number of pins, meaning you are restricted in the number of inputs and outputs. They are small and have low power consumption, making them ideal for battery-powered applications.

You can program ATtinys using C, just like ATmegas, but why not use the Arduino IDE, which simplifies programming these devices? First, you need a programmer because the ATtiny does not have a USB connection. You can use an Arduino Uno for this, which is what I've done (you can buy one on eBay for about 10-15 euros).

In my example, I will use the ATtiny84, which has 14 pins. Hook it up to the Arduino Uno by connecting the pins below using some wires and a breadboard. You can find the appropriate pins for other ATtiny models in the datasheets or check out this link to a collection of reference sheets. Also, place a 10µF electrolytic capacitor between the Reset and GND pins on the Arduino to prevent it from resetting (do this after you've loaded the ArduinoISP sketch).

### ATtiny84 to Arduino Uno Connections

| ATtiny84 Pin | Arduino Uno Pin |
|-------------|----------------|
| VCC = 1 | 5V |
| Reset = 4 | Digital 10 |
| MOSI = 7 | Digital 11 |
| MISO = 8 | Digital 12 |
| SCK = 9 | Digital 13 |
| GND = 14 | GND |

### Setting Up the Arduino as a Programmer

Before using the Arduino Uno as a programmer, you need to load a sketch onto the Arduino. Open **File > Examples > ArduinoISP** in the Arduino IDE, load it, and program your Arduino as usual. Now, you have a programmer.

The Arduino IDE does not support ATtiny chips by default, so you must load the ATtiny core into the Arduino IDE. I've used the core found on this page. Extract it and copy it to a folder named `hardware` under your regular sketch directory. After restarting the Arduino IDE, you will find new cores in the **Tools > Board** menu.

You'll notice several clock speeds listed with the boards. I haven't figured them all out, but here’s what I know:

1. Select the ATtiny model you have and the clock speed you want to use.
2. Go to **Tools > Programmer** and select **Arduino as ISP**.
3. Choose the correct serial port under the **Tools** menu.
4. Click **Burn Bootloader** (this does not actually burn a bootloader but configures the ATtiny's fuses).

### Uploading Code

Now you are ready to go! Write some code (or use the Blink example) and ensure the LED pin in the source code is set to `0` instead of `13` (since ATtiny84 does not have digital pin 13). Compile the sketch and select **Upload Using Programmer** to upload it to the ATtiny.

I encountered the following error twice, but it seems to be normal—it just works!  
`avrdude: please define PAGEL and BS2 signals in the configuration file for part ATtiny84`

At first, it took me a while to get it working due to bad connections on the breadboard. So, don't doubt the software—check your connections and settings! Also, remember that if you have burned the bootloader (set the fuses) to 8MHz, you should program the ATtiny using the same speed. If you want to switch to 1MHz, select that speed, burn the bootloader, and then program the sketch. Otherwise, it won't work properly.

