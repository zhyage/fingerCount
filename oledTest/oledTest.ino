/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
 

  display.drawLine(0, 15, 127, 15, WHITE);
  display.drawLine(0, 39, 127, 39, WHITE);
  display.drawLine(31, 15, 31, 63, WHITE);
  display.drawLine(63, 15, 63, 63, WHITE);

  display.setCursor(0, 0);
  display.println("PingPang");

  display.setCursor(0, 20);
  display.println("RED");
  
  display.setCursor(0, 44);
  display.println("BLUE");

  display.setCursor(32, 20);
  display.println("RED");
  
  display.setCursor(32, 44);
  display.println("BLUE");

  
  
  display.display(); 
}

void loop() {
  
}
