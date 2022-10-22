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

ser = serial.Serial(
        port='/dev/ttyS0',
        baudrate = 100,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=None
)

INTERVAL_RECEIVE_MASTER = 15

# Setup the leds
led_setup()
#log_file = open("/home/pi/serial/log.txt", mode="w", encoding="utf-8")
INTER_BALISE = 26
while 1:
    #active = 0

    #if active == 1:

    #for i in range(16):
    ########## red = gpio 26, yellow = 19, green = 13 => don't belive the sticker shown on camera ##########
    #time.sleep(INTER_BALISE*2)

    #time.sleep(60)
    for i in range(16):
        #x=""
        # By default, yellow led is on when program is active
        led_on(19)

        # Reading serial text received from Balise Rpi
        x=""
        x=ser.readline()

        # Decode serial data from bytes strings into utf-8 unicode strings
        #x = x.decode('utf-8')

        # Show data received on stdout (unicode)
        print(x)

        if x!="":
            # If data received from Balise, yellow led is off, red led blinks
            led_off(19)
            led_blink(26)

        # Converting data from bytes string to unicode string
            #x = str(b'\xe4\xbd\xa0\xe5\xa5\xbd', encoding='utf-8')

        # Opening file for writing
        #log_file = open("/home/pi/logs/log.txt", mode="w+b")#, encoding="utf-8")
        #s = "/home/pi/serial/log_%s-%s-%s-%sh%sm%ss.txt" % e.day,
        e = datetime.datetime.now()
        s = ("/home/pi/serial/logs/log_%s-%s-%s-%sh%sm.json" % (e.day, e.month, e.year, e.hour, e.minute))
        log_file = open(s, mode="a", encoding="utf-8")
        #log_file = open("/home/pi/logs/log_gyro.txt","w")

        if x=="":
            print("rien")
    #continue
        else:
            # Writing data in log file
            x=x.decode('utf-8')
            log_file.write(x)

        # Closing log file
        log_file.close()
        if x=="\n":
            time.sleep(57)

        # Frequency of reading of Master
        #time.sleep(INTERVAL_RECEIVE_MASTER)
        #if input()
        #time.sleep(0.5)
#log_file.close()