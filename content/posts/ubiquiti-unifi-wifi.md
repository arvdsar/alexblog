---
title: "Ubiquiti Unifi WiFi"
date: "2019-01-05"
---

Over the past years I've used several brands of WiFi accesspoints. Way back I started with one of the first Cisco 802.11b accesspoints with only 11mbit. Meanwhile accesspoints of Linksys, Dlink and more recently the Apple Airport Express accesspoints have been used. Actually they all offered wifi and at the time of use an appropriate speed related to the internet connection.

At a certain moment I moved to Apple Airport Express with the expectation that roaming between the accesspoints would work properly. I have an accesspoint on each floor of our house. Actually, the Apple Express worked quite well, just like everything of Apple, it just works.

The Apple Airport Express was getting slow and I found some Linksys WAP600N accesspoints which I could try. They worked faster, but roaming was not very good. The connection was kept as long as possible, while a much stronger signal was already available from a more nearby accesspoint. Transfer speeds were not optimal in that case. so time to move on.

Nowadays the Ubiquiti accesspoints are mentioned when people ask for decent network equipment, so I gave it a shot.

Since a couple of weeks I have an Ubiquiti UAP AC Lite on the ground floor and an UAP AC LR (Long Range) on the 1st floor. Ubiquiti accesspoints can work standalone but you can also use the Unifi controller software (or cloud key). I run the Unifi controller software in a Docker container on my Synology NAS. Using the Unifi software you can setup and monitor your Ubiquiti accesspoints. It also offers a guest portal, vlan and many more options. And for what I know it is this software that makes the interaction with the accesspoints flawless!

I can say that I'm very happy with the Ubiquiti setup and I'm going to replace all accesspoints with new ones from Ubiquiti.

While before my devices remained connected to an accesspoint that did not offer the best signal strength, this is solved by Ubiquiti. As soon as I move from the ground floor to the 1st floor the device is forced to connect to the accesspoint with the stronger signal. So my devices are always connected to the accesspoint with the best performance.
