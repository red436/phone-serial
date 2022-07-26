#!/usr/bin/python
 # carrage returns and endlines are only one byte each

import serial

commands = [{'name': 'AT+GSN\n', 'description': 'get-imei', 'rbytes': 31 }]
ok = False
exit = False
serConn = serial.Serial("/dev/ttyUSB0", 115200)
print(serConn.name) 
while not exit:
	ok = False
	command = input("Enter command: ")
	if command == "exit":
		exit = True
	serConn.write(bytes(command + "\n", "utf-8"))
	while not ok:
		res = serConn.readline()
		print(res)
		if res.find(b'OK') > -1:
			ok = True
serConn.close()
