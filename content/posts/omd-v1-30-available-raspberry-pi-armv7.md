---
title: "OMD v1.30 available for Raspberry Pi (ARMv7)"
date: "2016-07-03"
tags: 
  - "raspberry-pi"
---

An updated version of Open Monitoring Distribution (OMD) is available at the Bananian site [here](https://www.bananian.org/omd). They've build it for the ARMv7 (BananaPi, Raspberry Pi 2 & 3, OrangePi).

I've written a [complete install manual](https://www.vdsar.net/raspberry-pi-open-monitoring-distribution-setup-guide/) for version 1.00 which should work for version 1.30 too. Just make sure you use Raspbian Jessie.

The related Check\_mk\_agent files can be found at their download location too, [http://dl.bananian.org/software/omd/](http://dl.bananian.org/software/omd/).

_To install check\_mk\_agent on a raspberry pi you type the following commands from a home directory:_

wget [http://dl.bananian.org/software/omd/check-mk-agent\_1.2.6p12-1~bpo8+1\_armhf.deb](http://dl.bananian.org/software/omd/check-mk-agent_1.2.6p12-1~bpo8+1_armhf.deb) sudo dpkg -i check-mk-agent\_1.2.6p12-1~bpo8+1\_armhf.deb
