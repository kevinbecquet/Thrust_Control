import serial

from threading import Thread

#initialize serial port
ser = serial.Serial()
ser.port = '/dev/ttyACM0' #Arduino serial port
ser.baudrate = 9600
ser.timeout = 10 #specify timeout when using readline()
ser.open()


def readSerial():
    ser.readline() #read the first line (very likely to be incomplete thus unusable)
    while(True):
        if(ser.inWaiting()>7):
            line=ser.readline().decode('utf-8')
            line_as_list = line.split(',')

            time = int(line_as_list[0])
            force = float(line_as_list[1]) 
            
            print(time,force)

def writeSerial():

    while(True):
        f = input()
        ser.write(f.encode())
        
    


#readSerial()
t1 = Thread(target=readSerial)
t2 = Thread(target=writeSerial)

t1.start()
t2.start()    