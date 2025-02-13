---
title: "Raspberry Pi Open Monitoring Distribution setup guide"
date: "2015-01-02"
categories: 
  - "howto"
  - "tech"
tags: 
  - "computer"
  - "guide"
  - "linux"
  - "monitoring"
  - "nagios"
  - "omd"
  - "raspberry-pi"
  - "software"
coverImage: "Check_MK_vdSarICT-4.jpg"
---

![Running Check_MK Portal](images/Check_MK_vdSarICT-4-300x113.jpg)Post updated 29-11-2019. Checkmk is now owned / created by [Tribe29](https://tribe29.com/).

**_Check\_MK has been renamed to checkmk. I haven't used checkmk for a while, so the code examples below still contains the old name: Check\_MK. Read the manual, google and find out for yourself if the commands are still valid or that you have to rename those._** 

I use a setup of some Raspberry Pi's to monitor my own systems and some systems of my customers. My main goal is to be informed on system status (warnings and criticals) via one portal and preferably before my customers notice incidents on their systems.

![Raspberry Pi model](images/RPI-B-300x199.jpg)There is no need for expensive and energy consuming systems to do the monitoring. Some low budget and low power Raspberry Pi's do the job very nice. You can use more powerful Linux systems if you need to. This manual will probably still be useful.

First I started to use plain Nagios which is one of the most used systems in the industry, but it takes a lot of time to setup. It did work though. Then I found the Open Monitoring Distribution, OMD for short. This is a complete package of Nagios, Checkmk, PNP4Nagios, NagVis and Dokuwiki. The best part turned out to be CheckMK which offers a multisite interface, an automatic inventory of system services and so on. Start reading about [OMD](http://omdistro.org/) and [Checkmk](https://checkmk.com/editions.html) yourself.

This manual doesn't explicitly tell you when and how to forward ports on your firewall. I do mention the ports used. Just don't forget to forward ports when communicating between different locations ;-)

It did take me quite some time to get it up and running the way I wanted. A basic install isn't a challenge, but configuring secure connections between my site and my customers sites is something different. I tried to document all the steps I took. Some in detail, some a little less detailed. I believe in sharing so here is my manual. It might not be 100% perfect, but it should hand you some guidelines. Some Linux knowledge is useful. Read through the whole article first. Sometimes you need to read a little further to understand what I've written.

[Google](http://www.google.com) is my best friend and should be yours too when it comes to finding information. All information has been gathered by searching on Google, reading manuals and just doing. So if you get stuck, please check Google before asking.

Finally I like to thank everybody who has been working on [Nagios](http://www.nagios.org/), [Checkmk](https://checkmk.com/editions.html), OMD and the [port of OMD to the Raspberry Pi](https://labs.consol.de/blog/nagios/omd-1-00-raspberry-pi-ist-fertig/)!

Short description of my setup:

- **MonitorPi** is a Raspberry Pi running on my location. I will use it to monitor the systems (Portal) and configuring (adding/removing) hosts and so on.
- **CustomerPi** is a Raspberry Pi running on another location. This one is monitoring other systems on the customer site and is running an OMD install itself.
- **SomePi** is a Raspberry Pi running on another location too, but this one is not for monitoring. This one has a specific task like running some backup, sharing files, and so on. This SomePi is monitored directly from the MonitorPi.

Both the MonitorPi and the CustomerPi need OMD to be installed (you could skip the OMD part and only install LiveStatus on the CustomerPi, but that's your challenge ;-). (So SomePi doesn't need OMD!!)

## Setup OMD on your Pi's.

First do a clean setup of the Raspberry Pi and install the latest Raspbian. Once it is installed, continu:

`sudo raspi-config`

Resize the video memory to only 8 or 16 Mb, update the hostname and increase storage size. Reboot.

`sudo apt-get update sudo apt-get upgrade sudo rpi-update (update firmware) sudo passwd root (and enter a new root password. This enables Root user)`

Add OMD to the repository:

Updated 2-2-2015: I found OMD v1.21 for Raspberry Pi (ARMv6). Read [my Post](https://www.vdsar.net/update-omd-1-00-1-21-raspberry-pi/ "Update OMD 1.00 to 1.21 on Raspberry Pi") on how to install this new version.

Updated 3-7-2016: OMD v1.30 is available for Rasberry Pi 2 & 3 (ARMv7). Read [my post](https://www.vdsar.net/omd-v1-30-available-raspberry-pi-armv7/) on how to install this new version. Make sure you use Raspbian Jessie for this new version.

You don't need to install v1.00 first! The post replaces the next 6 lines below:

`su - (become root, using root wachtwoord) echo 'deb http://labs.consol.de/repo/stable/debian wheezy main' >> /etc/apt/sources.list gpg --keyserver keys.gnupg.net --recv-keys F8C1CA08A57B9ED7 gpg --armor --export F8C1CA08A57B9ED7 | apt-key add - apt-get update apt-get install omd-1.00`

Enter a new MySQL Root wachtwoord when asked for it. When finished you can create a new OMD site using:

`sudo omd create MyCorp _Take care, MyCorp is the name of the site you create and is Case Sensitive!! Choose a unique name for each Pi you setup._`

The site can be now started with

`omd start MyCorp`

The default web UI is available at **http://MonitorPi/MyCorp/** The admin user for the web applications is **omdadmin** with password **omd**. **For administration of this site use:**

`su - MyCorp`

`I guess the password is the same as the root password, otherwise reset the password with:`

`sudo passwd MyCorp`

Now you have OMD running, but it doesn't do much. Start monitoring the MonitorPi itself by installing Check\_MK\_Agent on it: You can find the most recent version at: https://checkmk.com/download.php. Find the latest version and use the link in the wget and dpkg command below. _Please remember: There is a difference between the Check\_MK Multisite (which is the webpage portal) and the Check\_MK\_Agent which is the agent running on a system to gather all the system information._

_Below Code is old. Pay attention that the URL of where to download the software has changed. Try to find you download link via the new site of checkmk: https://checkmk.com/download.php_

`sudo apt-get install xinetd cd ~ wget http://mathias-kettner.com/download/check-mk-agent_1.2.4p5-2_all.deb sudo dpkg -i check-mk-agent_1.2.4p5-2_all.deb`

You'll see a bunch of information once you try to run the agent with:

`./check_mk_agent`

Verify that the package installation generated the xinetd configuration file called "/etc/xinetd.d/check\_mk".

## Adding first Pi for monitoring

Once you've completed the setup of the MonitorPi you can add your first host to monitor.

Open the Check\_MK Multisite portal: http://monitorpi/MyCorp/check\_mk and login with 'omdadmin' and password 'omd'. On the left in the menu scroll down to the part that says: WATO Configuration. In that menu you'll find 'Host and Folders'. In there you can add a new host. The first host you add is MonitorPi with IP Address 127.0.0.1. Push button: 'save and go to service'. Have some patience and you'll see a list of all detected services. You'll also see a button on top with 'Save manual check configuration' . Click that one and all services are added for monitoring.

To add other systems you add the IP address of that system (and make sure check\_mk\_agent is installed on that system). For remote systems which you need to monitor over the internet, check the paragraph 'CheckMK via SSH' below.

## Install SSH Keys & New Users:

_You can skip this part if you like._ Create a new 'management' user on your Raspberry Pi. Using the original Pi is not really security best practice. Add SSH Key to enable login without password. You can find more info on SSH keys in one of my [previous posts](https://www.vdsar.net/rsync-backup-synology-remote-raspberry-pi/ "Rsync backup Synology to Raspberry Pi"). Read that post before continuing. Goal is to be able to login to your Pi without having to enter a password each time and to setup a new user other than the standard 'Pi'.

`sudo adduser johndoo sudo usermod -a -G adm,dialout,cdrom,sudo,audio,video,plugdev,games,users,netdev,input,spi,gpio vdsbeheer`

Now login as user  johndoo and add the public key, generated on the client computer, to the file: ~/.ssh/authorized\_keys of the user johndoo.

## Setup STUNNEL for secure Livestatus connections

I have a MonitorPi on my site and a CustomerPi on another location. Both running OMD of which I use Check\_MK Multisite to monitor all sites at once. Now the MonitorPi needs to get the Status information from the CustomerPi. This runs over TCP port 6557 and is unencrypted. To make this more secure I setup stunnel which creates a secure SSL/TLS tunnel between two non-encrypted services. I also chose a non standard port which is used. Instead of MonitorPi to connect over Port 6557 to CustomerPi, the MonitorPi will connect to itself on port 6557 where Stunnel will create a secure tunnel over internet to CustomerPi on port 12345. CustomerPi Stunnel will receive the data and send it to Check\_MK on itself port 6557. So Check\_MK won't notice it used Stunnel on anther port :-).

`sudo apt-get install stunnel4`

Enable stunnel by default.

On MonitorPi create a file /etc/stunnel/checkMK.conf with the following contents:

`pid = /var/run/stunnel.pid client = yes` \[fusion\_builder\_container hundred\_percent="yes" overflow="visible"\]\[fusion\_builder\_row\]\[fusion\_builder\_column type="1\_1" background\_position="left top" background\_color="" border\_size="" border\_color="" border\_style="solid" spacing="yes" background\_image="" background\_repeat="no-repeat" padding="" margin\_top="0px" margin\_bottom="0px" class="" id="" animation\_type="" animation\_speed="0.3" animation\_direction="left" hide\_on\_mobile="no" center\_content="no" min\_height="none"\]\[checkMK\] accept = 127.0.0.1:16557 connect = IP\_OF\_CUSTOMERPI:12345

In case you have multiple CustomerPi's, you have to create the above file for each CustomerPi. Each time you choose another portnumber in: "accept=127.0.0.1:16557". From the Check\_MK Multisite config you will each time connect to localhost (127.0.0.1) but the port number determines to which customerPi you connect. Because you have another IP\_OF\_CUSTOMERPI defined too, otherwise you won't connect to another Customer!

Next, on the customerPi create a file /etc/stunnel/checkMK.conf with the following contents:

`pid = /var/run/stunnel.pid cert = /etc/stunnel/cert.pem key = /etc/stunnel/key.pem` client = no \[checkMK\] accept = 12345

**The SSL key files are only used to secure the data, not for validation or authorization!**  

**<INSERT HOW to CREATE SSL KEY FILES>**

Enable Livestatus via TCP in the config utility on the CustomerPi.

`sudo omd config MyCorp`

## Distributed Monitoring

Now you've setup Stunnel on Both Pi's and enabled Livestatus over TCP you can setup Distributed Monitoring.

[![Distributed Monitoring](images/Check_MK_vdSarICT-300x201.jpg)](https://www.vdsar.net/wp-content/uploads/2015/01/Check_MK_vdSarICT.jpg)Go to http://monitorPi/MyCorp/check\_mk

_(note: Safari won't make the left menu bar scroll. Use Chrome instead!)_

Click on the image to get a readable version!

1. Choose Distributed Monitoring
2. Connect via TCP
3. Enter the port you used in the Stunnel CheckMK.conf file
4. When you click on a link inside the CheckMK Multisite portal, it needs to know where to go to. Use http when you haven't setup SSL for the site, otherwise use https.
5. Setup Replication. Make sure you add check\_mk/ to the URL. Also here http or https!

**Do this for each CustomerPi. You also have to add your MonitorPi once you start using distributed monitoring.  Choose for item 2: Connect to local site.**  **Item 4: http://monitorPi/MyCorp** **No Replication!**

Replication is cool. You can add hosts and services (and other config parameters like rules and users) from your MonitorPi. When you activate the changes it will upload the settings to all other Slave CustomerPi's too!!

##  Install email on Raspberry Pi

To send notifications by email you need to setup email on the Pi's. Do this on each Pi you want notifications send by email (the MonitorPi won't send the notifications related to a CustomerPi. The CustomerPi will send the notifications itself!!) `sudo apt-get install ssmtp sudo apt-get install mailutils sudo apt-get install mpack`

`sudo nano /etc/ssmtp/ssmtp.conf AuthUser=youruser@domain.nl AuthPass=***** FromLineOverride=YES mailhub=mail.yourdomain.nl:587 UseSTARTTLS=YES`

(also works with Gmail). You can test the mail configuration with:

`echo "sample text" | mail -s "Subject" username@domain.tld`

Now secure the mail configuration by limiting access to config files:

`sudo chown root:mail /etc/ssmtp/ssmtp.conf sudo chmod 640 /etc/ssmtp/ssmtp.conf sudo gpasswd --add username mail`

Now only root can change the file and members of the mail group can read the config. Username is the user that is used to run the OMD site, which is MyCorp in our example. For testing purposes, add your own user too (in this case johndoo) and reboot.

`sudo reboot now`

## Prowl Notifications in OMD

Prowl is a service available via [prowlapp.com](http://prowlapp.com) and enables sending messages to your smartphone. Create an account and get an API key.

Setup Perl on each Pi that needs to send notifications via Prowl. You can download the [prowl.pl](http://www.prowlapp.com/static/prowl.pl) script from the [API page](http://www.prowlapp.com/api.php) on the prowlapp site.

`sudo apt-get install libcrypt-ssleay-perl apt-get install libwww-perl libdbi-perl libdbd-mysql-perl libgd-gd2-perl`

Now create a new prowl\_script.sh which can be used by CheckMK:

`sudo nano /omd/sites/vdSarICT/share/check_mk/notifications/prowl_script.sh`

Enter below content to the script. The 2nd line is a desciption shown in CheckMK as notification method. The $NOTIFY variables are available in CheckMK. This script just adds some standard output from Check\_MK to the Prowl.pl script. You should read [this page](https://mathias-kettner.de/checkmk_flexible_notifications.html) too on notifications with Check\_MK.

`#!/bin/bash #Prowl script for CheckMK /omd/sites/MyCorp/bin/prowl.pl -apikey=$NOTIFY_PARAMETER_1 -application="$NOTIFY_HOSTALIAS $NOTIFY_HOSTADDRESS" -event="Host: $NOTIFY_HOSTSTATE, Service: $NOTIFY_SERVICESTATE" -notification="$NOTIFY_HOSTOUTPUT - $NOTIFY_SERVICEOUTPUT" -priority=1`

Now make your script executable: `sudo chmod +x prowl_script.sh`

Make sure to place the prowl.pl script  in the folder which is named in the above script. In this case: /omd/sites/MyCorp/bin/. Make it executable too (chmod +x prowl.pl)

[![Notifications with CheckMK](images/Check_MK_vdSarICT-2-300x217.jpg)](https://www.vdsar.net/wp-content/uploads/2015/01/Check_MK_vdSarICT-2.jpg)

To configure your notifications:

1. Go to users, create a user, provide an email address and
2. select Flexible Notifications
3. select your Prowl notifications script (this should be the text of the second line of you prowl\_script.sh script!)
4. add your prowl API-Key as **first** parameter. Each user can have it's own Prowl account and Prowl API key :-).

## Disable PING Host checks

Once you configure a host to monitor that is behind a firewall and will not respond to a ping you will continiously find it in critical status (unavailable). Fix it this way:

Find your main.mk file (/omd/sites/MyCorp/etc/check\_mk/main.mk) add this code to the file:

`extra_host_conf["check_command"] = [ ( "check-mk-dummy", ["noping"], ALL_HOSTS ), ]`

Each host tagged as 'noping' will use this dummy check.

[![NoPing Config](images/Check_MK_vdSarICT-3-300x162.jpg)](https://www.vdsar.net/wp-content/uploads/2015/01/Check_MK_vdSarICT-3.jpg)

Now go to CheckMK, WATO, Host Tags and edit the tag group: AGENT\_Type. Add an option with tag noping. See Picture. Now you can select this option 'noping' when adding or modifying a host.

## Install Check\_mk\_agent on Linux systems.

To monitor a Linux system, you need to install the check\_mk\_agent on it. The Raspberry Pi is running Linux too, so the same applies to each system you want to monitor. There is a check\_mk\_agent available for Windows too.

You can find the most recent version at: http://mathias-kettner.com/check\_mk\_download.html. Find the latest version and use the link in the wget and dpkg command below.

`sudo apt-get install xinetd cd ~ wget http://mathias-kettner.com/download/check-mk-agent_1.2.4p5-2_all.deb sudo dpkg -i check-mk-agent_1.2.4p5-2_all.deb`

You'll see a bunch of information once you try to run the agent with:

`./check_mk_agent`

Verify that the package installation generated the xinetd configuration file called "/etc/xinetd.d/check\_mk".

## CheckMK via SSH (for SomePi example)

So far we talked about MonitorPi and CustomerPi. Both running it's own OMD instance which come together in the Check\_MK Multisite page on the MonitorPi.

Let's look at the situation with SomePi. SomePi is a Raspberry Pi (or other Linuxserver) running at a remote site. This Pi is not for monitoring purposes, but running something else, maybe a website, filesharing, etc. We want to monitor the performance and status of this SomePi.

Just as with every other Linux, Windows or Raspberry Pi you need to install the check\_mk\_agent, see previous chapter.

To secure the traffic between the MonitorPi and SomePi we will use a secure SSH connection.

Find your main.mk file (/omd/sites/vdSarICT/etc/check\_mk/main.mk) and add this code to the file:

`datasource_programs=[ ( "ssh -l root -i /etc/check_mk/check_mk_MyCorp.key IP_OF_SOMEPI -p222",[ 'HostName' ]), ]`

I don't use the standard SSH port on remote Pi's. Portscanners will find that port very quickly and attacks will happen all day. I usually forward another external port like 222 to internal port 22 in the router/firewalls. For now, just leave out the -p222 and just use port 22. HostName is the name you give the system in the CheckMK configuration when you add a new host to monitor. The config will understand that instead of using a normal Check\_mk\_agent connection via port 6556, it needs to use the ssh connection you defined here.

Add multiple rows in this datasource\_programs definition for each external 'SomePi'.

You need to enable password less login via SSH. Therefore you need to use SSH Key's. Follow the next steps:

Create a Keypair on the MonitorPi:

`cd /etc/check_mk sudo ssh-keygen -t rsa` use a recognizable name like: check\_MK\_MyCorp.key. A \*.key and \*.pub file is created!

`sudo chown MyCorp check_mk_MyCorp.key chmod 400 check_mk_MyCorp.key`

Now go to SomePi and enable the Root user:

`sudo passwd root (enter new password) su - cd ~/.ssh (or create .ssh folder for root) nano authorized_keys`

put this command in the file: command="/usr/bin/check\_mk\_agent" and append the content of check\_mk\_MyCorp.pub from the MonitorPi to it. (Just copy paste) This command makes sure only check\_mk\_agent can be executed via SSH.

So the line in authorized\_keys will look like:

command="/usr/bin/check\_mk\_agent" ssh-rsa AAAAB3Nza........

Now back to the MonitorPi and create a new host in CheckMK, WATO. The name should be equal to the HostName used in the main.mk datasource\_programs statements!

`su - MyCorp (user running the site) ssh -l root -i /etc/check_mk/check_mk_MyCorp.key hostname -p port`

Running the above ssh command as the siteuser 'MyCorp' makes sure it is added to the known\_hosts file on the MonitorPi. Once this is done, you should get the output of Check\_mk\_agent via SSH from the remote Pi. 

## Next steps

You should enable SSL on Apache2 on the MonitorPi when you want to access this Pi from the Internet. Otherwise all traffic will be unencrypted.

Using the WATO Configuration in Check\_MK you should at least change the password of user omdadmin. Even better, create a new user and strong password.

\[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
