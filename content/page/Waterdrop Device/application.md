---
title: Application
date: "2010-12-11"
author: Alexander
---

Like with many other software development projects, while writing the application, many new features popped up. I decided to implement basic features first and, based on the results and experiences from the first photo sessions, build new releases. Currently, the application has the following features:

### Version 0.19 - Updated 6 August 2011
(Download link at the end of this article)

#### Hardware:
- LCD Display Control
- 16 keys matrix keypad
- 1 x flash trigger output
- 1 x autofocus & 1 x shutter output
- 1 x water valve output
- 1 x analog input for sound & light detection sensor

#### Program (Menu):
- Basic waterdrop program
- Auto increment time between drop creation and photo capture
- Auto increment time between two drops
- Auto increment size of water drops
- Sound detection
- Lightning detection
- Store values in EEPROM
- Load values from EEPROM
- Erase EEPROM values
- Configuration Menu to save basic values
- Possibility to enter values with 0.1 millisecond accuracy

In the basic program, you enter the waterdrop size (time to open the valve), time between creating the waterdrop and taking a photo (trigger flash), number of waterdrops, time between drops, and number of photo cycles. You can also enter the index number of the last photo taken by the camera. This can be very useful to find specific settings for a particular photo.

Within the three auto increment programs, you can also enter the increment value. For example, auto increment time with 5 milliseconds. The program will run the number of photo cycles and take a picture. It will then increment the photo index number.

Using the "Store values in EEPROM" menu, you can save the settings used to create a specific photo. Just enter the number of the photo (your camera usually stores this in the filename) and save the settings. Every time a photo is taken, the used settings are stored in the EEPROM. Settings for up to 39 photos can be stored. Users can flag any of these settings to skip them in an EEPROM erase cycle. This way, you can keep successful settings while still being able to erase useless ones. In the future, it might be nice to add external EEPROM memory.

**Note**: Storing information in EEPROM has its limits. The EEPROM can be written 100,000 times, after which it might become defective. This means, in theory, that after taking 100,000 photos (depending on the new program, maybe up to 400,000 photos), you will need to buy a new Atmel processor. They cost about 5 euros, and 100,000 photos is also the estimated lifetime of a regular DSLR mirror mechanism, so I would worry more about buying a new camera. ;-)

It's now possible to enter values with 0.1 millisecond accuracy (for the time between two drops and the time between releasing a drop and taking a shot). I expect that an effective accuracy of 0.5 milliseconds is more realistic, but it might be the difference between a nice picture and a great picture. :-)

### Improvements:
After one evening of using my initial program, I identified some possible improvements that need to be implemented:
- Possibility to use different drop sizes within one cycle (enter value for 2nd drop size, implemented since v0.18)
- When easily possible, make the increment programs also accept negative numbers, effectively making them a decrease
- When memory size allows, add control via PC over Serial port
- Use EthernetShield and control from PC or webpage
- Think about making the valve movable (just like an inkjet printer head) to create drops next to each other
- Optimize the questions asked in the menus (e.g., when only creating 1 drop, don't ask for time between drops—implemented in v0.19)
- Add the possibility of Next/Prev within a program

[wpdm_file id=1]


