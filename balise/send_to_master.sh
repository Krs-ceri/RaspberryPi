#!/bin/bash

FILE="/home/pi/serial/go_value.txt"
if [ -f "$FILE" ]; then
        #python serial_write.py
        interval=$(cat go_value.txt)
        cmd2="./sensors-scripts/pi-bme280/getbme280 -a 0x76 -t"
        cmd1="./sensors.-scripts/gy-521/test"
        #cmd1="python /home/pi/sensors-scripts/gyro.py"
        cmd="python /home/pi/serial/serial_write.py"
        #write current crontab in mycron
        crontab -l > mycron
        #delete last line of mycron
        sed -i '$ d' mycron

        #echo new cron into mycron file
        #echo cd > mycron
        #echo cd sensors-scripts/pi-bme280/ >> mycron
        #echo ./bme280.sh >> mycron
        #echo cd >> mycron

        echo "*/$interval * * * * $cmd2" > mycron
        echo "*/$interval * * * * $cmd1" >> mycron
        echo "*/$interval * * * * $cmd" >> mycron
        #install new cron file
        #cat mycron
        crontab mycron
        rm mycron
fi