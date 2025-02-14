---
title: "NodeRed Builds Taglist"
date: "2022-02-13"
author: Alexander
---

I build Node-RED images regularly, including several nodes that I use. I use these images on my Intel NUC and previously on my Synology. The images are X86/64 based.

I haven't invested time aligning the tags with the Node-RED versions, so I keep a list here to track which tag of my images contains which Node-RED version.

### mrmadalex/my_new_nodered Tag List

| Tag | Node-RED Version | Comments |
| --- | ---------------- | -------- |
| 50  | Node-RED 4.0.5   |          |
| 49  | Node-RED 4.0.2   |          |
| 46  | Node-RED 3.1.6   |          |
| 45  | Node-RED 3.1.3   |          |
| 43  | Node-RED 3.0.2   |          |
| 41  | Node-RED 3.0.0   | See Hue Magic remark below. |
| 39  | Node-RED 2.2.2   | (Probably still issues with Node-RED-Contrib-chatbot) |
| 38  | Node-RED 2.2.0   | (Issues with Node-RED-Contrib-chatbot) |
| 36  | Node-RED 2.1.6   |          |
| 35  | Node-RED 2.1.4   |          |

There seems to be an issue with Hue Magic 4.2.2, which you can find [here](https://github.com/Foddy/node-red-contrib-huemagic/issues/373). To solve it, enter the container of Node-RED and find the path: `/node_modules/huemagic/node-red-contrib-huemagic/utils`. In this directory, you'll find `messages.js`, which you can modify following the instructions in the [GitHub link](https://github.com/Foddy/node-red-contrib-huemagic/issues/373).

For the Node-RED change log, refer to [this link](https://github.com/node-red/node-red/blob/master/CHANGELOG.md).
