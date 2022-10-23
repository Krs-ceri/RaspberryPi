#!/usr/bin/env python
import time
import serial
import sys
import time

# Serial communication parameters between Master and Balise (same on both sides)
ser = serial.Serial(
        port='/dev/ttyS0', #Replace ttyS0 with ttyAM0 for Pi1,Pi2,Pi0
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=None
)

# Interval to send data to Master
INTERVAL_BALISE = 10

# Open sensors log files in read mode
log_file = open("/home/pi/sensors-scripts/log_bme280.txt", "r")
log_file1 = open("/home/pi/sensors-scripts/log_gyro.txt", "r")

# Reading log files
data = log_file.read()
data = data + log_file1.read()

# Encoding unicode string to byte strings
data = data.encode('utf-8')

# Sending data to Master through Serial connection
ser.write(data)