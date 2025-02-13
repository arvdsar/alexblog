---
title: Schematics
date: "2010-12-11"
author: Alexander

---

This page contains the schematics of the DIY waterdrop device. It's a collection of information I found on the internet and used to build my waterdrop device. Credits go to the people who designed it. Sometimes it's hard to get specific component types. Usually it is okay to use a similar type.
You can download the source code from the application page.
Table of contents:Arduino UnoValve ControlFlash and Shutter ControlVoltage Regulator 5 and 9 voltsLCD displayKeypad using 1 analog input pinSound Detection
Arduino Uno
You can find all information necessary on www.arduino.cc. I suggest to just buy it pre-build from some local reseller. If you want to build it yourself, you can find the schematics on this site too. The Uno has just sufficient memory and ports. You have to program this one efficient in case you want to store settings in memory etc. Buying the Mega gives you more memory and ports.(I have connected a 20x4 LCD, Keypad and the Flash-, Shutter-, Sound- and Valve Triggers and still have ports available on the Uno)
Valve Control
The Shako valve uses 24 volts DC. I would prefer to use 12 volts because it doesn't heat the voltage regulators that much, but 24 volts will do the job. The Arduino cannot provide the power to activate the valve, therefore you need this electronic circuit: &nbsp;(check the connection pins of the TIP121 or compatible carefully. I don't know if the pin numbers are correct in this drawing) 
Flash and Shutter Control
Use 3 optocouplers of&nbsp;type 4N25 or equal&nbsp;to trigger the flash and shutter. The benefits of an optocoupler is an optical isolation between the flash- and cameracircuits from the electronic part of the microcontroller. The schematic created for 1 flash and 1 camera.&nbsp;The shutter requires two optocouplers (1 for autofocus and 1 for shutter. Even when you don't use autofocus. You have to imitate the functionality of the shutter button of your camera which is half way press = autofocus and full press is shutter.) The other optocoupler is to trigger your external flash. In case you need more flashes, just extend the schematic. Remember keep the electronic circuits of the microcontroller and camera and flash seperated from each other (so do not connect the GND between Microcontroller and/or Camera and/or flash.
Each optocoupler is connected to one digital pin on the arduino. Making the pin high will turn on a led inside the optocoupler which makes the optical transistor inside the optocoupler to switch. No other external power is necessary for the optocoupler to work. Build as many optocoupler circuits as devices (or switches) you need.&nbsp; An optocoupler can handle a very limited amount of current so don't switch heavy currents. Modern flashes use about 6 volts to be triggered. Older flashes may use up to 300 volts which might damage the optocoupler. I don't know if there are optocouplers that can handle this voltage, but I think they exist.
Voltage Regulator 5 and 9 volts
The Arduino can handle voltages between 5 and 12 volts but only works stable between 7 and 12 volts (above 12 volts the&nbsp;onboard&nbsp;voltage regulator will overheat). The input voltage of my system is 24 volts because I need 24 volts for the valve. I created 3 voltages in my system:- 24 volt DC;- 9 volt DC for powering the Arduino Uno;- 5 volt DC for powering external circuits like the sound trigger.
The 9 volt is chosen because it's within the limits of the Arduino Uno specs and I wanted a high as possible voltage to make the difference with 24 volts as little as possible. (The bigger the difference, the hotter the regulator will be). I could choose 12 volts, but that is on the limit of the Arduino.The Arduino has its own voltage regulator and will output 5 volts on the digital pins which is perfect for all the other components like the optocouplers and so on.
The 5 volt regulator is used to power external devices like a sound trigger. I didn't want to load to much on the Arduino and this circuits costs a couple of euro's.
The voltage regulator used are a 7805 for 5 volts and the 7809 for 9 volts. Make sure you get the 1A version or even the 2A version. Mount a heatsink on the 780x component.The capacitor C3 is an electrolitic (ELCO), the others are regular (ask your supplier, they can advise you).
LCD displayJust buy a nice LCD display on ebay based on the HD44780 driver IC.&nbsp; Use one of the size you like 16x2 or 20x4.connect pins RS, Enable, D4, D5, D6 and D7 to the Arduino. Connect pin R/W to ground so you can write info to the display.Use Google to find one of the many explanations on how to connect the LCD Display.
This is a PDF manual&nbsp;of the&nbsp;LCD I used. All LCD's look like the same approach so it might be valid for yours too.
Keypad using 1 analog input pin
A matrix keypad&nbsp;can also be bought on ebay for a couple of dollars. Normally you need several digital input&nbsp;pins to read the matrix. By using a&nbsp;voltage divider you only need 1 analog input. This works great even on a 16 button keypad. In software, read the value of the analog port while pushing a key. Then you know the approximate value that that specific keypress will provide.&nbsp; The pins on the keypad are probably 4 rows + 4 columns (or 4 col + 4 rows). Just use your multimeter to see which pins are connected when pushing a button. I used the 5 volts of the Arduino board to 'power' this matrix.
More info on Arduino Forum&nbsp;and on this site.
Sound detection
I also build a sound detection interface to trigger the flash when a noise occurs. I used the circuit found in this PDF which I did not designed myself. It does work but I think there are better solutions which are more accurate. Search for it !
