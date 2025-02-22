---
title: "Login for Node-Red on TheThingBox"
date: "2015-12-20"
tags: 
  - "domotica"
  - "iot"
  - "raspberry-pi"
  - "software"
  - "thethingbox"
---

[TheThingBox](http://thethingbox.io) is a great image ready to be used on a Raspberry Pi and has preinstalled [Node-Red](http://nodered.org), [Mosquitto](http://mosquitto.org/) (MQTT) and several Nodes. The default install of Node-Red does not contain any form of login authorization so you shouldn't connect it to the internet by default.

To make it more secure the first step is to add some authorization to Node-Red. It took me a while to find how to do this for TheThingBox because it looks a little different than a default Node-Red install.

You need basic understanding of how to connect to your Raspberry Pi with SSH.

**Login to your Raspberry Pi (TheThingBox)** **Become root (just to be sure ;-)** `su -` `cd /root/thethingbox` `sudo npm install -g --unsafe-perm bcryptjs`

(update sept 2016:) With TheThingBox 2.2.0 the install of bcryptjs didn't work with above command. The below worked!

`sudo npm install bcryptjs`

**Create a password hash** `node -e "console.log(require('bcryptjs').hashSync(process.argv[1], 8));" 'YOURPASSWORDHERE'` **Copy the hash result, you need it in the config file below.** **To be sure you are at the right path:** `cd /root/thethingbox`

**Edit the config file:** `sudo nano thethingbox.js`

**Now you look for the part starting with: var settings\_nodered = ...... It looks like:**

`var settings_nodered = { // http://nodered.org/docs/configuration.html httpAdminRoot:"/", httpNodeRoot: "/api/", userDir: userDir, flowDir: flowDir, // TTB specific flowFile: flowDir + "flows.json", systemFlowDir: "/root/thethingbox/node_modules/node-red/flow", verbose: true, flowFilePretty: true, otherPropToSave: ['origin'], // properties to keep when dealing with nodes in memory paletteCategories:['subflows', 'input', 'output', 'function', 'social', 'storage', 'analysis', 'advanced'], hiddenWorkspaces: ['system'], functionGlobalContext: { settings: settings_ttb ,userDir: userDir ,settingslib: require('/root/thethingbox/settingsttb.js') ,wpi: require('node-red/node_modules/wiring-pi') // https://www.npmjs.com/package/wiring-pi ,CryptoJS: require('node-red/node_modules/crypto-js') // https://www.npmjs.com/package/cryptojs }, **adminAuth: { type: "credentials", users: [{ username: “YOURUSERNAME", password: “PASTE YOUR PASSWORDHASH HERE", permissions: "*" }]** }`

};

Please pay attention to the comma behind the } on the line before adminAuth: The adminAuth part is the part you need to add. The **\*** with permissions means all permissions, replace it with **read** for readonly. I guess you can add more users by repeating the **users:** part.

CTRL+X makes you save the config file. Reboot the raspberry pi and you should get a login screen!

**By default Node-Red is using http traffic which is unencrypted. I couldn't get https (SSL) setup using the Node-Red config but there is a workaround using stunnel.** 

The stunnel application is a SSL encryption wrapper that can tunnel unencrypted traffic (like NodeRed) through a SSL encrypted tunnel to another server. For now, use google to find a how-to. (update sept 2016): you can find some info in the document section here: [http://thethingbox.io/docs/faq\_tech.html](http://thethingbox.io/docs/faq_tech.html)\[/fusion\_builder\_column\]\[/fusion\_builder\_row\]\[/fusion\_builder\_container\]
