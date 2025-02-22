---
title: "Domotica Gateway"
date: "2012-12-04"
author: Alexander
---

## DIY - Domotica Gateway

The **Domotica Gateway (DG)** is built around an **Arduino Mega 2560** with an **Ethernet shield**. The main goal of the DG is to interface with the outside world using:

- Digital input and output ports
- **RFM12b 868Mhz** transceiver
- **434 Mhz transmitter and receiver** (for remote switches)
- Analog ports

*(The RFM12b 868Mhz transceiver was added at a later stage because it can send and receive data and is compatible with Attiny84 and TinyTX sensors. The 434Mhz transmitter is still used to control remote switches. The receiver is connected to capture remote switch signals but is not actively used now.)*

### Why a Dedicated Arduino?

I chose to use a dedicated Arduino to avoid interference with the **solar power measurements** on the Solar Monitor Arduino. The **Raspberry Pi** has a limited number of digital ports and operates at **3.3V**, while most of the sensors and equipment I use require **5V**. To address this, I created a dedicated box that allows communication between:

- The **Solar Monitor Arduino**
- The **Raspberry Pi**
- Websites and telnet sessions over Ethernet

This page describes **my setup**—let it inspire you to build your own!

## Main Functions of the Domotica Gateway

- Communicate with other systems using simple **Ethernet commands**
- Interface with **iOS Arduino Manager**
- Switch **relays**
- Control **434Mhz wall outlet switches**
- Receive **434Mhz remote control signals** to track switch status
- Send data to a **wireless LCD display** over **868Mhz**

### Communicating with Other Systems

Two **Ethernet server processes** listen for incoming connections, allowing up to **four simultaneous connections**:

1. One server process listens on **port 23** for **telnet** or simple text commands.
2. The other listens on another port for **iOS Controller** connections (compatible with **Arduino Manager**).

Example commands:

- `LampA_ON`, `LampA_OFF` → Switch **Light A** on/off
- `TX868=TXT,This is text.` → Transmit "This is text" over **868Mhz**
- `TX868=V1,300,340,243,235` → Send predefined values to the **LCD display**

The DG also sends **light status updates** to the **wireless LCD display**, transmitting variable values over the air for processing by the receiver.

### Controlling Relays

To switch relays, you need to **define them in the source code** and connect them to the **Arduino digital ports**. If a device is too far to be connected via relay, you can use **cheap 434Mhz remote control devices** instead.

In the Netherlands, brands like **Klik Aan, Klik Uit, Action, Blokker, and Elro** work well. You can find them at Action for **€9.99** for a pack of three.

### Using a 434Mhz Receiver for Remote Switch Status

I added a **434Mhz receiver** to the Arduino to receive remote control signals from an **Action kit remote** (set to a different code than the wall outlets). The idea was to:

1. Interpret the signal from the remote.
2. Switch the wall outlets using **434Mhz**.
3. Keep track of the actual switch status.

This would ensure that the **Arduino always knows the status** of the switches, preventing someone from manually switching a wall outlet without the Arduino registering it.

Unfortunately, the setup proved **unreliable**, possibly due to the receiver's placement, so I stopped using it.

### Communicating with an iOS Device

I use the **Arduino Manager** app, which provides:

- **Switches, displays, graphs, and LEDs** on an iOS device
- A simple library to connect an **iPhone or iPad** to the Arduino
- Commands that can be sent **from iOS to Arduino**, with status updates sent back

### Switching Relays

To switch relays, buy a **relay board** on **eBay**. They usually contain **1, 4, or 8 relays**, each connecting to a **digital port** on the Arduino.

- Set a **digital port to 1** (or 0, depending on the board) to activate the relay.
- Switch heavy loads like **220V lights, coffee machines, and TVs**.

#### DIN Connector Pin Layout (for my reference)

For a **4-relay board**, I used a **6-pin DIN connector**:

1. **5V**
2. **Relay 1** (Pin 42)
3. **Relay 2** (Pin 44)
4. **Relay 3** (Pin 46)
5. **Relay 4** (Pin 48)
6. **GND**

### Remote Control Wall Outlets

To control wall outlets:

- Buy a **cheap 434Mhz transmitter and receiver** (search eBay for **433Mhz** versions).
- Use an **Arduino library** to send remote control signals.
- Connect the **transmitter to PIN 12** on the Mega.
- Connect **PIN 13 to an LED** that lights up when data is sent.

I previously used the **same transmitter** for sending data to **wireless LCD displays** using the **VirtualWire library** but have now replaced this with **RFM12b 868Mhz transceivers**.

### RFM12B Wireless Transceivers (868Mhz)

I replaced the **VirtualWire library** and **cheap 434Mhz transmitters** with the **RF12 library from JeeLib** and **RFM12b transceivers**. Since these modules operate at **3.3V**, while the Arduino runs at **5V**, I recommend using the **RFM12b board from JeeLabs**.

*(I had one module running at 5V for three weeks, but it's not recommended!)*

RFM12b modules are available in **434Mhz, 868Mhz, and 915Mhz**. I chose **868Mhz** because **434Mhz** was already in use for my switches. The **915Mhz frequency is not allowed in my region**.

For more details, check out the **RF12 library** and search Google for related documentation.

---

### Download

![[attachments/Arduino Collection RFM12b - Febr 2013.zip]]
![[attachments/Libraries for collection febr 2013.zip]]


This package includes:

- **Energy Meter**
- **Domotica Gateway**
- **SensorBox**
- **Wireless LCD Display**

All components work together seamlessly. The **included libraries** are as they exist on my system—they may not be the most recent versions but should function correctly with the provided source code.

> ⚠️ The source code is not "monkey-proof"—you'll need to tweak it to fit your setup!

