---
title: Rsync backup Synology to Raspberry Pi
date: 2013-10-29
categories:
  - lifehacking-2
  - tech
tags:
  - synology
  - backup
coverImage: RPI-B.jpg
---

I've been using the  Strato Hidrive service for a couple of years now to make a remote backup of my local Synology NAS. This is done using Rsync that is available on the Synology and with Hidrive.

Strato Hidrive offers much more than only Rsync, but I just use it for remote backup. Actually I pay almost 140 euro's a year for 250 Gb of storage. My photo's are worth the money but then I realised that I can build something myself.

I just want a backup of selected folders from my Synology to a remote location. The Synology itself already has RAID-1 mirroring, data is backupped to external USB drives and so now and then to Blueray disks. All those backups are stored locally and because the drives are connected, one lightning strike is sufficient to destroy all.

The remote location is not that hard to find. You just need a friend or parent house with reasonable internet connection and a power outlet ;-).

[![Raspberry Pi model](images/RPI-B-300x199.jpg)](http://www.raspberrypi.org)I've bought a Raspberry Pi Model B with 512 Mb memory, 8 Gb SD Card, Powersupply and case for less than 70 euro's (that's half a year of the Hidrive subscription). An external USB harddrive of 2 TB can be bought for about the same amount. I choose the Western Digital Elements Desktop 2 TB with external power supply. The Raspberry Pi cannot power a 2,5 inch USB disk so you would need to buy an additional powered USB hub. Power usage of the desktop version of the WD Elements disk is 12 watt at spin-up, 5 watts while in use and almost nothing in standby. The disk does go to sleep when idle on the Raspberry Pi!

Below is a Step by Step description how to setup the Raspberry Pi and Synology to perform automated backups on the Raspberry Pi. I'm not a Linux expert. In case things do not work, check Google first. Leave a comment if you have improvement suggestions.

**NOTE: In this setup you create a sync of folders from the Synology to another location on the Raspberry Pi. If you change the content of a file, that file is overwritten in the destination. So it does not protect you from 'stupid'  mistakes while editing files. It does protect you from losing your data when your Synology is stolen, explodes or crashes. Continu reading, there is an option to make it a little more a backup.**

My first intention was to use the standard Synology Backup Manager to configure a rsync backup to another server. I couldn't get this working using SSH. Only unencrypted (so insecure) connections worked. Therefore I started to use the 'Scheduled Task’ function in the Synology to run my own rsync scripts. Actually I’m happy that I did, because I now know better how rsync works and I have setup other backups (i.e. backup another Raspberry Pi to my Synology!)

First make sure you have a running Raspberry Pi with [Raspian](http://www.raspberrypi.org/downloads) Linux installed on a SD Card. Connect an external USB harddisk to the Raspberry Pi (I will shorten Raspberry Pi to RPi from now on).

**Disk configuration** I finally choose to use EXT4 filesystem instead of NTFS. NTFS has the benefit that you can connect the disk to a Windows or Mac computer to read the data in case of a recovery. It turned out that the ntfs-3g driver for the RPi uses a lot of CPU therefore limiting the write speed. (SSH Secure transfer and Rsync takes CPU resources too). I think on a slow connection (up to 10 Mbit) you can still use NTFS, but in case you also want to use the RPi as a local NAS, don’t use NTFS. You can connect the USB drive with EXT4 file system to the Synology and read files directly. Also additional software to use it on Mac OS X is available too, so it's flexible enough for me!

Login to your RPi and execute the next commands:

_$ sudo fdisk -l_

Your disk will be one of the /dev/sd\* disks shown. Check which one is your external disk. If you only have one disk connected, it will be /dev/sda1. When the USB disk is new, it is most likely formatted in FAT or NTFS. Prepare the drive for Linux:

_$ sudo fdisk /dev/sda_  (sda without a number!)

first delete the current partition by pressing "d", then create a new (Linux) partition using "n". Finalize the changes by using "w". Next format the ext4 filesystem:

_$ sudo mkfs.ext4 /dev/sda1_  (sda1 with a one!)

Create a mount point for this disk. Use a name you like, I used usbdrive.

_$ sudo mkdir /mnt/usbdrive_

If you want to auto mount this disk every time, add it to /etc/fstab:

_$ sudo nano /etc/fstab_

add the following line to /etc/fstab:

/dev/sda1     /mnt/usbdrive     ext4     defaults,user     0     0

Maybe you need a restart of the RPi ($ sudo restart), but then you should see your USB drive attached and mounted. Try writing a directory or file to the disk using:

_$sudo mkdir /mnt/usbdrive/test_

If this works, your disk is mounted correctly.

**Setup Linux user accounts:**

If you want a more secure RPi, add a new user and remove the user: "pi". [This site](http://raspi.tv/2012/how-to-create-a-new-user-on-raspberry-pi) tells you how. At least change the standard password for user "pi" by using:

_$ passwd_

Create a new user "synology" to use for the rsync backup and set a password. Choose a highly secure password when you connect the RPi to the internet.

$ useradd synology -m -G users $ passwd synology

**Samba**

We don’t need Samba to rsync files to the RPi. Samba is used for sharing files with Windows and Mac. I.e. when you have the RPi connected to a local network you can access files on the RPi from the Windows browser. Also, let’s say you have this device setup at a remote site (your friends place). Your friend could hook-up a second harddisk and use your RPi to create a simple NAS. Also check [this page](http://simonthepiman.com/how_to_setup_windows_file_server.php).

Install Samba:

_$ sudo apt-get update_ _$ sudo apt-get install samba_ _$ sudo apt-get install samba-common-bin_

restart Samba: _$ service samba restart_

_Configure Samba user:_ $ _smbpasswd -a username_

_configure the shared folder(s):_ $ _sudo nano /etc/samba/smb.conf_

uncomment the line: security = user

Next, at the end of the smb.conf file add a shared folder configuration for the USB drive. Make sure your users are member of the group users when things don't work!

\[fusion\_builder\_container hundred\_percent="yes" overflow="visible"\]\[fusion\_builder\_row\]\[fusion\_builder\_column type="1\_1" background\_position="left top" background\_color="" border\_size="" border\_color="" border\_style="solid" spacing="yes" background\_image="" background\_repeat="no-repeat" padding="" margin\_top="0px" margin\_bottom="0px" class="" id="" animation\_type="" animation\_speed="0.3" animation\_direction="left" hide\_on\_mobile="no" center\_content="no" min\_height="none"\]\[usbdrive\] comment = external drive path = /mnt/usbdrive valid users = @users force group = users create mask = 0660 directory mask = 0771 read only = no

(Start reading yourself a little more on this Samba topic. I'm not sure if the settings are perfect, but at least it works for now)

**Setup SSH login with SSH keys**

When you login using SSH you are asked for a password. When using scripts for the rsync backup on the Synology, you don’t want to enter a password. To solve this you have to generate SSH RSA Keyfiles.

First login to your **Synology** using SSH (enable SSH on your Synology first). On windows you need Putty, on a Mac or Linux device you can just enter the command below from the terminal.

_$ ssh root@IP\_OF\_YOUR\_SYNOLOGY_ the root password is your admin password of the Synology.

on the Synology enter the following commands: _$ cd /root/.ssh_ _$ ssh-keygen_ Push enter for each question. At the end there is a private and public key file in /root/.ssh the default key file names are id-rsa and id-rsa.pub. You can enter another name during ssh-keygen if you like. (The private key = id-rsa, should reside in /root/.ssh and nowhere else. This is important otherwise it does not work! The public key = id-rsa.pub can be copied to the system you want to login to)

Copy the id-rsa.pub to the .ssh folder of the Synology user on your RPi. Enter the following commands on the Synology. This will also add the contents of the file to the authorized\_keys file.

_cat ~/.ssh/id\_rsa.pub | ssh synology@IP\_OF-RPI "mkdir ~/.ssh; cat >> ~/.ssh/authorized\_keys"_

Next, on the RPi:

_$ cd /home/synology/.ssh_ _$ chmod 600 authorized\_keys_

(The .ssh folder is hidden, that is the point before .ssh. Using „ls -la” you can see the directory contents including hidden files and folders)

Now you should be able to login from the Synology to the RPi without entering a password using: ssh synology@_IP\_OF-RPI_

You have to make sure this works, otherwise the rsync script will not work!

**Rsync configuration**

Rsync is installed by default on the RPi. We use Rsync over SSH meaning the login and datatransfer are encrypted. This is secure for transferring data over the internet.

create a folder on your RPi USB disk to store the backup (if you like).

$ mkdir /mnt/usbdrive/MyBackup

I describe my setup, adjust for your situation. My synology contain one disk with all shared folders like "video", "homes", "photo", etcetera. I don't want to backup all folders, because some contain very large files which can be replaced easily, like a movie file. There are multiple ways to configure rsync, it took me a while to find the best for my situation.

My disk structure:

/volume1 /volume1/video /volume1/video/Home Video --> non replaceable, so backup! /volume1/video/DVD  --> replaceable, do not backup! /volume1/homes/mike --> non replaceable, backup /volume1/homes/joey --> not important user, do not backup! /volume1/Scripts --> important, it contains the scripts I use!

I choose to enter /volume1 as source directory and exclude all files and directories that do not need to be processed with rsync. Before, I made the mistake to provide all the folders to be processed as source location. It did work, but it made the script a mess ;-).

The rsync scripts, exclusion files, rsync-log files are stored in a shared folder on the Synology: /volume1/Scripts. Because it is a shared folder I can access it from the Mac or Windows PC.

I now use the following command (simplified):

_rsync -avR --exclude-from=/volume1/Scripts/Rsync/Exclude.txt    /volume1    synology@IP\_OF\_RASPBERRY:/mnt/usbdrive/MyBackup >> /volume1/Scripts/logfile.txt_

The rsync format is: rsync options source destination

add "z" to the options to compress the data (-avRz) add "n" to the options to perform a dry run. (nothing is really copied, but you can see what happens in log files. -avRzn). add "--delete" (two dashes before delete, so - -delete (without a space) to delete files from destination when they are not on the source anymore.

\--exclude and --include are also options. (also two dashes in front of it)

White spaces make it difficult to enter them correctly within a command line (like: /volume1/video/**Home Video**). Some difficult escape characters are necessary and actually, I couldn't get it right and found another solution. I use an exclusion file with all files and folders I want to exclude from the backup.

Let's see what the rsync command above does: -avRzn are options. Archive, verbose, Recursive, Compression, DryRun. Remove the "n" option once you are convinced it's running properly. The compression option "z" is useful for internet transfers, on local networks it takes to much CPU and slows things down! **I suggest to have a look at the "b" option too.** The "b" option creates some kind of backup of a changed file. Use Google for this one!

\--exclude-from= This points to a file exclude.txt that is stored on the synology. This file contains all files and paths I want to exclude from the backup. An example is shown below.

\--delete without the --delete option only files will be updated or added on the destination location. No files will be deleted. This means that once you delete a file or directory on your Synology, it will remain on the RPi USB drive. I believe this is handy when you accidentally delete a folder and detect this 3 days later. Downside is that after a while your destination is cluttered with all kind of old folders and files you have already deleted (or moved) on the source location. So once in a while you could modify your script and add the --delete option, run the script once and again remove the --delete option. During this single run all old files and folders are removed. It might be a good idea to first do a dry run using the "n" option too and check your logfile.

/volume1 This is the source directory for the backup. Without the --exclude-from everything would be processed with sync!

synology@IP\_OF\_RASPBERRY:/mnt/usbdrive/MyBackup This is the destination to write the backup to. A SSH connection is opened to the RPi for user synology and data is stored in /mnt/usbdrive/MyBackup. This is why we needed the SSH Keys ;-)

_\>> /volume1/Scripts/logfile.txt_ Write the output to a file. You can see which directories and files are processed (and therefore also which files are not processed). When using the "n" option you can use this logfile to see what happens, without it really being processed.

**exclude.txt example**

This file contains all the files and directories we want to exclude from the backup. Remember, we tell rsync to backup: /volume1, so we need to exclude everything we don't want!

Create a text file with content like:

\- @\* - .\* - /volume1/aquota\*.\* - /volume1/video/DVD - /volume1/homes/joey - $RECYCLE.BIN - #recycle

As you can see, I exclude all files that start with . and @. Also aquata\*.\* and the recycle bin's are excluded. The folders DVD and joey are excluded. This took some trial and error and there you benefit from the "n" option and the logfile! The - in front of the items are necessary in the file. You can also use a + sign, but I have no cue (yet) why use - or +. Google will help you.

Download the rsync-script and exclude file I use. Modify it for your situation. The script also includes Flock. Flock makes sure the script can run only one time. Imagine that you make the initial backup which can run for multiple days. You don't want this script to start again during this run.

\[wpdm\_file id=11\]

**Configure the backup on the Synology**

I always use the latest DSM on my Synology. Below screenshot is from DSM 4.3. It does work with 5.x too! I think that the 'Scheduled task' option is implemented since DSM 4.x. Otherwise check Google on how to use CRON with the Synology.

Find the Scheduled Task planner (I use a Dutch version, but look at the icon)

[![Synology_DiskStation_-_vdSarDisk_3](images/Synology_DiskStation_-_vdSarDisk_3-300x202.png)](https://www.vdsar.net/wp-content/uploads/2013/10/Synology_DiskStation_-_vdSarDisk_3.png)

Add a new task brings the following screen:

[![Synology_DiskStation_-_vdSarDisk](images/Synology_DiskStation_-_vdSarDisk-300x241.png)](https://www.vdsar.net/wp-content/uploads/2013/10/Synology_DiskStation_-_vdSarDisk.png)

 

Root is the user (remember that you've created a SSH RSA Key in the /root/.ssh folder, that is because the script is started by Root in this task). enter the path to your script. In my case I've created the /volume1/Scripts shared folder where the script is. The tab 'planning' is probably 'schedule'  in English. Here you can determine how often the script should run.

**Make it an offsite solution**

I suggest to configure and test your setup while the RPi is connected to your local network. Once everything is working, do an initial sync too. The speed on your LAN is better than over the internet.

Once you bring the RPi to the remote location, you have to change your script on the Synology. Instead of the local IP adres you have to add the IP adres or Domain name of the remote location. In the remote location router you have to forward port 22 to the RPi. Port 22 is the SSH port.

Dre commented below (I didn't try this yet): If you want to use an alternative port btw (security wise), use the “-e ” (minus e) in the OPTIONS:

OPTIONS=”-avRz -e” And add “ssh -p $PORTNUMBER” to the perform rsync line:

rsync $OPTIONS “ssh -p 12345″ –delete –exclude-from=/volume1/Scripts/Exclude.txt $SRC $DEST >> $LOGFILE

**Final security suggestion**

SSH is open on port 22 which will be subject to a lot of attacks from the internet. That's why you have to setup a highly secure password. Maybe you should google a little on Raspberry Pi and security to see what I have missed.

Install Fail2Ban to block connections from IP addresses that have more than x-number of failed login attempts. Check [this page](http://www.bartbania.com/raspberry_pi/fail2ban-security-part-iii/) for the setup. After install it already works for SSH.\[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
