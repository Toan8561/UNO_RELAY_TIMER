#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <I2CKeyPad.h>
#include <menu.h>



/* Khởi tạo hàm suất ký tự đặc biệt */
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

#define bitflip(byte,nbit)  ((byte) ^=  (1<<(nbit)))

struct Relay_bite{
    unsigned char RL1: 1 ;
    unsigned char RL2: 1 ;
    unsigned char RL3: 1 ;
    unsigned char RL4: 1 ;
    unsigned char RL5: 1 ;
    unsigned char RL6: 1 ;
    unsigned char RL7: 1 ;
    unsigned char RL8: 1 ;
};

union RL{
    unsigned char relayall ;
    struct Relay_bite relay ;
};

union RL relays ; 

unsigned char TimerFlag[8]={0};
unsigned char TimerWrite=0;

/*==== Sài lcd.write() để thay thế ====*/

/*==== I2C COMMUNACATION ====*/
//#include <Adafruit_SPIDevice.h> //SCL A5 SDA A4
RTC_DS1307 rtc;

uint8_t second_buff;

typedef struct Time_buffer{
    // uint8_t WEEK_D;
    uint8_t DAY;
    uint8_t MONTH;
    uint8_t YEAR;
    uint8_t HOUR;
    uint8_t MINUTE;
    uint8_t SECOND;
} TIME;
TIME DS1307_TIME;
TIME TIMER[8]={0};

// char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thusday", "Friday", "Saturday"};

void DS1307_init(){
    /* Thực hiện kiếm DS1307 bằng địa chỉ có sẵn 0x68  trên I2C bus */
    if (! rtc.begin()){
        Serial.print("Couldn't find RTC");
        Serial.print("Check connection");
        while (1);
    }
    /* Nếu tìm thấy DS1307 sẽ gửi về bit 1 - kết nối thành công */
    if (! rtc.isrunning()){
        Serial.print("RTC is NOT running!");
        Serial.println("Check for RTC chip!");
    }
    
    // /* Thực hiện nạp dữ liệu thời gian tại lúc build vào firmware thông qua kết nối USB */
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); //Thực hiện set giờ thủ công year|month|day|hour|minute|second
                    }  

void DS1037_get_time(){
    TIME *p;
    DateTime now = rtc.now();
    p=&DS1307_TIME;
    p->DAY= now.day();
    p->MONTH= now.month();
    p->YEAR=now.year()- 2000; //đọc năm, bỏ phần 20 trong 2000
    p->HOUR=now.hour();
    p->MINUTE=now.minute();
    p->SECOND=now.second();
                        }

                      
void DS1307_time_store(){
    TIME *p;
    p=&DS1307_TIME;
    uint8_t writeData[6] = {p->YEAR,p->MONTH,p->DAY,p->HOUR,p->MINUTE,p->SECOND};
    rtc.writenvram(0, writeData, 6);
}

void DS1307_time_update(){
    if(digitalRead(13)){
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
        DS1037_get_time(); 
        DS1307_time_store(); 
    }
    else{
        uint8_t readData[6] = {0};
        rtc.readnvram(readData, 6, 0);
        rtc.adjust(DateTime(readData[0]+2000, readData[1], readData[2], readData[3], readData[4], readData[5]));
    }
}  


