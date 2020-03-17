#Libraries
import Adafruit_DHT as dht
from time import sleep
#Set DATA pin
DHT = 4
while True:
    #Read Temp and Hum from DHT22
    h,t = dht.read(dht.DHT22, DHT)
    #Print Temperature and Humidity on Shell window
    print t, ' graden | ', h, '%'
    sleep(1)
