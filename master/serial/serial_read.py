#!/usr/bin/env python
import time
import datetime
import os
import serial
import RPi.GPIO as GPIO

def led_setup():
    GPIO.setmode(GPIO.BCM)
    GPIO.setwarnings(False)
    GPIO.setup(26, GPIO.OUT)
    GPIO.setup(19, GPIO.OUT)
    GPIO.setup(13, GPIO.OUT)

def led_blink(led):
    for i in range (1):
        GPIO.output(led, GPIO.HIGH)
        time.sleep(0.25)
        GPIO.output(led, GPIO.LOW)
        time.sleep(0.25)

def led_on(led):
    GPIO.output(led, GPIO.HIGH)

def led_off(led):
    GPIO.output(led, GPIO.LOW)

# Serial communication parameters between Master and Balise
ser = serial.Serial(
        port='/dev/ttyS0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=None
)

# Interval to collect data sent from Balise
INTER_BALISE = 26
INTER_MASTER = 15

# Setup the leds
led_setup()

# GPIO numbers
red = 26
yellow = 19
green = 13

# Path to log.json
s = "/home/pi/serial/logs/log.json"

while 1:
    ########## red = gpio 26, yellow = 19, green = 13 => don't belive the sticker shown on camera ########

    log_file = open(s, mode="wb")# encoding="utf-8")
    x=""

    #port_open = 0
    #if port_open == 0:
    #    print("Ok port open")
    #    port_open = 1
    #else:
    #    ser.open()
    #ser.flushInput()
    #time.sleep(30)
    #ser.flushInput()
    #ser.flushOutput()
    ser.reset_input_buffer()
    ser.reset_output_buffer()
    for i in range(16):
        # By default, yellow led is on when program is active
        led_on(yellow)

        # Reading serial text received from Balise Rpi
        x=""
        x=ser.readline()


        # Show data received on stdout (unicode)
        print(x)

        # If data received from Balise, yellow led is off, red led blinks
        led_off(yellow)
        led_blink(red)

        # Converting data from bytes string to unicode string
            #x = str(b'\xe4\xbd\xa0\xe5\xa5\xbd', encoding='utf-8')

        # Opening file for writing
        #s = "/home/pi/serial/log_%s-%s-%s-%sh%sm%ss.txt" % e.day,
        #e = datetime.datetime.now()
        #s = ("/home/pi/serial/logs/log_%s-%s-%s-%sh%sm.json" % (e.day, e.month, e.year, e.hour, e.minute))
        log_file = open(s, mode="ab")#, encoding="utf-8")
        #with open(s, encoding="utf-8", errors='ignore') as log_file:
        # log_file = open("/home/pi/logs/log_gyro.txt","w")

        if x=="":
            print("rien")
        else:
            # Decode serial data from bytes strings into utf-8 unicode strings
            #x=x.decode('utf-8')
            # Writing data in log file
            log_file.write(x)
        s0 = b'\n'
        # Closing log file
        log_file.close()
        if x==s0: #"\n":
            led_on(yellow)
            #ser.close()
            #time.sleep(27)
            #ser.reset_input_buffer()
            #ser.reset_output_buffer()