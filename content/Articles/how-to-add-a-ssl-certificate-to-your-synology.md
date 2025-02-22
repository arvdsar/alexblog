---
title: "How to add a SSL certificate to your synology!"
date: "2010-02-22"
categories: 
  - "howto"
tags: 
  - "security"
  - "ssl"
  - "synology"
---

This post describes how to add a SSL Certificate to the synology NAS device. (tested on DS207+ and DS209 II) _I was amazed how many post on the internet can be found, but none of all are a complete description on how to do this !_

\- Make sure that Telnet access is enabled (Management Menu, Terminal, enable Telnet) - Within one of your shared folders on the synology, create a new folder. _i.e.: You have a shared folder like \\\\ipaddress\\generic, create a subfolder like: \\\\ipaddress\\generic\\certificate_ Login to your synology using telnet: **telnet ipaddress** login using username: root and your admin password

<!--more-->

On the prompt you type the following: **cd /usr/syno mkdir ssl cd ssl wget [http://123adm.free.fr/home/pages/documents/syno-cert\_fichiers/openssl.cnf](http://123adm.free.fr/home/pages/documents/syno-cert_fichiers/openssl.cnf)**

_The last command downloads the openssl.cnf to your ssl directory._ Then we have to create the private key and some certificate request file (\*.csr): **cd /volume1/generic/certificate** (where generic/certificate is some folder you created)

**openssl genrsa -des3 -out some.key 2048 openssl rsa -in some.key -out some.nopass.key openssl req -nodes -new -key some.key -out some.csr** _Some info will be requested - Look at the end of this document how to fill this in!_

(the latter creates the csr file which you have to use to get your certificate from some SSL provider. If you get some error telling you that the openssl.cnf file is missing, then the wget above failed !) **Now you have some files in your shared drive: \\\\ipaddress\\generic\\certificate - some.key - some.nopass.key (without password) - some.csr** You can access those files like you always access your files on the synolgy using the filemanager or windows explorer.

Go to some site where they sell SSL certificates and follow the instructions. When they ask you to provide your csr information, open the **some.csr** on your synology, copy and paste the info into the website. Probably you can then check what's in the certificate request on the site. The site will deliver a **something.CER** file which is your certificate. Now go into the management tool of the synology, go to webservices and click the button 'import certficate'.

**Upload the some.nopass.key as your private key Upload the something.CER file as your certificate.**

The webservice will reboot and now your certificate should work (when accessing the synology using HTTPS !)

What to enter when creating the csr file, just an example ! Country Code: NL (2 letter code) Province / state: Noord Holland Locality: Amsterdam city Organisation: Company Name Organisation Unit: IT Departement Common Name: data.website.com (Enter your full qualified domainname here) Your Email: [info@website.com](mailto:info@website.com)

next to questions you can answer with 'ENTER'. (as far as I know)
