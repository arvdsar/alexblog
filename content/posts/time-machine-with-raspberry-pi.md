---
title: "Time Machine with Raspberry Pi"
date: "2014-07-26"
categories: 
  - "howto"
  - "gadgets"
  - "lifehacking-2"
  - "tech"
tags: 
  - "apple"
  - "backup"
  - "mac"
  - "raspberry-pi"
  - "time-machine"
coverImage: "RPI-B.jpg"
---

Create a Time Machine backup location for you Mac OS X systems using a Raspberry Pi and an USB harddisk. Works like a charm!

Setup your Raspberry Pi with Raspbian and connect the USB Harddisk.

Login to your RPi and execute the following command: $ sudo fdisk -l

Your disk will be one of the /dev/sd\* disks shown. Check which one is your external disk. If you only have one disk connected, it will be /dev/sda1.

When the USB disk is new, it is most likely formatted in FAT or NTFS. Prepare the drive for Linux: $ sudo fdisk /dev/sda (sda without a number!)

First delete the current partition by pressing “d”, then create a new (Linux) partition using “n”. Finalize the changes by using “w”. Next, format the ext4 filesystem: $ sudo mkfs.ext4 /dev/sda1 (sda1 with a one!)

Create a mount point for this disk. Use a name you like, I used "usbdrive". $ sudo mkdir /mnt/usbdrive

Check the UUID of the USB Drive: $ ls -l /dev/disk/by-uuid/

Copy the UUID (or write it on paper). If you want to auto mount this disk every time, add it to /etc/fstab:

$ sudo nano /etc/fstab add the following line to /etc/fstab: UUID=2304ab39234A /mnt/usbdrive ext4 defaults,user 0 2 _(2304ab39234A should be replaced with your UUID)_

The previous part was to setup the USB disk. Now we are going to the fun stuff. Install netatalk which adds Appletalk support. $ sudo apt-get install netatalk

$ sudo nano /etc/netatalk/AppleVolumes.default

Add for example the following directories to make those available on your Mac. A home directory for the user, a Time Machine backup location and just a network folder. Make sure you've created those folders and provide them sufficient rights for the user.

~/"Home Directory" /mnt/usbdrive/TimeMachine "Time Machine" options:tm /mnt/usbdrive/Raspi"RasPi Drive"

Options:tm is the option to make it a TimeMachine drive

Authorization is done based on the regular Linux users on the Pi. So you might want to create the same user on your Pi as you use on your Mac. Reboot your Pi to make sure it is al running.

Next, on your Mac you should see the Pi locations show up. Setup Time Machine on the Mac. When it asks for a username/password, it's the user you created on your Pi.
