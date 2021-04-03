#include "lcd12864b_s.h"

LCD12864B_S lcd(PA4, PA5, PA6);

void setup() {
  lcd.init();
  lcd.printfxy(0, 0, "hello,%s", "world");
  delay(2000);
  lcd.cls();
  lcd.printfxy(0, 1, "hello,%s", "wrold");
}

void loop() {

}
