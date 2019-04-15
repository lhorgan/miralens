from time import sleep

import serial

curr_entry = ""

ser = serial.Serial('COM3', 9600, timeout=0) # Establish the connection on a specific port

while True:
    yay = ser.read().decode("utf-8") 
    if(yay.find("\n") >= 0):
        first, second = yay.split("\n")
        curr_entry += first
        print(curr_entry)
        curr_entry = second
    else:
        curr_entry += yay