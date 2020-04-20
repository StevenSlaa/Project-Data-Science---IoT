#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Configuration
// WIFI
const char* ssid = "MIJN SSID";
const char* password = "MIJN WACHTWOORD";
// Display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SDA 19  //SDA Pin that is connected to OLED Display
#define SCL 22  //SCL Pin that is connected to OLED Display
// ThingSpeak
String apiKey = "API_KEY HERE";

IPAddress ip;
HTTPClient http;

// Declaration for an SSD1306 display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 4);

void setup() {
  Serial.begin(115200);
  Wire.begin (SDA, SCL); // Start I2C communication
  
  //Error checking for display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  //Clear display buffer and print Wifi connection status to the display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(F("Connecting to Network"));
  display.display();
  
  WiFi.begin(ssid, password); //Connect wifi with the SSID and Password

  //Try connecting to the wifi network every second if the previous attempt failed
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  ip = WiFi.localIP(); // Get the ESP's IP Adres
  
  //Clear display buffer and print Wifi connection status to the display
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
  getData(); // Get first data
}

void loop() {
  //Check if connection is still available
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    Serial.println(getData()); //Print the received json payload to the serial monitor
  }
  delay(10000); // Wait 10 seconds
}

String getData() {
  HTTPClient http; // Start a new http client
  http.begin("https://api.thingspeak.com/channels/1009663/fields/1.json?api_key=" + apiKey); //Specify the URL
  int httpCode = http.GET();                                        //Make the request
  if (httpCode > 0) { //Check for the returning code
    String payload = http.getString();
  } else {
    Serial.println("Error on HTTP request");
  }
  http.end(); //Free the resources
  return payload;
}
