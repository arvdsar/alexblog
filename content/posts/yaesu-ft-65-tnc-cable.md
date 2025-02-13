---
title: "Yaesu FT-65 - TNC Cable"
date: "2021-07-24"
---

After 26 years I wanted to experiment a bit with packet radio again. Packet Radio is not used that much anymore, but there is still some activity. Around 1995 I was active on 27MC, but this time I wanted to try the 2 meter/70 cm band and recently passed my license exam.

So now I have Yaesu FT-65 HT (handheld) transceiver and the fun can start. I had to make an interface cable between the speaker and mic connector of the Yaesu and also be able to trigger the PTT button to start a transmission.

I used the schema found here: [https://github.com/jaymzx/RPi-WD-Packet-Interface](https://github.com/jaymzx/RPi-WD-Packet-Interface)

It isn't working flawless at the time of writing. The DCD led, which is just fun seems to disturb somehow. (So I disabled it for now).

The biggest thing was to create a proper interface of the Speaker / Mic cable. Some info related to the pin-out can be found [https://hackaday.io/project/171066-yaesu-baofengkenwood-converter/log/176295-yaesu-ft-65-pinout](https://hackaday.io/project/171066-yaesu-baofengkenwood-converter/log/176295-yaesu-ft-65-pinout:)

Initially I used another schema and the Yaesu started to reset itself when the squelch was open, strange behavior all over the place. It turned out that the sleeve (where you usually expect ground) is not ground in case of the speaker. It's easily overlooked in the pinout schema!

So what is working:

2.5" Jack Plug for the Mic: Connect the Mic (signal) to the tip of the connector. Ground is on the sleeve (as sort of expected). Enabling PTT is done by connecting the MIC using 2k resistor to ground.

3.5' Jack Plug for the Speaker: connect the audio (signal) to the sleeve (where you would expect ground) and connect ground to the tip.

It is a tight fit to put two separate connectors into the Yaesu FT-65 so I had to remove the 'casing' of the connector and isolated it with some shrink tube. Be careful that the sleeve of both connectors do not touch each other.

I'm using direwolf with Linpac to use AX25 packet radio.
