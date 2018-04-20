#include <Arduino.h>
#include <LED.h>
#include <IR.h>
#include <DotSD.h>
#include <WIFI.h>

LED led;
IR ir;
DotSD dotSD;
// WIFI wifi;

// 44 Key
#define BTN_BRIGHT_UP     0xFF3AC5
#define BTN_BRIGHT_UP_2   0x820
#define BTN_BRIGHT_UP_3   0x20
#define BTN_BRIGHT_DOWN   0xFFBA45
#define BTN_BRIGHT_DOWN_2 0x821
#define BTN_BRIGHT_DOWN_3 0x21
#define BTN_RESTART       0xFD807F
#define BTN_BATTERY       0xFD20DF
#define BTN_FASTER        0xFFE817
#define BTN_SLOWER        0xFFC837
#define BTN_OFF           0x80C
#define BTN_PREV          0xFF08F7
#define BTN_PREV_2        0x811
#define BTN_PREV_3        0x11
#define BTN_NEXT          0xFF28D7
#define BTN_NEXT_2        0x810
#define BTN_NEXT_3        0x10
#define BTN_AUTOPLAY      0XFFF00F
#define BTN_SWITCH_MODE   0XFF827D
#define BTN_SWITCH_MODE_2 0X80B
#define BTN_SWITCH_MODE_3 0XB

#define BTN_DIR1 0XFF30CF

#define BTN_NONE         -1

boolean povMode = false;

void setup() {
  delay(5000);
  Serial.println("Welcome to dotdotflow");
  ir.init();
  led.init();
  // dotSD.init();
  // wifi.init();
}

void nextPressed() {
  (povMode) ? led.nextImage() : led.nextPattern();
}

void prevPressed() {
  (povMode) ? led.prevImage() : led.prevPattern();
}

void loop() {
  // wifi.listenWifi();
  if (povMode) {
    led.pov();
  } else {
    switch(led.patternNumber) {
      case 0:
        led.fire(50, 80, 15);
        break;
      case 1:
        led.sparkle(random(255), random(255), random(255), 0);
        break;
      case 2:
        led.convergeIn();
        break;
    }
  }
  
  ir.IRinterrupt();

  if(ir.results.value != BTN_NONE) {
    switch(ir.results.value) {
      case BTN_NEXT:
        nextPressed();
        break;
      case BTN_PREV:
        prevPressed();
        break;
      case BTN_SWITCH_MODE:
        povMode = !povMode;
        break;
      case BTN_DIR1:
        dotSD.printDirectory(dotSD.root, 0);
        // dotSD.root.openNextFile()

        // Serial.println("Test file:");
        // dotSD.printFile("porn_letters.bmp");
        // dotSD.bmpDrawScale("porn_letters.bmp");

        // bmpFile.close();
        break;
    }
    // Reset IR value
    ir.results.value = BTN_NONE;
  }


}

