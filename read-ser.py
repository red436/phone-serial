#!/usr/bin/python
 # carrage returns and endlines are only one byte each

import serial

ok = False
exit = False
serConn = serial.Serial("/dev/ttyUSB0", 9600)
print(serConn.name) 
while not ok:
	res = serConn.readline()
	print(res)
serConn.close()
