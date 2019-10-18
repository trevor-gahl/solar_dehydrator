#include<DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Define OLED parameterstemperature =dht.readTemperature();
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Define DHT temperature sensor parameters
#define DHTPIN 2
#define DHTTYPE DHT22

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   12
#define OLED_CLK   11
#define OLED_DC    10
#define OLED_CS    8
#define OLED_RESET 9

// Define temperature threshold
#define THRESHOLD 57.2

// Initialize the display and temperature sensor
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  			OLED_MOSI, OLED_CLK, OLED_DC,
			OLED_RESET, OLED_CS);
DHT dht(DHTPIN,DHTTYPE);

// Create global variables to hold sensor data
float humidity;
float temperature;
bool fan_mode = false;

// Function to print sensor data to OLED
void screen_refresh(float humidity, float temperature, bool fan_mode)
{
  display.clearDisplay();
  display.setTextSize(1.8);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(F("Temperature(C): "));
  display.println(temperature);
  display.println();
  display.println();
  display.print(F("Humidity%: "));
  display.println(humidity);
  display.println();
  display.println();
  display.print(F("Fan Mode: "));
  if(fan_mode){
    display.println(F("ON"));
  }else{
    display.println(F("OFF"));
  }
  display.display();
}

// Setup code section
void setup() {
 
 // Initialize serial port to 9600 baud
 Serial.begin(9600);
 
 // Initialize temperature sensor
 dht.begin();

 // Check display status
 if(!display.begin(SSD1306_SWITCHCAPVCC)) {
   Serial.println(F("SSD1306 allocation failed"));
   for(;;); // Don't proceed, loop forever
 }
 
 // Initialize relay pin as output and initialize to off
 pinMode(5,OUTPUT);
 digitalWrite(5, HIGH); // Relay is active low
}

void loop() {
  
  // Read sensor data
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  // Determine fan mode based on sensor data
  if(temperature>THRESHOLD){
    digitalWrite(5, LOW);  // Relay is active low
    fan_mode=true;
  }else{
    digitalWrite(5, HIGH); // Relay is active low    
    fan_mode=false;
  }

  // Print data to screen
  screen_refresh(humidity, temperature, fan_mode);
}
