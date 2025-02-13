---
title: "Phone notifying doorbell with Pushingbox"
date: "2012-12-09"
categories: 
  - "gadgets"
  - "tech"
tags: 
  - "arduino"
  - "domotica"
  - "lifehacking"
  - "pushingbox"
  - "security"
---

The sound of our regular doorbell isn't heard everywhere in the house. Also, sometimes you know that somebody has been at the door but you don't know who. I found the [article](http://makeprojects.com/Project/Notifying+Doorbell+with+PushingBox/2165/1) below in which especially [Pushingbox.com](http://www.pushingbox.com) took my interest.

Pushingbox is an online service which you can trigger from an Arduino microcontroller very easy. Pushingbox will execute a specified scenario in which it can send messages to email, twitter, Prowl!, Android notifiers and so on. It is also capable of loading content from an URL which makes you can download an image from a webcam (or IP Cam) and attach it to email.

<!--more-->

Many online services offer some kind of email interface. You can have your own Facebook.com email address and send a notification including image to Facebook from pushingbox. Or send the same email to your Evernote email and create a logbook with images of everybody at your door on Evernote. Many telecom operators offer email to SMS gateways but when using a smartphone you don't need that.

I already have a Foscam IP camera pointed at the door, so it was a small step to hook it up in Pushingbox. Use the following URL in the scenario configuration (check for steps the included [article](http://makeprojects.com/Project/Notifying+Doorbell+with+PushingBox/2165/1) below). http://URL:PORT/snapshot.cgi?user=USERNAME&pwd=PASSWORD

So, push my doorbell and a picture of you is send to my email, Facebook and [Evernote](http://www.evernote.com). A [Prowl](http://www.prowlapp.com) notification appears on my iPhone and...... there is some jingle bells tune (just for Christmas) playing from my [Wireless LCD Display](https://www.vdsar.net/diy-wireless-lcd-display/ "DIY – Arduino wireless LCD Display").

I would prefer to connect the doorbell switch using wires to the Arduino, maybe with using an optocoupler. For now I bought a 7 Euro wireless doorbell from [Elro DB280](http://www.elro.eu/products/category/Deurbellen/draadloze_deurbellen/batterijen2/draadloze_deurbel_cambridge) at the Gamma. It's a 3 AA Battery powered doorbell station (3 x 1.5volt = 4.5 volts) which can be connected to the 5 volt power of the Arduino. I took apart the receiver and connected one of the wires of the speaker (the one that is not connected to the red + wire) to an analog pin of the Arduino. When the voltage on that pin changes, it knows somebody pushed the wireless doorbell button. There is another solution too. I already have a 434Mhz receiver in the [Domotica gateway](https://www.vdsar.net/diy-domotica-gateway/ "DIY – Domotica Gateway") that is capable of receiving signals for remote switching like the "Klik aan / Klik Uit" and others from Blokker, Action and Elro. It turned out that the doorbell switch also sends a compatible signal which can be decoded with the [ReceiveSwitch](http://randysimons.com/overige/browsable/433MHz/ArduinoRemoteSwitchLibrary.7z) library.

Currently I use the doorbell receiver connected to an analog port. I experienced it to be more reliable at the moment.

The doorbell is connected to my Domotica gateway. The Domotica gateway triggers Pushingbox.com and also wireless sends a command to the Wireless LCD Display. A message will appear on the LCD and some tunes are played.

<script type="text/javascript" src="https://cacher.dozuki.net/static/embed/ifixit-embed.3.js#id=2165&amp;site=makeprojects.com" data-dozuki-embed="3">// <![fusion_builder_container hundred_percent="yes" overflow="visible"][fusion_builder_row][fusion_builder_column type="1_1" background_position="left top" background_color="" border_size="" border_color="" border_style="solid" spacing="yes" background_image="" background_repeat="no-repeat" padding="" margin_top="0px" margin_bottom="0px" class="" id="" animation_type="" animation_speed="0.3" animation_direction="left" hide_on_mobile="no" center_content="no" min_height="none"][CDATA[ <div></div> // ]]></script>

[Notifying Doorbell with PushingBox](http://makeprojects.com/Project/Notifying+Doorbell+with+PushingBox/2165/1)\[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
