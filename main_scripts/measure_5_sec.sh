#!/bin/bash

while true
do
        #./sensors-scripts/pi-bme280/comp.sh
        ./sensors-scripts/pi-bme280/getbme280 -a 0x76 -t
        ./sensors-scripts/gy-521/comp.sh
        python serial/serial_write.py
        #./serial/send_to_master.sh
        sleep 10
done