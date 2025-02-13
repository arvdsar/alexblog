---
title: "Lightroom Catalog Sync using Dropbox selective sync"
date: "2012-05-01"
categories: 
  - "howto"
  - "lifehacking-2"
  - "photography"
  - "tech"
tags: 
  - "catalog"
  - "dropbox"
  - "lightroom"
  - "lion"
  - "mac-os-x"
  - "sync"
---

A while ago I wrote a [post](https://www.vdsar.net/archives/989 "Lightroom Catalog Sync with Dropbox") about how I use [Dropbox](http://db.tt/fGigLDp) to sync my Adobe Lightroom catalog across multiple computers. This worked fine until I started using a Mac OS X Lion system, actually at the moment of writing I want to sync between two Mac OS X Lion systems. _(The next section contains useful info for Windows users too!)_

Maybe you should read my [previous post](https://www.vdsar.net/archives/989 "Lightroom Catalog Sync with Dropbox") before reading the next section.

It seems that Mac OS X handles symbolic links a little different than Windows 7 does. On Windows I stored the catalog in the Dropbox folder and created a symbolic link to another location on my harddrive, let's say c:/lightroomcatalog. By doing this I managed to get the Lightroom previews cache folder to be created in c:/lightroomcatalog and NOT being synced to Dropbox. The catalog itself was synced to Dropbox because of the symbolic link.

<!--more-->On Mac OS X though, I noticed that although I had created a folder like /lightroomcatalog and opened the alias or symbolic link created in that folder, Lightroom was actually opening the catalog file in the Dropbox folder. It turned out that the previews folder was now created in the Dropbox folder too and not in /lightroomcatalog.

One thing you don't want on Dropbox is your previews folder because it becomes large and it has no use to have it there.

The solution is even simpler than expected. In Dropbox is an option to exclude specific folders from syncing. So now I just point lightroom to open the actual catalog file in Dropbox and it does create the previews folder. Then I close Lightroom, go to preferences of Dropbox and in the tab 'advanced' choose 'selective sync'. Push the 'advanced options' button and exclude the lightroom preview folder from syncing. Next go to dropbox website and manually delete the folder from there too. I expected it to be deleted but it is not.

You have to exclude this folder on all systems where you have Lightroom running. Otherwise system 2 will still sync the folder.

Conclusion: Keep in mind that Dropbox has a feature called 'Selective Sync'  and you can exclude folders within Dropbox folder that you don't want to sync!! New folders added in Dropbox folder are synced by default.

Get your free Dropbox account using [this link.](http://db.tt/fGigLDp) It offers both you and me additional free storage!
