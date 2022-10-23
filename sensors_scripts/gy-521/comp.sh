#!/bin/bash
g++ sensors-scripts/gy-521/libSensorSample.cpp -o sensors-scripts/gy-521/test -lwiringPi sensors-scripts/gy-521/libSensor.cpp
./sensors-scripts/gy-521/test