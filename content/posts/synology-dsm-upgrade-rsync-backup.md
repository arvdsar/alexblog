---
title: "Synology DSM 5.1 upgrade and Rsync Backup"
date: "2014-11-09"
categories: 
  - "howto"
  - "tech"
---

After upgrading my Synology from DSM 5.0 to 5.1 I noticed that Rsync from my Macbook to the Synology didn't work anymore. Read [my post](https://www.vdsar.net/rsync-backup-mac-os-x-synology/ "Rsync backup Mac OS X to Synology") on how to set Backup from Macbook to Synology using Rsync. To fix the issue was quite simple:

In the Synology DSM go to the config screen, choose Backup and Replication, Backup Services and enable Network backup service. I only have a Dutch screenshot:

[![Synology DiskStation Enable Network Backup Service](images/Synology-DiskStation-vdSarDisk-300x226.png)](https://www.vdsar.net/wp-content/uploads/2014/11/Synology-DiskStation-vdSarDisk.png)

I'm not sure if I had this enabled on DSM 4 or 5 too and that it was disabled during upgrade to DSM 5.1 or it is a new setting.