LiquidCrystal_I2C lcd(0X27,20,4); 
/* Ký tự đặt biệt cho LCD */
/* https://maxpromer.github.io/LCD-Character-Creator/ */
uint8_t bell[8]  =    {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
uint8_t retarrow[8] = {0x10,0x10,0x14,0x12,0x1F,0x02,0x04,0x00};
uint8_t clock[8] =    {0x00,0x0E,0x15,0x17,0x11,0x0E,0x00,0x00};
uint8_t heart[8] =    {0x00,0x0A,0x1F,0x1F,0x0E,0x04,0x00,0x00};

void LCD_startup(){
    //lcd.init();       //Khởi động LCD bằng địa chỉ đã khai báo 
    lcd.begin(20,4);    //Khởi động LCD bằng địa chỉ đã khai báo                
    lcd.backlight();    // Bật đèn nền để cho LCD dễ nhìn trong đêm 
    lcd.clear();        //Thực hiện xóa mà hình LCD để tránh hiện tượng có dữ liệu tồn đọng
                    }

void LCD_SpecChars(){
    lcd.createChar(0, bell);
    lcd.createChar(1, retarrow);
    lcd.createChar(2, clock);
    lcd.createChar(3, heart);
                    }

/*LCD_date need 12-14 space in LCD*/
void LCD_print_time(){

        DateTime now = rtc.now();
        TIME *p;
        p=&DS1307_TIME;

        int day= p->DAY, month= p->MONTH, year=p->YEAR, hour= p->HOUR, minute= p->MINUTE; 
        int second= p->SECOND; 

        lcd.setCursor(9,0); 
        lcd.print("|");
        lcd.print(" ");
        lcd.print(daysOfTheWeek[now.dayOfTheWeek()]); 

        lcd.setCursor(9,1);
        lcd.print("|");

        if (day <= 9){
            lcd.print("0");
            lcd.print(day);   }
        else lcd.print(day);
        lcd.print('/');
        if (month <= 9){
            lcd.print("0");
            lcd.print(month); }
        else lcd.print(month);
        lcd.print('/');
        if (year <= 9){
            lcd.print("0");
            lcd.print(year);   }
        else lcd.print(year);
    
        lcd.setCursor(9,2);
        lcd.print("|");
        if (hour <= 9){
            lcd.print("0");
            lcd.print(hour);  }
        else lcd.print(hour);

        lcd.print(':');

        if (minute <= 9){
            lcd.print("0");
            lcd.print(minute);    }
        else lcd.print(minute);

        lcd.print(':');

        if (second <= 9){
            lcd.print("0");
            lcd.print(second);    }
        else lcd.print(second);
}


// IRQ var
bool keyChange = false;
const uint8_t KEYPAD_ADDRESS = 0x38;
//char keymap[] = "123A456B789C*0#DNF";  // N = NoKey, F = Fail
char keymap[] = "DCBA#9630852*741NF";  // N = NoKey, F = Fail
I2CKeyPad keyPad(KEYPAD_ADDRESS);

void keyChanged(){  keyChange = true;   }

void keyPad_init(){
    if (keyPad.begin() == false){
        Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
        while (1);
    }
    keyPad.loadKeyMap(keymap);
}

char interrupts_getkey(bool IRQ_flag){
    char chart;

    if (IRQ_flag){
        uint8_t index = keyPad.getKey();
        // only after keyChange is handled it is time reset the flag
        keyChange = false;
        if (index != 16) chart = keymap[index];
        else chart = keymap[16];
    }
    return chart;
}

int getData() {
  String container = "";
  int cursor=1;
  lcd.setCursor(1, 1);
  while (true) {
    char chart = interrupts_getkey(keyChange);
    delay(150);
    if (chart == '*') break;
    else if (isDigit(chart)) {
      container += chart;
      cursor += 1;
      lcd.print(chart);
    }

    else {
      //Nothing
    }
  }
  return container.toInt();
}

void SetTimer(TIME *p, unsigned char *Flag){
    lcd.clear();
    lcd.home();

    char chart;
    int buffer=0;
    delay(150);
    chart = interrupts_getkey(keyChange);
    
    while(chart=='N'){
        lcd.clear();
        lcd.home();
        lcd.setCursor(0,0);
        lcd.print("  SET TIMER MODE   ");
        lcd.setCursor(0,2);
        lcd.print("(*)EXIT   (#)ENTER ");

        chart = interrupts_getkey(keyChange);
        delay(150);
    }
    
    switch (chart){
    case '*':
        break;
    
    case '#':
        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Year: ");
            buffer=getData();
        } while ((buffer>2099)||(buffer<1970));
        
        p->YEAR = (uint8_t)(buffer-2000);

        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Month: ");
            buffer=getData();
        } while ((buffer>12)||(buffer<=0));
        p->MONTH = (uint8_t)buffer;

        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Day: ");
            buffer=getData();
        } while ((buffer>31)||(buffer<=0));
        p->DAY = (uint8_t)buffer;

        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Hours: ");
            buffer=getData();
        } while (buffer>23);
        p->HOUR = (uint8_t)buffer;

        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Minutes: ");
            buffer=getData();
        } while (buffer>59);
        p->MINUTE = (uint8_t)buffer;

        do{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Enter Seconds: ");
            buffer=getData();
        } while (buffer>59);
        p->SECOND = (uint8_t)buffer;

        *Flag=1;
        break;

    default:
        break;
    }
}


