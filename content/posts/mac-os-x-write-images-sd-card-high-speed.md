---
title: "Mac OS X - write images to SD Card with high speed"
date: "2015-02-13"
categories: 
  - "howto"
  - "raspberrypi"
  - "tech"
tags: 
  - "mac-os-x"
  - "raspberry-pi"
---

_Updated 2018: Just download_ [_Etcher_](https://www.balena.io/etcher/) _which works like a charm. Although the below still works!_

Writing SDCard images using my Macbook took way to long, up to half an hour to write one simple Raspberry Pi image to a SDCard. I just did what many instructions told me to do. You will probably recognize this command:

dd if=/path/to/image/file.img of=/dev/disk3 bs=1m  (where /dev/disk3 depends on your system).

Then I came across a comment somewhere of somebody telling to use rdisk3 instead of disk3. rdisk3 means using writing directly to SDCard outside of the OS doing all kind of buffering. Writing an SD card is done in 5 minutes or so.

so next time you write an image to a SDCard use:

dd if=/path/to/image/file.img of=/dev/rdisk3 bs=1m
