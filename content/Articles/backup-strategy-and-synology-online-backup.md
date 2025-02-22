---
title: "Backup strategy and Synology Online backup"
date: "2011-02-23"
categories: 
  - "howto"
  - "lifehacking-2"
  - "tech"
tags: 
  - "backup"
  - "internet"
  - "lifehacking"
  - "security"
  - "synology"
---

I'm happy to see that more users are starting to use NAS devices (Network Attached Storage) to store and share their data, music, photos and videos within a household. Many people choose for a setup with a RAID 1 configuration which means that they have installed 2 harddisks that hold a copy of each others data (mirroring). Within a RAID 1 configuration, one harddisk can fail while the other still holds the data. You replace the faulty drive and your system / NAS is up and running again without any dataloss (usually you can still use it while one drive is faulty).

This RAID 1 protection is one step in safeguarding your data but, depending on your needs, you might want to think about additional protection. Now you are asking, why should I? Because think about what will happen when lightning strikes ruining you electrical devices, your house catches fire or a virus on your computer that starts deleting all data on your NAS. When you delete data, it is also removed from a Raid 1 configuration.

**DO NOT UNDERESTIMATE THE RISKS !**

There are some additional measures you can take to avoid data loss:

- Create a backup on external HDD (electrical device that will die when lightning strikes!)
- Create a backup on CD/DVD/BluRay disks (your drive may die, but your disk will probably survive)
- Store the external HDD and/or CD/DVD/BluRay disks on another location (when your building burns down)
- Create an online backup

The first 3 options are probably no rocket science for you but the last one, create an online backup, might be.

I devide online backup in two area's.

1. Online storage services like dropbox, skydrive, strato Hidrive.
2. Online sharing services like i.e. Flickr, Picasa, etc

I have written an [article](https://www.vdsar.net/archives/177) before about using Flickr as a backup facility for your photos which you can find [here](https://www.vdsar.net/archives/177). Many other solutions are available like dropbox and Live Skydrive. In this article I want to focus more an a specific solution I use for backing up my data online. I describe a specific solution for the Synology NAS devices in combination with Strato Hidrive. This might inspire you to find a similar solution for you NAS device.

**My backup strategy**

_First I have to make a difference between online sychronization and online backup. A synchronization means that your data is always in sync. When you update a file, that updated version is available, the old version is gone. If you delete a file, the file will also be deleted from the online storage !_ _A backup means that a version of your data of a specific moment in time is available. This means, if you create a backup every day, you will have the old version of a file in the backup of yesterday and the new version of that file in the backup of tonight._

_Fortunately, depending on your synchronizations software, there are options to NOT delete files that are being deleted on the host system._

_**The above is important to understand.**_

My backup strategy consists of a RAID 1 setup, an additional external harddisk with a copy of the NAS data being synchronized every 2 days. An online synchronization of specific data folders without removal of deleted files is performed every night and periodically I create a backup of specific data on Bluray disks which I store remotely too. I recently upgraded to bluray because the amount of data became to much to use DVD's.

**How to setup your synology NAS with Rsync and Strato Hidrive**

I am using a Synology NAS DS207+ with DSM 3.0 installed. This should work the same on every Synology using DSM 3.0. The online storage I use is hosted at [Strato](http://strato.com/) which offers packages of 20-1000 GB of data. You need Rsync functionality that is offered starting at the 100GB package. Rsync is the synchronization tool that is build into the Synology.

First of all you need a Strato Hidrive with the appropriate size. Check out [strato.com](http://www.strato.com) and find Hidrive. Order the package (or Trial) with the appropriate size. Remember you need Rsync functionality that starts at the 100GB package!

In the **Hidrive** admin panel, create a new user account and assign it rights to use 'Rsync over SSH'. The directory that is being created for this user account is in my case /users/username/ I created a subfolder manualy that is named 'rsync' like: /users/username/rsync. You can do this using the filemanager of Hidrive. The online backup will be placed in this subfolder (it's optional because the synology creates a subfolder with the name of your Synology too).

In the Synology go to the admin panel and choose the dropdown list (top left corner) and select 'Create and restore backup' (I have the Dutch version so I don't know the exact English translations). Then choose to create a backup. You will see a wizard guiding you through the proces.

Enter a name of the backup (my online backup) and click next. Then choose 'Network Backup (rsync compatible server). (you see there is also an option to create an online backup to another synology NAS at i.e. a friends place).

Then enter servername or Ip addres: rsync.hidrive.strato.com BackupModule (path): /users/username/rsync Add your username and password of the account you created above.

I also flagged the encryption and compression option. I flagged the backup on block level too.

A very important option is the 'Do not remove backup files'. When you leave this unflagged, a file deleted from the NAS will also be deleted from the online storage. When you flag it, deleted files will remain on the online storage so you have a backup of the file. _So now and then I open the settings of the backup and unflag this option, have one backup made and flag it again. This makes that deleted files are indeed being removed. I only do this when I'm 100% sure that I don't need it anymore (when are you 100% sure??)_

You also have to select all folders that you want to synchronize to the online storage. I only backup the things I cannot recover like documents and photos.  Decide on this in relation to the costs of the online storage packages.

Then you have to select a backup schedule which should be depending on the frequency that you update your files. I do a daily backup because I expect changes every day and besides, when nothing has changed, nothing is being updated!

The same procedure can be used to create a regular backup on an external harddisk. In this case choose local backup instead of network backup!

With this article I hope to inspire you to think about your backup strategy. To many people have lost their data because of ignorance or slackness.
