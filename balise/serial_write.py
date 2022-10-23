#!/usr/bin/env python
import time
import serial
import sys
import time

ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
        baudrate = 100,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

INTERVAL_SEND_TO_MASTER = 10
#word = input(b'Hello maitre')
#word = b'Hello world'
#while 1:
    # Opening log files to read them
log_file = open("/home/pi/sensors-scripts/log_bme280.txt", "r")
log_file1 = open("/home/pi/sensors-scripts/log_gyro.txt", "r")

    # Reading log files
data = log_file.read()
data = data + log_file1.read()

    # Encoding unicode string to byte strings
data = data.encode('utf-8')
    #ser.write(b'Hello world')

    # Sending data to Master through Serial connection
ser.write(data)
    #time.sleep(1)
    #time.sleep(INTERVAL_SEND_TO_MASTER)