#!/usr/bin/env python3

import serial
from timeit import default_timer as timer

print("Measure Serial Speed")

with serial.Serial('/dev/ttyACM0', 19200, timeout=3) as ser:
	ser.write(b's') # Write to start speedtset
	start = timer()
	s = ser.readline()
	end = timer()
	elapsed = end - start
	print(str(elapsed) + "s")
	byteCount = len(s)
	print("Bytes: " + str(byteCount))
	
	print("Speed " + str(byteCount / elapsed / 1000) + "kB/s")
