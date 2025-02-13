---
title: "Limit SD Card writes on Rasberry Pi using Ramlog"
date: "2015-01-17"
categories: 
  - "howto"
  - "tech"
tags: 
  - "raspberry-pi"
coverImage: "sdcard.jpg"
---

A SD card has a limited amount of writes it can handle. The Raspberry Pi will write to log files a lot and reduce the lifetime of your SD Card.

Update 3-2-2016: RamLog seems not to be compatible with Debian Jessie. I haven't tried it yet but I have found a [blog](https://www.finnchristiansen.de/2015/11/11/raspberry-pi-debian-jessie-ramlog-und-fs2ram/) that might offer a solution for Jessie.

A simple solution is to use Ramlog which creates a temporary disk in memory where the logfiles are stored and updated. At boot the log files are loaded in memory. At shutdown they are saved to SD Card. During runtime writes are done in memory and not to disk!

How to install: `sudo apt-get install rsync sudo apt-get install lsof wget http://www.tremende.com/ramlog/download/ramlog_2.0.0_all.deb sudo dpkg -i ramlog_2.0.0_all.deb`

Now you need to modify some config files: `sudo nano /etc/init.d/ramlog`

Add the next two lines in the init part of the config (the part that starts with: #BEGIN INIT INFO). Include the # character!! `# X-Start-Before: rsyslog # X-Stop-After: rsyslog`

Now edit /etc/init.d/rsyslog `sudo nano /etc/init.d/rsyslog`

add 'ramlog' to the following two existing lines `# Required-Start: $remote_fs $time ramlog # Required-Stop: umountnfs $time ramlog`

`sudo insserv sudo reboot`

Reboot twice!!

After the second reboot check the ramlog log file for errors:

`sudo cat /var/log/ramlog` You'll probably see messages saying that you need to stop other daemons before being able to load/start ramlog. For example Samba or Cups. In that case find the appropriate file in /etc/init.d

For example Samba:

`sudo nano /etc/init.d/samba`

Add 'ramlog' to the following two existing lines `# Required-Start: $network $local_fs $remote_fs ramlog # Required-Stop: $network $local_fs $remote_fs ramlog`

For Cups: `sudo nano /etc/init.d/cups`

add 'ramlog' to the following two existing lines: `# Required-Start: $syslog $remote_fs ramlog # Required-Stop: $syslog $remote_fs ramlog`

Those lines makes sure ramlog is started before the other daemon (like cups or samba) is started.

After changing those config files, do a `sudo insserv` again and reboot.
