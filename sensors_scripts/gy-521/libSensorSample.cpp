#include <iostream>
#include <wiringPi.h>
#include <stdio.h>
#include <cmath>
#include "libSensor.h"

using namespace std;

int main()
{
    if (wiringPiSetup() == -1)
        return -1;

    Sensor gyro;
    perror("Init gyro");

    int x,y,z, x_gyro;

        //while(1){
        x=gyro.getAccelX();
        y=gyro.getAccelY();
        z=gyro.getAccelZ();

        x_gyro = gyro.getGyroX();

        //float scale0 = 131.0;
        //float scale1 = 16384.0;

        FILE *fptr;
        fptr = fopen("/home/pi/sensors-scripts/log_gyro.txt","wb");
        fprintf(fptr, "gyro_x: %.3f,\ngyro_y: %.3f,\ngyro_z: %.3f,\naccel_x: %.3f,\naccel_y: %.3f,\naccel_z: %.3f\n}\n}\n\n",
                        (float)gyro.getGyroX()/131.0,(float)gyro.getGyroY()/131.0,(float)gyro.getGyroZ()/131.0,
                        (float)gyro.getAccelX()/16384.0, (float)gyro.getAccelY()/16384.0,
                        (float)gyro.getAccelZ()/16384.0);
        printf("Gyro Axe X: %.3f\nGyro Axe Y: %.3f\nGyro Axe Z: %.3f\nAcceleration Axe X: %.3f\nAcceleration Axe Y: %.3f\nAcceleration Axe Z: %.3f\n\n",
                        (float)gyro.getGyroX()/131.0, (float)gyro.getGyroY()/131.0, (float)gyro.getGyroZ()/131.0,
                        (float)gyro.getAccelX()/16384.0, (float)gyro.getAccelY()/16384.0,
                        (float)gyro.getAccelZ()/16384.0);
        fclose(fptr);
        //printf("x=%d    y=%d    z=%d      ax=%f\n", x, y, z, gyro.getAngleX());

}