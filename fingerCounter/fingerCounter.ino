# include <EasyButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
# include "FingerCounter.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BUTTON_PIN_RED 2
#define BUTTON_PIN_BLUE 4
#define BUTTON_PIN_CONFIG 7

#define BAUDRATE 115200

EasyButton buttonRed(BUTTON_PIN_RED);
EasyButton buttonBlue(BUTTON_PIN_BLUE);
EasyButton buttonConfig(BUTTON_PIN_CONFIG);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



//void onRedButtonPress()
//{
//    match.blueRedButtonShortClick(false);
//    displayPoints(match);
//}
//
//void onBlueButtonPress()
//{
//    match.blueRedButtonShortClick(true);
//    displayPoints(match);
//}
//
//void onRedButtonLongPress()
//{
//    match.blueRedButtonLongClick(false);
//    displayPoints(match);
//}
//
//void onBlueButtonLongPress()
//{
//    match.blueRedButtonLongClick(true);
//    displayPoints(match);
//}
//
//void onConfigButtonPress()
//{
//    match.configButtonShortClick();
//    displayPoints(match);
//}
//
//void onConfigButtonLongPress()
//{
//    match.configButtonLongClick();
//    displayPoints(match);
//}

void setup()
{
    Serial.begin(BAUDRATE);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
    { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }

//    buttonRed.begin();
//    buttonBlue.begin();
//    buttonConfig.begin();
//
//    buttonRed.onPressed(onRedButtonPress);
//    buttonRed.onPressedFor(2000, onRedButtonLongPress);
//    buttonBlue.onPressed(onBlueButtonPress);
//    buttonBlue.onPressedFor(2000, onBlueButtonLongPress);
//    buttonConfig.onPressed(onConfigButtonPress);
//    buttonConfig.onPressedFor(2000, onConfigButtonLongPress);
}

//Match match;

//void displayPoints(Match& match)
//{
//    display.clearDisplay();
//
//    display.setTextSize(1);
//    display.setTextColor(WHITE);
//    
//
//    display.drawLine(0, 15, 127, 15, WHITE);
//    display.drawLine(0, 39, 127, 39, WHITE);
//    display.drawLine(31, 15, 31, 63, WHITE);
//    display.drawLine(63, 15, 63, 63, WHITE);
//
//    display.setCursor(0, 0);
//    display.println(match.getCurrentGameType());
//
//    display.setCursor(0, 20);
//    display.println("RED");
//    
//    display.setCursor(0, 44);
//    display.println("BLUE");
//
//    display.setCursor(32, 20);
//    display.println(match.getGamePoints().redPoints);
//    
//    display.setCursor(32, 44);
//    display.println(match.getGamePoints().bluePoints);
//
//    int servCirclePos = 20;
//
//    if(match.getServ()) // blue
//    {
//        servCirclePos = 44;
//    }
//    else
//    {
//        servCirclePos = 20;
//    }
//
//    display.fillCircle(74, servCirclePos, 8, INVERSE);
//
//    display.setCursor(85, 20);
//    display.println(match.getCurrentPoints().redPoints);
//    
//    display.setCursor(85, 44);
//    display.println(match.getCurrentPoints().bluePoints);
//  
//    display.display();
//}

void loop()
{
//    buttonRed.read();
//    buttonBlue.read();
//    buttonConfig.read();
}
