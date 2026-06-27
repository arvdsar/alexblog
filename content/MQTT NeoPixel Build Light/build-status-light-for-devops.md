---
title: "Build status light for DevOps"
date: "2020-12-19"
tags: 
  - "devops"
  - "esp8266"
  - "neopixel"
  - "platformio"
---

![[IMG_3071-1.jpeg]]

Since we are now working from home, having a "Build Status Light" with a "Broken Build Siren" at the office no longer makes much sense. I wanted to do something fun, so I created a personal "Build Light" for my team members.  

The device is built using inexpensive components and is very easy to assemble. It subscribes to MQTT topics that provide the status of multiple CI/CD pipelines or display the status of a single CI/CD pipeline on all LEDs at once.  

I replaced the WiFiManager library with IotWebConf library which has an always available configuration page.

Below the README.MD from the Github Repository which is always up-to-date.
[Read on GitHub](https://github.com/arvdsar/MQTT_NeoPixel_Status_Multiple_Improved/blob/master/README.md)

Download the latest pre-build firmware 
![[firmware%20buildlight%20v1_5.zip]]
