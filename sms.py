#!/usr/bin/python
 # carrage returns and endlines are only one byte each

import serial

ok = False
exit = False
serConn = serial.Serial("/dev/ttyUSB0", 115200)
print(serConn.name) 
serConn.write(b'AT+CMGF=1\n')
serConn.write(b'AT+CMGS="7075846965"\n')
serConn.write(b'This is a third test ttest, test with a\n new line!')
serConn.write(b'\x1a')
while not ok:
	res = serConn.readline()
	print(res)
	if res.find(b'OK') > -1:
		ok = True
serConn.close()
