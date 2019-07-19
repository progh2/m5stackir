#include <M5Stack.h>
#include <IRremote.h>

int RECV_PIN = 36; 
IRrecv irrecv(RECV_PIN); 
decode_results results; 

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
  if (irrecv.decode(&results)) {  
    M5.Lcd.fillRect(0,40,200,30, GREEN);
    M5.Lcd.setCursor(0,40);
    M5.Lcd.println(results.value, HEX);
    irrecv.resume(); 
  }
  delay(100);   
}
