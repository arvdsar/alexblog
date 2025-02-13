---
title: "Doorbell to Smartphone"
date: "2012-12-09"
author: Alexander
---

## DIY - Doorbell to Smartphone

The sound of our regular doorbell isn't heard everywhere in the house. Also, sometimes you know that somebody has been at the door, but you don't know who. I found the article below, in which **Pushingbox.com** particularly caught my interest.  

[Pushingbox](http://www.pushingbox.com) is an online service that can be easily triggered from an Arduino microcontroller. It executes predefined scenarios to send messages via email, Twitter, Prowl, Android notifiers, and more. Additionally, it can load content from a URL, enabling the download of an image from a webcam (or IP cam) and attaching it to an email.  

Many online services offer an email interface. For instance, you can use your **Facebook email address** to send a notification with an image directly to Facebook from Pushingbox. You can also send the same email to your **Evernote email**, creating a logbook with images of everyone who visits your door. While some telecom providers offer email-to-SMS gateways, using a smartphone eliminates the need for such services.  

I already have a **Foscam IP camera** pointed at the door, so integrating it with Pushingbox was straightforward. Use the following URL in the scenario configuration (refer to the steps in the article below):

http://URL:PORT/snapshot.cgi?user=USERNAME&pwd=PASSWORD


Now, when someone presses the doorbell:  
- A **picture** is sent to my **email, Facebook, and Evernote**.  
- A **Prowl notification** appears on my **iPhone**.  
- A **jingle bells tune** plays on my **Wireless LCD Display** (just for Christmas!).  

### Connecting the Doorbell to Arduino  

I prefer connecting the doorbell switch using wires to the Arduino, possibly with an **optocoupler**. However, for now, I bought a **7 Euro wireless doorbell (Elro DB280)** at **Gamma**. This **3 AA battery-powered** doorbell station (3 x 1.5V = 4.5V) can be connected to the **5V power of the Arduino**.  

I disassembled the receiver and connected one of the speaker wires (the one *not* connected to the red + wire) to an **analog pin of the Arduino**. When the voltage on that pin changes, the system detects that someone has pressed the wireless doorbell button.  

### Alternative Solution  

Another option is using a **434MHz receiver** in my **Domotica gateway**. This receiver can handle remote switching signals like **"KlikAanKlikUit"** and similar systems from **Blokker, Action, and Elro**. It turns out that the **doorbell switch sends a compatible signal**, which can be decoded with the **ReceiveSwitch** library.  

Currently, I use the **doorbell receiver connected to an analog port**, as I have found it to be more reliable.  

### Integration with Domotica Gateway  

The **doorbell is connected to my Domotica gateway**, which:  
1. Triggers **Pushingbox.com**  
2. Sends a **wireless command** to the **Wireless LCD Display**  
3. Displays a message on the **LCD screen** and plays a tune  

## Conclusion  

With **Pushingbox** and some simple hardware modifications, I’ve transformed my doorbell into a **smart notification system**. Now, whenever someone rings the bell, I receive a **picture notification**, a **smartphone alert**, and even a **musical jingle**!  

---

### Notifying Doorbell with Pushingbox  
