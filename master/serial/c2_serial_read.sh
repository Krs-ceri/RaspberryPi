#!/bin/sh

gcc -Wall -o c2_s c2_serial_read.c -lwiringPi
./c2_s