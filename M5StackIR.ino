#include <M5Stack.h>

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("Ready...");
}

void loop() {
  // put your main code here, to run repeatedly:

}
