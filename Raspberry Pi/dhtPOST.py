import json
import Adafruit_DHT
import requests

#DHT Sensor Setup
DHT_SENSOR = Adafruit_DHT.DHT22
DHT = 4
temperature = 0
humidity = 0

#POST Request Setup
url = 'https://postb.in/1583321863853-5484660009387'
headers = {'content-type': 'application/json'}

while True:
  payload = {
    "name": "Temperatuur Sensor",
    "temperature": temperature,
    "humidity": humidity
  }
  h, t = Adafruit_DHT.read(DHT_SENSOR, DHT)
  if h is not None and t is not None:
    temperature = t
    humidity = h
  jsonPayload = json.dumps(payload)
  #print(jsonPayload)
  response = requests.post(url, data=json.dumps(payload), headers=headers)
  print(response.content)