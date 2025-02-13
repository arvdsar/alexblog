---
title: "DIY - Energy Monitor"
date: "2012-12-02"
author: Alexander
---

The energy monitor is based on the Arduino Mega 2560 which offers sufficient memory and multiple UART's (Serial Ports). Currently it is:

- Arduino Mega 2560 with EthernetShield
- Count pulses of kWh meter and generate energy statistics
- Read P1-port output of smart energy meter
- Upload the statistics to pvoutput.org
- Monitor electricity import and export from grid and total consumption
- Monitor gas consumption
- Send statistics over ethernet to my Arduino ‘Domotica Gateway’.

This page describes the parts used and roughly how it works. I have used parts of other freely available code and combined it to what I wanted to have. Source code is available on request; just leave a comment asking for it. You will receive the whole package: Energy Meter, Domotica Gateway, and Wireless LCD Display. Unfortunately, it is not 'monkey proof', so you have to dig into the code and change it to suit your situation and needs.

### Credits
Harold65 for his version 7, which is used as the base for my modifications.

This page will be updated with additional info. It takes some time to write it all down.

## P1 - Port connection
The smart meter is connected with an RJ11 connector. You can use an old telephone cable if you like. There are 3 connections to make:

- **RTS** - Set this HIGH, and the meter will send data every 10 seconds.
- **GND** - Just connect it to GND on your Arduino.
- **RxD** - Serial receive. Connect to the 7404 chip (just continue reading!).

**Remember:** RJ11 can have 6 pins but usually comes with 4. So count as if there were 6 pins on the connector!!!

The smart meter P1 port has inverted TTL signals. TTL means the voltage is 0 - 5 volts instead of regular serial signals, which are -12V and +12V. Also, the signal is inverted, so you can't just connect it to your Arduino. (You could when using SoftSerial, but I use the hardware serial port, which offers better performance.) It's not hard to invert the signals, but you need an additional IC (chip) to invert them. Go buy an **SN74HC04** chip for 20 cents and hook it up:

- **Pin 14** to +5V (=VCC)
- **Pin 7** to GND
- **Pin 1** to RxD (from smart meter)
- **Pin 2** to Arduino Receive on UART 1 (Pin 19 on Arduino)

When a **5V** is received on **Pin 1**, a **0V** is on **Pin 2**.
When a **0V** is on **Pin 1**, **Pin 2** becomes **5V**. It just inverts the 1 to 0 and 0 to 1. ;-)

The Mega 2560 has **4 UARTs**. UART 0 is also connected to USB for connection to the PC and serial monitoring. We pick **UART 1 (Serial1)**, which has the **Receive on Pin 19**. The smart meter uses slightly different settings than normal. Since Arduino IDE **1.0.2**, we can easily set those parameters by using:

```cpp
Serial1.begin(9600, SERIAL_7E1);
```

In my code, I use **Pin 4** to connect to the **RTS pin** in the smart meter. When **Pin 4** is HIGH, the meter starts sending data every **10 seconds**. I don't do rocket science with this pin—just make it high at program start and start reading.

You receive the whole package: **Energy Meter, Domotica Gateway, SensorBox, and Wireless LCD Display**, so all versions work together. I've packed all libraries as they are on my disk now. Those might not be the most recent versions, but they should work with the sources. Unfortunately, the sources are not 'monkey proof', so you have to dig into the code and change it to suit your situation and needs.

