#include <ArduinoJson.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Surfplank 2.4GHz";
const char* password = "ababababba";
IPAddress ip;

HTTPClient http;


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
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

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  ip = WiFi.localIP();

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
  getTemperature();
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    deserializeJson(doc, input);
    
    //getTemperature();
  }

  delay(10000);
}

void printData(int temperature, int humidity) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
}

String getData() {
  HTTPClient http;
  http.begin("https://api.thingspeak.com/channels/1009663/fields/1.json?api_key=HL69SBOYW13OVNEI"); //Specify the URL
  int httpCode = http.GET();                                        //Make the request
  if (httpCode > 0) { //Check for the returning code
    String payload = http.getString();
  } else {
    Serial.println("Error on HTTP request");
  }
  http.end(); //Free the resources
  return payload;
}
