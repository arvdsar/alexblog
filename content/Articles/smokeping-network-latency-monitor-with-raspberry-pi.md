---
title: Smokeping - network latency monitor
date: 2018-12-27
---

_This post was still in my drafts for maybe 2 years now. Not sure if it is complete, but it did remind me of the nice tool 'SmokePing'._ 

I'm using Open Monitoring Distribution as a decent monitoring setup on my local and some customer networks. It isn't a 5 minute setup though and sometime you just don't need this many features.

Somewhere I found an article writing about Smokeping and I gave it a shot on a Raspberry Pi. It does what it says, it pings to hosts and maintains a decent graph on the response times. It has some additional features like HTTP, SSH tests and even a master/slave setup.

I've installed it on a Raspberry Pi 3 which I connected directly to my main cable modem/router. I experience some outages so now and then and this way I can easily determine if this is caused at the router or somewhere in my local network.

Get yourself a Raspberry Pi (preferably a 2 or 3 to get some performance) and install Raspbian OS. When you have it running you do the following:

sudo apt-get update  
sudo apt-get upgrade  
sudo apt-get install smokeping sendmail  _(You really need sendmail too!!)_

(on a Raspberry Pi 3 I needed the below  apache config too. On an older install it was just working without these apache commands)  
cd /etc/apache2/conf-available  
ln -s ../../smokeping/apache2.conf smokeping.conf  
a2enconf smokeping  
a2enmod cgid  
service apache2 restart
