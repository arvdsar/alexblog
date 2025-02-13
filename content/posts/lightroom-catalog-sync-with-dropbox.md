---
title: "Lightroom Catalog Sync with Dropbox"
date: "2012-03-22"
categories: 
  - "howto"
  - "lifehacking-2"
  - "photography"
  - "tech"
tags: 
  - "dropbox"
  - "lightroom"
---

Adobe Lightroom is not a network enabled application. You can perfectly store your images on a network storage location (speed might become an issue) but the Lightroom catalog has to be on your harddrive.

When you want to use Adobe Lightroom on multiple computers, it's always a hassle to keep your Lightroom catalog in sync. Lightroom relies heavily on the catalog. The catalog contains references to your photos and holds all adjustments to your photos.

When you want to use Lighroom on multiple computers, lets say your PC and notebook, you always have to copy your catalog file from one system to the other. And someday it will go wrong. That day you will copy the older version of the catalog over the most recent version.

Dropbox, an online file storage and sychronisation service is a perfect solution to prevent this. I believe there are multiple articles written about Lightroom Catalogs and Dropbox, but those usually have one disadvantage, they also store all 'previews' on Dropbox. You will run out of space soon.

This article describes how I've setup Lightroom in combination with Dropbox AND your images stored on some kind of network drive.

<!--more-->

So first you have to get yourself a free [dropbox](http://db.tt/L4REJC7) account. Use [this link](http://db.tt/L4REJC7) and we both get an addional 250 MB storage as a bonus ;-). Install the Dropbox Client on all systems that you want to sync your files with, but for now at least on the systems where you have Lightroom installed. For this article my assumption is you use a PC and Notebook, but you can do it on as many systems as you like.

Assumption: You have your images files stored on a network drive so the images are available from all your systems. I expect you have this setup already and just want an efficient way to sync the Lightroom Catalog.

As you will see, the Dropbox client will create a folder 'Dropbox' on your system. All files and folders in that Dropbox folder will be synced between all systems. The benefit of Dropbox is that the files are stored on your harddrive AND online at Dropbox. So you don't have to worry about internet connection speed.

Now go to the folder where you have stored your Lightroom catalog. You will see that besides the catalog file (\*.cat) there are some other folders with Previews. If we would move the whole set to Dropbox your dropbox would run out of space soon.

**First of all, make a backup copy of your lightroom catalog file. Just in case something goes wrong!**

Now download and install [Link Shell Extention](http://schinagl.priv.at/nt/hardlinkshellext/hardlinkshellext.html). You can find it at the end of [this](http://schinagl.priv.at/nt/hardlinkshellext/hardlinkshellext.html) page.

Now create a folder 'Lightroom Catalog' inside your Dropbox folder. Move your Lightroom catalog file inside that new folder. Now the lighroom catalog is stored in Dropbox. (DO NOT START LIGHTROOM YET!). Make sure the catalog is not in your original folder on your harddrive anymore (otherwise rename it to something as a backup).

Go to the Dropbox/Lightroom Catalog folder and right click on your catalog file. Choose 'Pick Link Source'. (if you don't see 'Pick Link Source' then you have not installed Link Shell Extention correctly). Next go to your original folder and inside that folder (where your catalog was before) right click and choose 'Drop As - Symbolic Link'. You will see a shortcut to the Lightroom catalog in your dropbox folder is created.

What has happened? You have moved the LR Catalog to Dropbox and created a symbolic link at the original location.

Now you start Lightroom and you will notice that Lightroom will start normally. Do something in Lightroom that modifies a photo. Now you will see that the Dropbox icon in your taskbar will start synchronizing.

Remember: NEVER start Lightroom on more than 1 system at a time, otherwise a sync conflict will occur. Also after closing Lightroom, give Dropbox some time to sync the catalog file before opening Lightroom on the other system.

What I've noticed is that Dropbox saves a history of changes in a hidden 'Cache' folder. Because every tiny change is written to the database you get hundreds of history files in that cache folder making you run out of space. 1. You can delete the contents of that Cache folder (it's inside your dropbox folder) 2. Better, before starting lightroom rightclick on the Dropbox Icon in your taskbar and 'Pauze Sync'.  Do your thing in Lightroom and when finished, 'Resume Sync'.  Now the most recent catalog is synced with Dropbox.

\*So when you notice that your harddrive is running out of space quickly (30Gb in an hour!!) you have not paid attention to point 1 and/or 2 above!!

You have to create the symbolic link on all your systems and actually it doesn't matter if you have stored the catalog in another folder. Just symbolic link the catalog from dropbox to your original location of the catalog on that specific computer!

Because we used a symbolic link, the preview folders remain on your harddrive and are not moved to Dropbox! This would have happend when we pointed Lightroom directly to open the catalog from within the Dropbox folder.

TIP 1: I've also stored my plugins into a folder 'Dropbox/Lightroom Plugins'. I configured Lightroom to open Plugins from that folder directly, without using Symbolic links. One benefit of the Plugins in Dropbox is that the configuration of the plugin is usually available on all systems too and all systems use the same version!

An article with more information on how to store stuff outside your dropbox folder can be found [here](http://lifehacker.com/5154698/sync-files-and-folders-outside-your-my-dropbox-folder)

TIP 2: I create a Lighroom Backup from Lightroom everytime I exit Lightroom. I save this backup on my local harddrive, just in case something goes wrong in Dropbox sync!
