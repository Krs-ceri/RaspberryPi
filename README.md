# RaspberryPi
This is our first Raspberry pi project, including sensors and master-slave rasp. Also, collecting data over a web-server.

## TCP Server

file_client.cpp : send log.json when receiving in data, then delete it (change dir : line 41/85/104) g++ -o c file_client.cpp


file_server.cpp : receive data from tcp connection, and save it as "log.json" (change dir : line 41/85/104) g++ -o s file_server.cpp



