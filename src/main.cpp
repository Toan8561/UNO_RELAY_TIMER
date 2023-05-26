#include "header.h"


void setup(){
  Serial.begin(115200);
  Serial.println(__FILE__);
  DS1307_init();
  LCD_startup();

  // randomSeed(analogRead(A0));
  // num = random(lower, upper);

  /* Thực hiện nạp dữ liệu thời gian tại lúc build vào firmware */

  DS1307_time_update();

  
    // Wire.begin();
    // Wire.setClock(700000);
    // keyPad_init();
    // pinMode(2, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(2), keyChanged, FALLING);

  // int selecter=1;
  // Menu *menu;
  // menu = &MainMenu;
  // MenuDisplay(menu,selecter);
}


void loop(){
  DS1037_get_time();
  LCD_print_time();
  TIME *p;
  p=&DS1307_TIME;
  if(second_buff != p->SECOND){
    DS1307_time_store();
    second_buff = p->SECOND;
  }

  lcd.setCursor(0,2);
  char chart = interrupts_getkey(keyChange);
  if(chart != 'N') lcd.println(chart);
  else lcd.println();

  Serial.println(num);

}

