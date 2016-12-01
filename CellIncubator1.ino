/*Author: William R. Jackson
Project: Software for Cellular Incubator v .01
Purpose: The Code herein is used to regulate the temperature inside of a sealed container for the purpose of creating an ideal environment for 
Cellular Life. This is acheived by turning a lightbulb on and off to regulate the temperature inside the container. It works like an easy bake oven,
essentially.
*/


//Begin Display Libraries. Specifications for Display: https://www.amazon.com/Diymall%C2%AE-Serial-128x64-Display-Arduino/dp/B00O2KDQBE
//Chinese in Origin, cannot find specific data sheet.
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Begin Sensor Libraries. Specifications for Sensor: https://www.adafruit.com/products/381?gclid=CNb-z9L4t84CFcIkhgod5fgG9A
#include <OneWire.h>
#include <DallasTemperature.h>

//No Libraries required for Relay. Specifications for Relay: 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define ONE_WIRE_BUS 12
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define RELAY_ON 1
#define RELAY_OFF 0
#define Relay_1  13

double setTemp = 37.00;

void setup() {
	Serial.begin(9600);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	sensors.begin();
	display.display();
	delay(2000);
	display.clearDisplay();
  digitalWrite(Relay_1, RELAY_OFF);
  pinMode(Relay_1, OUTPUT);  
}

void loop() {
  //Starts the Display
	display.display();
  double currentTemp = sensors.getTempCByIndex(0);
	display.setTextSize(.5);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);
	sensors.requestTemperatures();
  display.println("UNCA easyBake v.01");
  display.print("Set Temp:  ");
  display.print(setTemp);
  display.print(" C      ");
  display.println("Current Temp: ");
  display.print(currentTemp);
  display.print(" C");
	delay(1000);
  //The next bit draws a rectangle over the previous text
  //This is because it doesn't reset the display every time it happens.
  display.fillRect(0, 24, 30, 30, 0x0000);
  display.setCursor(0, 24); 
  display.print(sensors.getTempCByIndex(0));
  if (currentTemp < setTemp) {
    digitalWrite(Relay_1, RELAY_ON);// set the Relay ON
  }
  else {
    digitalWrite(Relay_1, RELAY_OFF);
  }
  }

