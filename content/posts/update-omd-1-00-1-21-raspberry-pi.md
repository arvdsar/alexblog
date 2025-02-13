---
title: "Update OMD 1.00 to 1.21 on Raspberry Pi"
date: "2015-02-02"
categories: 
  - "howto"
tags: 
  - "computer"
  - "raspberry-pi"
---

Today the new Raspberry Pi 2 model B was announced. ARMv7 CPU with 1 Gb of memory. This made me search for OMD (Open Monitoring Distribution) for ARMv7 (Which can be found [here](https://www.bananian.org/omd)). While searching I stumbled upon an update [OMD 1.21 for ARMv6](http://www.monitoring-portal.org/wbb/index.php?page=Thread&threadID=32454) which is the original Raspberry Pi. I have two Pi's running. One at my location and one at a customer site.

I upgraded my Pi succesfully to the new version using the following commands:

Login as root (or su -) `echo 'deb http://labs.consol.de/repo/testing/debian wheezy main' >> /etc/apt/sources.list.d/consol.list gpg --keyserver keys.gnupg.net --recv-keys F8C1CA08A57B9ED7 gpg --armor --export F8C1CA08A57B9ED7 | apt-key add - aptitude update aptitude search omd-1.21` The final command will return the latest 1.21 build, in my case: omd-1.21.20141206

`aptitude install omd-1.21.20141206`

A new installation of OMD will be installed. This is how OMD is updated, it's not overwriting an old install.

`omd versions (shows you the installed versions) omd stop <sitename> omd update <sitename> omd start <sitename>`

Now you will be running the OMD 1.21 version. During the update I got an error related to new settings in NagVis config. I don't use Nagvis yet, only messed a little with it. So I choose to just install the new settings. On the other Pi where I haven't messed around with NagVis I didn't get any errors.
