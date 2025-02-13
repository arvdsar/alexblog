---
title: "My Sensors"
date: "2018-12-27"
author: Alexander
---

I'm a big fan of the TinyTX sensors and the source code from Nathan Chantrell. By using a low-cost, small microcontroller (Attiny84) and the RFM12b transceiver, it is possible to build an entire grid of sensors in your home.

I have had two devices running for a few weeks now. These are manually made by soldering all the wires together, which doesn't look very neat and takes some time to build. Nathan published TinyTX version 3, which offers exactly what I was looking for: more available connections and space for experimentation. I've ordered 10 printed circuit boards from Seeed Studio to create more sensors at home.

Currently, my plans are as follows:
- Temperature & Humidity in the living room (implemented in a Wireless LCD Display)
- Outdoor Temperature & Humidity using a DHT22 sensor
- Attic Temperature & Humidity using a DHT11 sensor (inaccurate, but it works for now)
- Temperature & Humidity sensor in the kids' bedroom
- Temperature & Humidity sensor in the bathroom
- More temperature sensors
- Water flow sensor using piezo elements to detect someone taking a shower
- Add LDR sensors to detect light
- Mailbox (real-life) sensor to detect when mail is being delivered
