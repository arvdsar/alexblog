---
title: "DIY - Domotica 2020"
date: "2017-05-27"
author: Alexander
---

For about four years, I've been running my domotica setup using Arduinos, Raspberry Pis, and TinyTX. Step by step, I've added more components and upgraded the setup. You can read a lot about my older setup in the **DIY - Archive**.

Gradually, I'll be updating this page to add details about my recent setup.

## My Current Setup Is Built Around:

- **Docker Containers** (running on Synology NAS and Intel NUC)  
- **Portainer** (to manage the containers)  
- **Node-Red**  
- **Domoticz**  
- **Homebridge** (for Apple HomeKit)  
- **InfluxDB** (for storing data)  
- **Grafana** (for graphs)  
- **NGINX** (to access all these apps remotely)  
- **TinyTX Sensors** (from my previous setup)  
- **The Things Network** (Open LoRaWAN network)  
- **Z-Wave**  
- **Philips Hue**  
- **ESP8266** and probably more...

I've reduced the number of Raspberry Pis in my setup. Most of the above applications were running in Docker Containers on my **Synology DS-716 II NAS**. Since the number of containers increased, I added an **Intel NUC** to the setup, running most of the containers. Only the containers with databases now run on the Synology NAS (since it has enough storage and RAID 1).

Using Docker turned out to be stable, and upgrading to new versions of the tools is rather easy—made even simpler using **Portainer**.

Having been a Windows user for many years, I switched to Apple a few years ago. Therefore, I like getting things up and running with **HomeKit**, **Siri for voice control**, and **Apple Watch**. However, you'll also find **Google Nest** in my setup.

I'm not going to write detailed instructions on setting up specific software, as that information is easily available elsewhere. Instead, I aim to inspire you on how you could set things up, and occasionally provide links and code to help you along the way.

*To be continued...*
