#include "ThingSpeak.h"
#include "config.h"
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
WiFiClient  client;
IPAddress ip;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);  //Initialize serial
  Wire.begin (19, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Connecting to Network"));
  display.display();

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  int statusCode = 0;

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    ip = WiFi.localIP();
    //Dipslaying wifi information for 2 seconds on the display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F("SSID: "));
    display.setCursor(0, 10);
    display.println(F(ssid));
    display.setCursor(0, 30);
    display.println(F("IP-address:"));
    display.setCursor(0, 40);
    display.println(ip);
    display.display();
    delay(2000);
  }

  // Read temperature
  float temperature = ThingSpeak.readFloatField(CHANNEL_ID, 1, APIKEY);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200) {
    Serial.println("Temperature = " + String(temperature) + " C");
  } else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }
  // Read humidity
  float humidity = ThingSpeak.readLongField(CHANNEL_ID, 2, APIKEY);
  if (statusCode == 200) {
    Serial.println("Humidity = " + String(humidity) + " %");
  } else {
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode));
  }
  displayData(temperature, humidity); // Display data on the display
  delay(READ_INTERVAL);
}

// Displaying temperature and humidity to on the OLED Display
void displayData(float temperature, float humidity) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Temperature:"));
  display.setCursor(0, 10);
  display.setTextSize(2);
  display.println(temperature);
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println(F("Humidity:"));
  display.setCursor(0, 40);
  display.setTextSize(2);
  display.println(humidity);
  display.display();
}