void ActualActivation(Menu *menu, int select){
    TIME *p;
    switch (menu->MenuID){

    case Relay14Set:
        switch (select){
        case 0:
            relays.relay.RL1 = !(relays.relay.RL1);
            break;

        case 1:
            relays.relay.RL2 = !(relays.relay.RL2);
            break;

        case 2:
            relays.relay.RL3 = !(relays.relay.RL3);
            break;

        case 3:
            relays.relay.RL4 = !(relays.relay.RL4);
            break;
        }
        break;

    case Relay58Set:
        switch (select){
        case 0:
            relays.relay.RL5 = !(relays.relay.RL5);
            break;

        case 1:
            relays.relay.RL6 = !(relays.relay.RL6);
            break;

        case 2:
            relays.relay.RL7 = !(relays.relay.RL7);
            break;

        case 3:
            relays.relay.RL8 = !(relays.relay.RL8);
            break;
        }
        break;

    case Relay14T:
        switch (select){
        case 0:
            p=&TIMER[0];
            SetTimer(p, &TimerFlag[0]);
            break;

        case 1:
            p=&TIMER[1];
            SetTimer(p, &TimerFlag[1]);
            break;

        case 2:
            p=&TIMER[2];
            SetTimer(p, &TimerFlag[2]);
            break;

        case 3:
            p=&TIMER[3];
            SetTimer(p, &TimerFlag[3]);
            break;
        }
        break;
    
    case Relay58T:
        switch (select){
        case 0:
            p=&TIMER[4];
            SetTimer(p, &TimerFlag[4]);
            break;

        case 1:
            p=&TIMER[5];
            SetTimer(p, &TimerFlag[5]);
            break;

        case 2:
            p=&TIMER[6];
            SetTimer(p, &TimerFlag[6]);
            break;

        case 3:
            p=&TIMER[7];
            SetTimer(p, &TimerFlag[7]);
            break;
        }
        break;

    case SetTime:
        switch (select){
        case 0:
            
            break;

        case 1:
        
            break;

        case 2:
        
            break;

        case 3:
        
            break;
        }
        break;

    case OnOffRelay:
        if(select == 3) relays.relayall ^= 0xFF;
        break;
    
    default:
        break;
    }
}

