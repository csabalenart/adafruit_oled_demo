#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "animation.h"
#include "irt_logo.h"

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels

#define SCREEN_I2C_ADDR 0x3C // or 0x3D
#define SDA_OLED 17u //ez nem kell
#define SCL_OLED 18u //ez sem
#define RST_OLED 21u // -1, ha nem lenne reset

TwoWire myWire = TwoWire(1);
Adafruit_SSD1306 display(128, 64, &myWire, RST_OLED);


void setup() {
  Serial.begin(115200);
  myWire.begin(SDA_OLED, SCL_OLED); // Needs to come before display.begin() is used
  if(display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR)){
    Serial.println("Sikeres oled start");
  }else{
    Serial.println("Nem sikerült oledezni");
  }
  display.cp437(true);
}
int frame = 0;
void loop() {
  display.clearDisplay();
  display.drawXBitmap(0, 0, IRT_LOGO, IRTLOGO_WIDTH, IRTLOGO_HEIGHT, 1);
  display.drawBitmap(0, 33, frames[frame], FRAME_WIDTH, FRAME_HEIGHT, 1);
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(37,45);
  display.println("Lenart Istvan");
  display.display();
  frame = (frame + 1) % FRAME_COUNT;
  delay(FRAME_DELAY);
}

