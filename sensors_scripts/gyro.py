#!/usr/bin/python
import smbus
import math

# Register
power_mgmt_1 = 0x6b
power_mgmt_2 = 0x6c

def read_byte(reg):
    return bus.read_byte_data(address, reg)

def read_word(reg):
    h = bus.read_byte_data(address, reg)
    l = bus.read_byte_data(address, reg+1)
    value = (h << 8) + l
    return value

def read_word_2c(reg):
    val = read_word(reg)
    if (val >= 0x8000):
        return -((65535 - val) + 1)
    else:
        return val

def dist(a,b):
    return math.sqrt((a*a)+(b*b))

def get_y_rotation(x,y,z):
    radians = math.atan2(x, dist(y,z))
    return -math.degrees(radians)

def get_x_rotation(x,y,z):
    radians = math.atan2(y, dist(x,z))
    return math.degrees(radians)

bus = smbus.SMBus(1) # bus = smbus.SMBus(0) fuer Revision 1
address = 0x68       # via i2cdetect

# Aktivieren, um das Modul ansprechen zu koennen
bus.write_byte_data(address, power_mgmt_1, 0)

#print("Gyroscope 3 axes")
#print("--------")

gyroskop_xout = read_word_2c(0x43)
gyroskop_yout = read_word_2c(0x45)
gyroskop_zout = read_word_2c(0x47)

gyroskop_xout = gyroskop_xout/131.0
gyroskop_yout = gyroskop_yout/131.0
gyroskop_zout = gyroskop_zout/131.0

print("gyro_x: %.3f," % gyroskop_xout)#, " skaliert: ", (gyroskop_xout / 131))
print("gyro_y: %.3f," % gyroskop_yout)#, " skaliert: ", (gyroskop_xout / 131))
print("gyro_z: %.3f," % gyroskop_zout)#, " skaliert: ", (gyroskop_xout / 131))

#print("gyro_y: ", ("%7.3f," % gyroskop_yout/131.0))#, " skaliert: ", (gyroskop_yout / 131))
#print("gyro_z: ", ("%7.3f," % gyroskop_zout/131.0))#, " skaliert: ", (gyroskop_zout / 131))

#print ("")
#print ("Capteur d'acceleration")
#print ("---------------------")

#s = "Gyroscope 3 axes" + "\n" + "--------" + "\n"

s = ""
#s = s + "gyro_x: " + str(gyroskop_xout/131.0) + "\n" #, " skaliert: ", (gyroskop_xout / 131))
#s = s + "gyro_y: " + str(gyroskop_yout/131.0) + "\n" #, " skaliert: ", (gyroskop_xout / 131))
#s = s + "gyro_z: " + str(gyroskop_zout/131.0) + "\n" #, " skaliert: ", (gyroskop_xout / 131))


s = s + "gyro_x: " + ("%.3f," % gyroskop_xout) + "\n" #, " skaliert: ", (gyroskop_yout / 131))
s = s + "gyro_y: " + ("%.3f," % gyroskop_yout) + "\n" #, " skaliert: ", (gyroskop_yout / 131))
s = s + "gyro_z: " + ("%.3f," % gyroskop_zout) + "\n" #, " skaliert: ", (gyroskop_zout / 131))

#s = s + '\n'
#s = s + "Capteur d'acceleration" + "\n"
#s = s + "----------------------" + "\n"

beschleunigung_xout = read_word_2c(0x3b)
beschleunigung_yout = read_word_2c(0x3d)
beschleunigung_zout = read_word_2c(0x3f)

accel_xout = beschleunigung_xout / 16384.0
accel_yout = beschleunigung_yout / 16384.0
accel_zout = beschleunigung_zout / 16384.0


#print ("accel_x: ", beschleunigung_xout/16384.0)#, " skaliert: ", beschleunigung_xout_skaliert)
#print ("accel_y: ", beschleunigung_yout/16384.0)#, " skaliert: ", beschleunigung_xout_skaliert)
#print ("accel_z: ", beschleunigung_zout/16384.0)#, " skaliert: ", beschleunigung_xout_skaliert)

print ("accel_x: ", ("%.3f," % accel_xout))#, " skaliert: ", beschleunigung_yout_skaliert)
print ("accel_y: ", ("%.3f," % accel_yout))#, " skaliert: ", beschleunigung_yout_skaliert)
print ("accel_z: ", ("%.3f" % accel_zout))#, " skaliert: ", beschleunigung_zout_skaliert)

#s = s + "accel_x: " + str(beschleunigung_xout/16384.0) + "\n" #, " skaliert: ", beschleunigung_xout_skaliert)
#s = s + "accel_y: " + str(beschleunigung_yout/16384.0) + "\n" #, " skaliert: ", beschleunigung_yout_skaliert)
#s = s + "accel_z: " + str(beschleunigung_zout/16384.0) + "\n" #, " skaliert: ", beschleunigung_yout_skaliert)

s = s + "accel_x: " + ("%.3f," % accel_xout) + "\n" #, " skaliert: ", beschleunigung_zout_skaliert)
s = s + "accel_y: " + ("%.3f," % accel_yout) + "\n" #, " skaliert: ", beschleunigung_zout_skaliert)
s = s + "accel_z: " + ("%.3f" % accel_zout) + "\n" #, " skaliert: ", beschleunigung_zout_skaliert)

s = s + "}" + "\n"
s = s + "}" + "\n"

#print ("X Rotation: " , get_x_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert))
#print ("Y Rotation: " , get_y_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert))
print("}")
print("}")

#s = s + "X Rotation: " , get_x_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert)
#s = s + "Y Rotation: " , get_y_rotation(beschleunigung_xout_skaliert, beschleunigung_yout_skaliert, beschleunigung_zout_skaliert)

file = open("/home/pi/sensors-scripts/log_gyro.txt", mode="w")
file.write(s)
file.close()