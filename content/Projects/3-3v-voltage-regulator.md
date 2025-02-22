---
title: "3.3v Voltage Regulator"
date: "2017-06-04"
author: Alexander
---

I needed an energy efficient voltage regulator board to get a stable 3.3volts out of a 18650 battery which has a nominal voltage of 3.7volts but at full charge they reach 4.2volts. Until now I reduced the voltage with 0.7 volt by using a 1N4148 diode in series but that is far from ideal. In other situations where prototype boards contain an onboard voltage regulator they use often to much energy in standby. A battery won't last too long in that case.

I've designed a 3.3 volt board using a MCP1703 and two capacitors. Very simple setup and it should do the job. Max current is 250 mA they say. I designed the board using Eagle. You can find the design files here:
![[DIY Projects/attachements/3.3volt_mcp1703_RevA.zip]]

I've ordered the PCB's at Seeedstudio and used a hot air solder iron to finalize the boards with components. It is working perfectly!


![[IMG_0373.png]]!