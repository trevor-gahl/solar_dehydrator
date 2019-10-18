#include<DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTPIN 2
#define DHTTYPE DHT22


// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   12
#define OLED_CLK   11
#define OLED_DC    10
#define OLED_CS    8
#define OLED_RESET 9
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
DHT dht(DHTPIN,DHTTYPE);

int chk;
float humidity;
float temperature;
bool fan_mode = false;


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 dht.begin();
 // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
 pinMode(5,OUTPUT);
 digitalWrite(5, HIGH); // Active Low
 

}

void loop() {
  // put your main code here, to run repeatedly:
  humidity = dht.readHumidity();
  temperature =dht.readTemperature();
  display.clearDisplay();
  display.setTextSize(1.8); // Draw 2X-scale text
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
  display.display();      // Show initial text
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %, Temperature: ");
  Serial.print(temperature);
  Serial.println(" Celsius");
  if(temperature>57.2){
    digitalWrite(5, LOW);   // turn the LED on (HIGH is the voltage level)
    fan_mode=true;
    delay(2000);                       // wait for a second
  }else{
    digitalWrite(5, HIGH);    // turn the LED off by making the voltage LOW
    delay(2000);                       // wait for a second
    fan_mode=false;
  }
}
