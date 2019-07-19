#include <M5Stack.h>
#include <IRremote.h>

int RECV_PIN = 36; 
IRrecv irrecv(RECV_PIN); 

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println("IR Code Reader");
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("Ready...");
  irrecv.enableIRIn(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
