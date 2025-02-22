#!/usr/bin/env python
#This program sends string: TX868=TIME,xxxxxxx  to the domotica gateway which will forward the number xxxxxxx to the wireless LCD 
# display to update the realtime clock and set the RTC
#add it to the crontab of the system

#version 0.1  www.vdsar.net


import time
import socket
import random


# Echo client program
HOST = '192.168.3.123'    # The remote host Enter IP of your Domotica gateway
PORT = 23             # The same port as used by the server
TimeZone = 3600 #3600 seconds per hour  (maybe adjust with Daylight saving stuff)

for num in range(0,3):	
	time_string = "TX868=TIME," + str(int(time.time()+TimeZone))
	print "Time string send: "
	print time_string

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect((HOST, PORT))
	s.sendall(time_string)
	s.close()

	RandomA = random.randint(15, 59)
	print "random = ", RandomA
	time.sleep(RandomA)
