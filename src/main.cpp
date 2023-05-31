#include "header.h"

Menu *menu = &MainMenu;

void setup(){
  Serial.begin(115200);
  Serial.println(__FILE__);

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

  relays.relayall = 0xFF;
  // TimerFlag.Timerall = 0x00;
}

void loop(){
  char buffer=relays.relayall;
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
      if(chart == 'A') delay(175);
      // select = (select==1)?3:select-1;
      switch(menu->MenuID){
        case Got_Title: select = (select==1)?3:select-1; break;
        case Main_Menu: select = (select==1)?3:select-1; break;
        case OnOffRelay: select = (select==1)?3:select-1; break;
        default: select = (select==0)?3:select-1;

      }
    }

    if(chart == 'D') {
      if(chart == 'D') delay(175);
      // select = (select==3)?1:select+1;
      switch(menu->MenuID){
        case Got_Title: select = (select==3)?1:select+1; break;
        case Main_Menu: select = (select==3)?1:select+1; break;
        case OnOffRelay: select = (select==3)?1:select+1; break;
        default: select = (select==3)?0:select+1;
      }
    }

    if(chart == 'C') {
      if(chart == 'C') delay(175);
      switch (select){
      case 0: menu=(menu->Menulist0==NULL)?menu:menu->Menulist0; break;
      case 1: menu=(menu->Menulist1==NULL)?menu:menu->Menulist1; break;
      case 2: menu=(menu->Menulist2==NULL)?menu:menu->Menulist2; break;
      case 3: menu=(menu->Menulist3==NULL)?menu:menu->Menulist3; break;
      }
    new_menu=1; 
    }

    if(chart == 'B') {
      if(chart == 'B') delay(175);
      menu=(menu->pre==NULL)?menu:menu->pre;
      new_menu=1;
    }
    
    if(chart == '*') {
      if(chart == '*') delay(175);
      ActualActivation(menu,select);
      new_menu=1;
    }

    if(new_menu) {  lcd.clear();  new_menu = 0; }
    MenuDisplay(menu,select);
    
  }
  ActivationDisplay(menu);
  if(menu->MenuID==Main_Menu) LCD_print_time();
  if(buffer != relays.relayall) {
    RelayOut(RelayI2C, relays.relayall);
    buffer = relays.relayall;
  }

  Serial.println(relays.relayall, HEX);
  for(int i=0 ; i<8 ; i++){
    Serial.print("TIMER["); Serial.print(i); Serial.print("]: ");
    Serial.print(TIMER[i].YEAR+2000, DEC);
    Serial.print("/");
    Serial.print(TIMER[i].MONTH, DEC);
    Serial.print("/");
    Serial.print(TIMER[i].DAY, DEC);
    Serial.print("-");
    Serial.print(TIMER[i].HOUR, DEC);
    Serial.print(":");
    Serial.print(TIMER[i].MINUTE, DEC);
    Serial.print(":");
    Serial.print(TIMER[i].SECOND, DEC);
    Serial.print(" ");
    Serial.print("Flag:");
    Serial.print(TimerFlag[i]);
    Serial.println(" ");
  }
  
  Serial.print("RTC:"); 
    Serial.print(DS1307_TIME.YEAR+2000, DEC);
    Serial.print("/");
    Serial.print(DS1307_TIME.MONTH, DEC);
    Serial.print("/");
    Serial.print(DS1307_TIME.DAY, DEC);
    Serial.print("-");
    Serial.print(DS1307_TIME.HOUR, DEC);
    Serial.print(":");
    Serial.print(DS1307_TIME.MINUTE, DEC);
    Serial.print(":");
    Serial.print(DS1307_TIME.SECOND, DEC);
    Serial.println(" ");
    
    RelayAuto();
}