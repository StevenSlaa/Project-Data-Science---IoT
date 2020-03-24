import json
import Adafruit_DHT
import requests
from time import sleep
import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library

GPIO.setwarnings(False)    # Ignore warning for now
GPIO.setmode(GPIO.BOARD)   # Use physical pin numbering
# Set pin 8 to be an output pin and set initial value to low (off)
GPIO.setup(8, GPIO.OUT, initial=GPIO.LOW)

# DHT Sensor Setup
DHT_SENSOR = Adafruit_DHT.DHT22
DHT = 4
temperature = 0
humidity = 0

# POST Request Setup (ThingSpeak)
key = "TJCLHK0VN84Z59FQ"
url = 'https://api.thingspeak.com/update'
# headers = {'content-type': 'application/json'}
channel_id = 1009663

while True:
    payload = {
        "field1": temperature,
        "field2": humidity,
        "api_key": key
    }
    h, t = Adafruit_DHT.read(DHT_SENSOR, DHT)
    if h is not None and t is not None:
        temperature = t
        humidity = h
    jsonPayload = json.dumps(payload)
    # print(jsonPayload)
    response = requests.get(url, params=payload)
    print("Temperature: ", temperature, " | Humidity: ", humidity)
    GPIO.output(8, GPIO.HIGH)  # Turn on
    sleep(1)                  # Sleep for 1 second
    GPIO.output(8, GPIO.LOW)  # Turn off
    sleep(1)                  # Sleep for 1 second
