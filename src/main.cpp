#include "header.h"

Menu *menu = &MainMenu;

void setup(){
  // Serial.begin(115200);
  // Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(700000);

  pinMode(13, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), keyChanged, FALLING);

  DS1307_init();
  keyPad_init();
  LCD_startup();

  LCD_SpecChars();

  /* Thực hiện nạp dữ liệu thời gian tại lúc build vào firmware */
  DS1307_time_update();
  
}

void loop(){
  DS1037_get_time();
  TIME *p;
  p=&DS1307_TIME;
  if(second_buff != p->SECOND){
    DS1307_time_store();
    second_buff = p->SECOND;
  }
  char chart = interrupts_getkey(keyChange);
  if(chart !='N'){
    if(chart == 'A') {
      if(chart == 'A') delay(150);
      select = (select==1)?3:select-1;
      // switch(menu->MenuID){
      //   case Got_Title: select = (select==1)?3:select-1; break;
      //   case Main_Menu: select = (select==1)?3:select-1; break;
      //   default: select = (select==0)?3:select-1;

      // }
    }

    if(chart == 'D') {
      if(chart == 'D') delay(150);
      select = (select==3)?1:select+1;
      // switch(menu->MenuID){
      //   case Got_Title: select = (select==3)?1:select+1; break;
      //   case Main_Menu: select = (select==3)?1:select+1; break;
      //   default: select = (select==3)?0:select+1;
      // }
    }

    if(chart == 'C') {
      switch (select){
      case 1: menu=(menu->Menulist1==NULL)?menu:menu->Menulist1; break;
      case 2: menu=(menu->Menulist2==NULL)?menu:menu->Menulist2; break;
      case 3: menu=(menu->Menulist3==NULL)?menu:menu->Menulist3; break;
      }
    new_menu=1; 
    }

    if(chart == 'B') {
      menu=(menu->pre==NULL)?menu:menu->pre;
      new_menu=1;
    }
    if(new_menu) {  lcd.clear();  new_menu = 0; }
    MenuDisplay(menu,select);
    
  }
  // if(menu->MenuID==Main_Menu) LCD_print_time();
  // else LCD_print_time(menu);
  // else Serial.println("No key push");
  // if(chart != 'N') Serial.println(chart);
  // else Serial.println("No key map connection");

  
}
