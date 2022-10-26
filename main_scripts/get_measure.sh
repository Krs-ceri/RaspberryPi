#!/bin/bash

while true
do
        #./sensors-scripts/pi-bme280/comp.sh
        ./sensors-scripts/pi-bme280/getbme280 -a 0x76 -t
        #sleep 1
        ./sensors-scripts/gy-521/comp.sh
        sleep 5
        #python serial/serial_write.py
        #./serial/send_to_master.sh
        #sleep 30
done