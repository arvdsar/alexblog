---
title: "Rsync backup Mac OS X to Synology"
date: "2013-11-02"
categories: 
  - "lifehacking-2"
  - "tech"
tags: 
  - "backup"
  - "lifehacking"
  - "mac-os-x"
  - "rsync"
  - "synology"
  - "wake-on-lan"
---

I use Apple's Time Machine to make a regular backup of my Macbook. This seems to work okay, but so now and then it needs to redo the complete backup to remain reliable.... That sounds a little unreliable to me.

Because most of my data is on my Synology NAS or in the Cloud like Dropbox or Google Drive, I'm not that worried. Except for my iPhoto and iMovie libraries which reside on the Macbook only. The contents, that are the photo's and movies, are on the Synology too, but to reimport everything after a crash.... No way.

So  I've added a new script to my Synology to wake up my Macbook and start a rsync backup from Macbook to the Synology. The wake up works only via a wired network connection at home. That's ideal in this case because I only want this automated rsync when it is docked at home on a wired network (and then I also have the power plugged in).

Read my [previous post](https://www.vdsar.net/rsync-backup-synology-remote-raspberry-pi/ "Rsync backup Synology to Raspberry Pi") about Synology and Rsync too.

**Wake on LAN via Synology**

First install Wake on Lan (WOL) packages on your synology. Follow [this guide.](http://www.ruinelli.ch/various/syno_wol) It does work on DSM 4.3 too.

Now make the modification I found on [Dieter Vekeman website](http://dietervekeman.wordpress.com/2011/12/27/wake-on-lan/). Specific part is copied below:

After installing the WOL items, you will find an index.cgi script on the Synology installed at /volume1/@appstore/Wake On LAN/wol/ (default location)

Edit the index.cgi script, look for the line that says: _\# if no reply..no user...no authentication...so, bye-bye_

and comment the following line by putting # in front _**#die;**_

This makes you can wake up a system without login. You need this for the script to work.

By calling the next command you can wake-up a system.

wget [http://192.168.xxx.xxx:5000/webman/3rdparty/wol/index.cgi?wol\_mac=00:12:34:56:78:99](http://192.168.xxx.xxx:5000/webman/3rdparty/wol/index.cgi?wol_mac=00:12:34:56:78:99)

where 192.168.xxx.xxx is the local IP of your Synology DSM server and the mac address is your pc you want to startup.

In MacOS X system preferences, energy, check that wake from network is enabled!

**The SSH and Rsync stuff:**

Read my [previous article](https://www.vdsar.net/rsync-backup-synology-remote-raspberry-pi/ "Rsync backup Synology to Raspberry Pi") where I described how to setup SSH RSA Key's to be able to login without entering a password. Generate the Private and Public key on your Synology (/root/.ssh). If you already have a key pair just use that one! When you generate another in the same directory, it won't work.

Enable SSH login on MAC OS X by going to system settings, sharing, remote access (I have Dutch OS which says: "Systeem voorkeuren, Delen, Extern inloggen"). Make sure you use a secure password!

Add the public key contents (id\_rsa.pub) to the authorized\_key file of the user on the Mac:

On the Synology type: _cat ~/.ssh/id\_rsa.pub | ssh MACUSER@IP\_OF-MAC “mkdir ~/.ssh; cat >> ~/.ssh/authorized\_keys”_

see if it works: ssh MACUSER@IP\_OF\_MAC

now you should login without password.

Now you can create a script just like I described in my [previous post](https://www.vdsar.net/rsync-backup-synology-remote-raspberry-pi/ "Rsync backup Synology to Raspberry Pi"). You run the script as root on the synology. Source of data is MACUSER@IP\_OF\_MAC:/Users/MACUSER/Pictures Destination of data is a folder on your Synology.

I've added an example of my script, including the Wake on LAN part. Edit this script and add it to the 'Scheduled Task Manager' on the Synology and there you go. Again, check my previous post!

\[fusion\_builder\_container hundred\_percent="yes" overflow="visible"\]\[fusion\_builder\_row\]\[fusion\_builder\_column type="1\_1" background\_position="left top" background\_color="" border\_size="" border\_color="" border\_style="solid" spacing="yes" background\_image="" background\_repeat="no-repeat" padding="" margin\_top="0px" margin\_bottom="0px" class="" id="" animation\_type="" animation\_speed="0.3" animation\_direction="left" hide\_on\_mobile="no" center\_content="no" min\_height="none"\]\[wpdm\_file id=12\]

_I put the backup in a folder that is already synced to the remote Raspberry Pi too. So an additional backup is also available at remote location!_

Your iPhoto Library (and iMovie too) is shown as one big file on the Mac and contains several MB or GB's of data. This file is a package and Rsync can see the individual files in the package. So if you change or add one photo, Rsync only updates the photo and some database files from the package at the backup location.

 \[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
