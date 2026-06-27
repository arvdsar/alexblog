---
title: "PlatformIO - Flash Firmware"
date: "2020-12-19"
author: Alexander

---

This is a short intro on how to flash new firmware to a microcontroller using PlatformIO. It was specifically written for some friends to use my MQTT_NeoPixel_Status_Multiple sketch on a Wemos D1 MINI.  
Flashing new firmware:
Flashing the firmware can be done using&nbsp;PlatformIO&nbsp;which is an OpenSource Embedded development platform with a great plugin for Visual Studio Code. Install PlatformIO in Visual studio Code and clone a software repository to a local folder. &nbsp;If the repository is setup for PlatformIO it will contain a standard folder structure and a platformio.ini file (an example is one of my repositories: https://github.com/arvdsar/MQTT_NeoPixel_Status_Multiple) 

Mac OS Big Sur - fix when building doesn’t work:
source ~/.platformio/penv/bin/activate
pip install -U --pre pyserial

In Visual Studio Code, select the PlatformIO Icon, Open, Projects and Add Existing and then select the folder where you have cloned a PlatformIO compatible repository.
The next time you don’t have to ‘add existing’, but just select it from the list of projects.When the project is added and opened, you see the ’src’ folder with in there the main.cpp file. This file contains the application. The platformio.ini is the configuration file for the platformIO environment and contains the dependencies of libraries, type of hardware (Wemos D1) and so on.
Compiling and uploading can be done by connecting the Wemos using a microUSB cable to your laptop. Select the platformIO icon on the left, then you see the type of hardware (d1_mini_pro or d1_mini) and below that, the build and upload option. Click on it and in most cases it will automatically detect the appropriate USB port and upload the firmware. (The type of hardware shown depends on the platformio.ini configuration file)
PAY ATTENTION: There are different versions of the Wemos D1: 4Mb and 16Mb. 4Mb = Mini, 16Mb = Mini_pro. Just try flashing. If it fails you pick the other one.&nbsp;
This is where you see the strength of PlatformIO. You can create multiple configurations in platformio.ini and based on the hardware you use, build and upload it from one environment.
Just in case you wonder where the firmware.bin file is, you can find it in a hidden folder: projectfolder/.pio/build/d1_miniThis file can be uploaded in case your sketch supports OTA (over the air) updates.
