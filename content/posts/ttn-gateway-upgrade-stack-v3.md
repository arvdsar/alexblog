---
title: "TTN Gateway upgrade Stack v3"
date: "2021-10-02"
---

The TheThingsNetwork v2 stack is deprecated and the nodes and gateway have to be upgraded to the V3 stack. I have a [DIY gateway running with an IMST IC880A-SPI LoRa board](https://www.vdsar.net/lorawan-gateway-diy/).

I was looking for the easiest way to upgrade the gateway and found a [standard install via Balena.io](https://www.balena.io/blog/deploy-a-basics-station-lora-gateway-with-ttn-and-balena/). Using this I moved to the new Basic Station protocol which is more secure than the outdated protocol I used before and its now connected to TTN V3 Stack.

The only downside was that the Raspberry Pi I have used in the gateway (the original version 1) was too old so I had to replace this with a Raspberry Pi 3B+. (I didn't want to use the RPi 4 since that one uses more energy and is way overpowered for this purpose).

Follow the instructions on [this page](https://www.balena.io/blog/deploy-a-basics-station-lora-gateway-with-ttn-and-balena/) and you should be up and running in no time. The first time I tried, it did not work and I got an error that station.json could not be processed. To fix this, I deleted the gateway from the TTN Console and flashed the SD Card again so I could start from scratch. For me it worked to first do the Balena.io procedure and when the gateway is running you see an 'error' that the Gateway EUI is unknown. Now you go to the TTN Console and create a new gateway like the instructions explain. Second later I was up-and-running!
