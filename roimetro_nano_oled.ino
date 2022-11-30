/**************************************************************************
ROIMETRO LW1EHP
DISPLAY OLED SSD1306 128X64
ARDUINO NANO
A0 DIRECTA
A1 REFLEJADA
A4 DATOS I2C
A5 CLOCK I2C
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
/*
#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };
*/
float Vi=0.00;
float Vr=0.00;
float Ti=0.00;
float Tr=0.00;
float Pi=0.00;
float Pr=0.00;
float ro=0.00;
float ROE=0.00;

void setup() {
  
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  delay(200);
  
}

void loop() 
  {
  Vi=analogRead(A0)*5.00/1023;
  Vr=analogRead(A1)*5.00/1023;
  ro=Vr/Vi;
  ROE=(1+ro)/(1-ro);
  Ti=0.707*Vi;
  Tr=0.707*Vr;
  Pi=(Ti*Ti)/400.00;
  Pr=(Tr*Tr)/400.00;
  
  display.setTextSize(1); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 6);
  display.print(F("Vi: "));
  display.println(Vi);
  display.setCursor(10, 16);
  display.print(F("Vr: "));
  display.println(Vr);
  display.setCursor(10, 26);
  display.print(F("Pi: "));
  display.println(Pi);
  display.setCursor(10, 36);
  display.print(F("Pr: "));
  display.println(Pr);
  display.drawRect(1, 1, 126, 62, SSD1306_WHITE);
  display.setTextSize(2); 
  display.setCursor(83, 6);
  display.println("ROE");
  display.setCursor(78, 25);
  display.println(ROE);
  display.display();      
  delay(250);
  display.clearDisplay();
  }
