---
title: "Notification when host unavailable"
date: "2013-01-05"
categories: 
  - "howto"
  - "gadgets"
  - "lifehacking-2"
  - "tech"
tags: 
  - "cloud"
  - "domotica"
  - "ipcam"
  - "pushingbox"
  - "python"
---

I needed a solution to check every x-minutes if my IP camera is still online.

I use the [Pushingbox.com](http://www.pushingbox.com) service to send a notification when a certain host is not available. Checkout Pushingbox.com to see which kinds of notification services they offer. At least a notification to email and Prowl! is possible.

I've combined the python script from the French blog site: [GuiguiAbloc](http://blog.guiguiabloc.fr/index.php/2012/02/22/pushingbox-vos-notifications-in-the-cloud/comment-page-1/) with another script to regularly check if a specific service is available and when not, to send a notification via Pushingbox.

[The script](https://www.vdsar.net/wp-content/uploads/2013/01/hostnotify.py_.zip) expects the URL to check as an argument, i.e.: python hostnotify.py http://192.168.1.34:8080

I have not tried all kind of services, but for HTTP services it works. I use this script to check every x-minutes if my IP camera is still online. When the build in webservice of the camera is not available, I receive a notification via Pushingbox. This script is more reliable then doing a PING to a network address. To check regularly, add the script to the crontab of your system and execute the script every x-minutes. The crontab should be something like this for every 5 minutes:

```
*/5 * * * * /home/Python/hostnotify.py http://192.168.1.34:8080
```

Make sure you setup a scenario on Pushingbox.com and add the DEVID of the scenario to the source code.

_Actually, in my setup I've included source code that besides sending a notification, it also sends a command to my Domotica Gateway which switches the camera off and on to do a reset._