void ActivationDisplay(Menu *menu){
    switch (menu->MenuID){

    case Relay14Set:
        lcd.setCursor(12,0);
        if(!relays.relay.RL1) lcd.print("ON");
        else if(relays.relay.RL1) lcd.print("OFF");

        lcd.setCursor(12,1);
        if(!relays.relay.RL2) lcd.print("ON");
        else if(relays.relay.RL2) lcd.print("OFF");

        lcd.setCursor(12,2);
        if(!relays.relay.RL3) lcd.print("ON");
        else if(relays.relay.RL3) lcd.print("OFF");

        lcd.setCursor(12,3);
       if(!relays.relay.RL4) lcd.print("ON");
        else if(relays.relay.RL4) lcd.print("OFF");
        break;

    case Relay58Set:
        lcd.setCursor(12,0);
        if(!relays.relay.RL5) lcd.print("ON");
        else if(relays.relay.RL5) lcd.print("OFF");

        lcd.setCursor(12,1);
        if(!relays.relay.RL6) lcd.print("ON");
        else if(relays.relay.RL6) lcd.print("OFF");

        lcd.setCursor(12,2);
        if(!relays.relay.RL7) lcd.print("ON");
        else if(relays.relay.RL7) lcd.print("OFF");

        lcd.setCursor(12,3);
        if(!relays.relay.RL8) lcd.print("ON");
        else if(relays.relay.RL8) lcd.print("OFF");
        break;

    case Relay14T:
        lcd.setCursor(12,0);
        if(TimerFlag[0]) lcd.write(2);

        lcd.setCursor(12,1);
        if(TimerFlag[1]) lcd.write(2);

        lcd.setCursor(12,2);
        if(TimerFlag[2]) lcd.write(2);

        lcd.setCursor(12,3);
        if(TimerFlag[3]) lcd.write(2);
        break;
    
    case Relay58T:
        lcd.setCursor(12,0);
        if(TimerFlag[4]) lcd.write(2);

        lcd.setCursor(12,1);
        if(TimerFlag[5])lcd.write(2);

        lcd.setCursor(12,2);
        if(TimerFlag[6]) lcd.write(2);

        lcd.setCursor(12,3);
        if(TimerFlag[7]) lcd.write(2);
        break;

    case SetTime:

        break;
    
    default:
        break;
    }
}

int select=1, new_menu = 0;
void MenuDisplay(Menu *menu, int select){
    lcd.setCursor(0,0); lcd.print(menu->List0);
    lcd.setCursor(0,1); lcd.print(menu->List1);
    lcd.setCursor(0,2); lcd.print(menu->List2);
    lcd.setCursor(0,3); lcd.print(menu->List3);

    // lcd.setCursor(0,select); lcd.print(">");
    lcd.setCursor(0,select); lcd.write(1);
} 

void RelayAuto(){
    TIME *p;
    p=&DS1307_TIME;

    uint8_t readData[6] = {0};
    rtc.readnvram(readData, 6, 0);

    unsigned char ToggleFlag[8]={0};

    for(int i=0; i<8; i++){
        if(TimerFlag[i]){
            if(p->SECOND >= TIMER[i].SECOND){
                if(p->MINUTE >= TIMER[i].MINUTE){
                    if(p->HOUR >= TIMER[i].HOUR){
                        if(p->DAY >= TIMER[i].DAY){
                            if(p->MONTH >= TIMER[i].MONTH){
                                if(p->YEAR >= TIMER[i].YEAR){
                                    ToggleFlag[i] = 1;
                                    TimerFlag[i] = 0;
                                    TimerWrite = 1;
                                    new_menu = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(ToggleFlag[0]) relays.relay.RL1 = !(relays.relay.RL1);
    if(ToggleFlag[1]) relays.relay.RL2 = !(relays.relay.RL2);
    if(ToggleFlag[2]) relays.relay.RL3 = !(relays.relay.RL3);
    if(ToggleFlag[3]) relays.relay.RL4 = !(relays.relay.RL4);
    if(ToggleFlag[4]) relays.relay.RL5 = !(relays.relay.RL5);
    if(ToggleFlag[5]) relays.relay.RL6 = !(relays.relay.RL6);
    if(ToggleFlag[6]) relays.relay.RL7 = !(relays.relay.RL7);
    if(ToggleFlag[7]) relays.relay.RL8 = !(relays.relay.RL8);
}


int RelayI2C=0x39;

void RelayOut(int Realay_addr, char Data){
    Wire.beginTransmission(Realay_addr);
    Wire.write(Data);
    Wire.endTransmission();
}