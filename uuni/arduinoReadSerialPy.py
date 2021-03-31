import serial
import time
import mysql.connector
from datetime import date, datetime, timedelta

#a for the loop "counter"
a = 0
#time.strftime('%Y-%m-%d %H:%M:%S')


db = mysql.connector.connect(
    host = "",
    user = "",
    password = "",
    database = ""
    )
print(db)
cursor = db.cursor()


#simple insert to database for serial data
def insert_to_db(ftemp, ftime, fname):
    add_temperature = ("INSERT INTO {} "
                   "(temperature, time) "
                   "VALUES (%s, %s)".format(fname))
    data = (ftemp, ftime)
    cursor.execute(add_temperature, data)
    db.commit()

#serial setup
ser = serial.Serial('/dev/ttyACM0', baudrate = 9600, timeout=1)
ser.flush()

#loop to read serial data and pass it to database
while 1:
    today = datetime.now()
    arduinoData = ser.readline()
    eka = arduinoData.decode('utf-8')
    eka = eka.split()

    arduinoData = ser.readline()
    toka = arduinoData.decode('utf-8')
    toka = toka.split()

    arduinoData = ser.readline()
    kolmas = arduinoData.decode('utf-8')
    kolmas = kolmas.split()

    arduinoData = ser.readline()
    neljas = arduinoData.decode('utf-8')
    neljas = neljas.split()
    
    #checks for everything to be where they are supposed to
    if ((a > 5) and (len(eka)>2) and (len(toka)>2) and (len(kolmas)>2) and (len(neljas)>2)):
        #print(eka[2], eka[0])
        #print(eka[0] == "NTC1TEMP")
        #print(toka[2], toka[0])
        #print(kolmas[2], kolmas[0])
        #print(neljas[2], neljas[0])
        insert_to_db(eka[2], today, eka[0])
        insert_to_db(toka[2], today, toka[0])
        insert_to_db(kolmas[2], today, kolmas[0])
        insert_to_db(neljas[2], today, neljas[0])        
        
    #loop 5 times before doing anything to stabilize things        
    if a <= 5:
        a = a + 1
    time.sleep(5)
    

    
    