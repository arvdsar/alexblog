---
title: "Wanhao Di3 Marlin Firmware"
date: "2020-06-28"
---

My Wanhao Duplicator i3 printer was still running on its initial firmware. This firmware lacks thermal runaway protection which is an important feature which can prevent fire.

Thermal runaway protection stops heating the extruder when there is no temperature increase for a set period. This can happen when your thermistor is disconnected for example.

I decided to go for the MARLIN firmware. No specific reason, its one of the most known firmwares.

The first step is to flash a bootloader onto the controllerboard. This is not hard when you have an Arduino Uno at hand and some wires. You do have to open the controller box, but on Youtube you can find many instructions on how to open the controller box and how to flash the bootloader.

The next step was to flash the Marlin firmware onto the controller. It turned out that for some reason it was not working with Platformio. It was not recognizing the board, but using the Arduino IDE it was not problem.

Most of the time was spend on creating the appropriate configuration file. There are some examples online which helped me to get most of the parameters set correctly, but the LCD didn't work properly. This was fixed by adding the following #define to configuration.h:

#define ST7920\_DELAY\_2 DELAY\_NS(400)

Additionally uncomment:  
#define LCD\_FOR\_MELZI

I have saved my working configuration files onto Github:  
[https://github.com/arvdsar/](https://github.com/arvdsar/wanhao_i3_v2_Marlin_v2_config)[wanhao\_i3\_v2\_Marlin\_v2\_config](https://github.com/arvdsar/wanhao_i3_v2_Marlin_v2_config)

One of the cool features of the new firmware is bed-leveling. The glass-bed is not perfectly level. You manually level the bed as good as you can and then via the menu you start bed-leveling. On 9 spots you will adjust the z-axis so that a sheet of paper can just move under the extruder. The firmware will then take into account the differences in height.

So if you are wondering if you should upgrade your firmware on the Wanhao i3, I recommend it!
