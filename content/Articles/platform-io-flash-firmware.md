---
title: "Platform IO flash firmware"
date: "2020-12-25"
---

I started using PlatformIO as replacement of the Arduino IDE. At first it was a bit harder to work with, but it has a lot of great features and after a while it is way more efficient than the Arduino IDE. Especially the libary management is a big plus.

This page is to give a very short instruction on how to build and upload new firmware to a microcontroller like the Wemos D1. Actually it was specifically written for a project with a couple of friends to get them started.

**Flashing new firmware**:

Flashing the firmware can be done using [PlatformIO](https://platformio.org/) which is an OpenSource Embedded development platform with a great plugin for Visual Studio Code. Install PlatformIO in Visual studio Code and clone a software repository to a local folder.  If the repository is setup for PlatformIO it will contain a standard folder structure and a platformio.ini file (an example is one of my repositories: [https://github.com/arvdsar/MQTT\_NeoPixel\_Status\_Multiple\_Improved](https://github.com/arvdsar/MQTT_NeoPixel_Status_Multiple_Improved)

```
Mac OS Big Sur - fix when building doesn’t work:
source ~/.platformio/penv/bin/activate
pip install -U --pre pyserial
```

In Visual Studio Code, select the PlatformIO Icon, Open, Projects and Add Existing and then select the folder where you have cloned a PlatformIO compatible repository.

![](Screenshot_25-11-2020_21_01-1024x573.png)

The next time you don’t have to ‘add existing’, but just select it from the list of projects.  
When the project is added and opened, you see the ’src’ folder with in there the main.cpp file. This file contains the application. The platformio.ini is the configuration file for the platformIO environment and contains the dependencies of libraries, type of hardware (Wemos D1) and so on.

![](Welcome_—_BuildMonitorMQTT_New-1024x985.png)

Compiling and uploading can be done by connecting the Wemos using a microUSB cable to your laptop. Select the platformIO icon on the left, then you see the type of hardware (d1\_mini\_pro or d1\_mini) and below that, the build and upload option. Click on it and in most cases it will automatically detect the appropriate USB port and upload the firmware. (The type of hardware shown depends on the platformio.ini configuration file)

PAY ATTENTION: There are different versions of the Wemos D1: 4Mb and 16Mb. 4Mb = Mini, 16Mb = Mini\_pro. Just try flashing. If it fails you pick the other one. 

This is where you see the strength of PlatformIO. You can create multiple configurations in platformio.ini and based on the hardware you use, build and upload it from one environment.

![](Screenshot-2-788x1024.png)

Just in case you wonder where the firmware.bin file is, you can find it in a hidden folder: projectfolder/.pio/build/d1\_mini  
This file can be uploaded in case your sketch supports OTA (over the air) updates.

![](firmwares-1024x585.png)
