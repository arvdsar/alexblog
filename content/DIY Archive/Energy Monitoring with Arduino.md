---
title: "Energy monitoring with Arduino"
date: "2012-12-01"
categories: 
  - "gadgets"
  - "lifehacking-2"
  - "tech"
tags: 
  - "arduino"
  - "domotica"
  - "electricity-monitoring"
  - "energy-monitoring"
  - "pv"
  - "pvoutput"
  - "solar-panels"
---

Since we've bought a bunch of solar panels on our roof, I'm building an electricity monitoring device based on the Arduino microcontroller.

It's running for a while, monitoring solar power generation but now it can also read the Smart energy Meter which we got from the energy company.  So currently it reads and/or calculates the following data:

\- Actual & Peak solar power generation - total solar power generation today and lifetime - actual, peak and total today electricity import from grid - actual, peak and total today electricity export to grid - Actual, Peak and total today electricity consumption (Import + Solar - export) - Gas consumption per hour and day

All values are uploaded to PVoutput.org which offers some extended parameters to 'supporters'. Those can be used for i.e. Gas consumption. Unfortunately it can store the data but not (yet) show them in graphs.

Read more and download sources on the Arduino projects [here](https://www.vdsar.net/diy-domotica-solar-pv-output-metering/ "DIY – Domotica & Solar (PV) output metering"). And check the menu too for 'DIY - Domotica & PVOutput' for more details!

_You can download the whole package, Energy Meter, Domotica Gateway and Wireless LCD Display. Unfortunately it is not 'monkey proof', so you have to dig into the code and change it to suit your situation and needs._
