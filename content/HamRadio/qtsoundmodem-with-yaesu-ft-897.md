---
title: QtSoundModem with U5Link & Yaesu FT-897 for HF Packet
date: 2022-01-01
categories:
  - ham-radio
tags:
  - Hamradio
---

How to configure your Raspberry Pi with QtSoundModem, an U5Link USB to Yaesu adapter and the Yaesu FT-897(d).

The following article from PE1RRR provided me information on where to find Packet on the HF band (20 meters) and I had to try it out. [https://eindhoven.space/2021/12/24/where-to-find-packet-on-20-meter-](https://eindhoven.space/2021/12/24/where-to-find-packet-on-20-meter-band/)[band](https://eindhoven.space/2021/12/24/where-to-find-packet-on-20-meter-band/


I’m running my HAM Radio software on a Raspberry Pi using [Build-a-Pi from KM4ACK](https://github.com/km4ack/pi-build).

With Build-a-Pi it is very easy to install all kind of HAM Radio software on the Raspberry Pi, including piQtSoundModem software.

I followed the above article and in no time the setup was done…. At least, for receiving. I was able to receive some packet stations over HF, but the PTT was not working.

I’m using a Yaesu FT-897d which is connected with a U5Link adapter to the Raspberry Pi. The U5link is a great adapter, but it cannot be triggered directly from QtSoundModem. I could not find a proper example to send HEX commands over CAT for PTT ON and PTT OFF nor could I trigger the DTR pin to trigger PTT.

After some messing around I found the solution to get this working properly by using a combination of **FLRIG**, **HAMLIB** (**rigctld**) and **PiQtSoundModem**. (all available in the Build-a-Pi setup)

![](Notification_Center.png)

FLRIG works properly with the U5Link adapter and the Yaesu FT-897d (see picture). The trick was to now start RIGCTLD (hamlib) to interface between FLRIG and QtSoundModem. You start rigctld from the command line with the following command where -m 4 tells it to use FLRIG: **rigctld -m 4 &**

Now you can start PiQtSoundModem from the startmenu and configure PTT to use HAMLIB.

![](HamPi_-_WiFi.png)

On the RaspberryPi (Build-a-Pi) you have PiQtTermTCP as terminal application. You can use this to connect to another station over Packet Radio.

You might wonder why I added FLRIG in the mix. One, because I already used it for Direwolf and Packet Radio on 2 meter but more importantly, when you configure RIGCTLD to use -m 1023 (for Yaesu FT-897d) directly, it will trigger the PTT at the moment you start rigctld. This is because the DTR is triggered on the U5Link and that causes the PTT to be on.

I had some trouble to get the audio out over the Yaesu. That was strange, since Packet Radio on 2 meters was working fine. It turned out that I had set the transceiver to USB (upper sideband) and in that mode it won’t take the audio input from the back of the receiver. Changing the mode to DIG (digital) made it work properly. (And DIG is for me already setup to use USB for FT8, JS8Call and based on the article above, is also fine for Packet on HF with this setup!)

I hope this article helps some people struggling with the combination of U5Link, Yaesu and some specific HAM Radio tools.
