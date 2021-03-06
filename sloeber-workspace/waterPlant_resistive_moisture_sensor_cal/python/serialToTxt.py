# -*- coding: utf-8 -*-

##############
## Script listens to serial port and writes contents into a file
##############
## requires pySerial to be installed
import serial

serial_port = 'COM4'
baud_rate = 9600 #In arduino, Serial.begin(baud_rate)
write_to_file_path = "output11.txt"

ser = serial.Serial(serial_port, baud_rate)

with open(write_to_file_path, 'w+') as f:
    while True:
        line = ser.readline()
        line = line.decode("utf-8")  # ser.readline returns a binary, convert to string
        f.writelines(line)
        f.flush()
        print(line)