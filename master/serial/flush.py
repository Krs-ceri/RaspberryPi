#!/usr/bin/env python
import time
import datetime
import os
import serial

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=None
)

ser.reset_input_buffer()
ser.reset_output_buffer()
ser.close()