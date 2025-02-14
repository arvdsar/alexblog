---
title: "S0 counter with Arduino Yun"
date: "2020-06-21"
author: Alexander

---

Dutch smart meters can only deliver electricity stats on imported and exported electricity from and to the grid. PV inverters sometimes have an API or RS-232 or other interface to deliver information on generated energy but my PV inverter does to have this.
I've written an S0 Counter which counts pulses from an energy meter (or other pulse sensors like water meters) and upload the details to pvoutput.org and additionally send the values via MQTT topics for use in your domotica setup. (i.e. Domoticz or Node-Red).
Below the README.MD from the Github Repository which is always up-to-date.
[git-github-markdown url="https://github.com/arvdsar/S0_PVOutput_MQTT_Yun/blob/master/README.md" cache_ttl="3600" cache_strategy="static"]
