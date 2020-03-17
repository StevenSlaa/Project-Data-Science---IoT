import json
import Adafruit_DHT

DHT_SENSOR = Adafruit_DHT.DHT22
DHT = 4

temperature = 0
humidity = 0

while True:
  payload = {
    "name": "Temperatuur Sensor",
    "temperature": temperature,
    "humidity": temperature
  }
  h, t = Adafruit_DHT.read(DHT_SENSOR, DHT)
  if h is not None and t is not None:
    temperature = t
    humidity = h
  jsonPayload = json.dumps(payload)
  print(jsonPayload)
