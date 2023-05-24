#include <menu.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

/*========== MainMenu ==========*/
Menu MainMenu  = {
    NULL,
    "                    ",
    "  TIMER             ",&TimerMenu,
    "  USER CONFIG       ",&UserMenu,
    "  CLOCK MOD         ",&CLOCK_MOD,
};

Menu TimerMenu  = {
    &MainMenu,
    "    TIMER  MENU     ", 
    "  ALARM SETTING     ",&AlarmMenu,
    "  TIMER FOR RELAY   ",&TimerRelayMenu,
    "  CLEAR ALL DATA    ",NULL,
};

Menu UserMenu  = {
    &MainMenu,
    "     USER  MENU     ",
    "  RELAY STATUS      ",&RelayStatusMenu,
    "  SETTING           ",&SettingMenu,
    "  CLOCK MOD         ",&CLOCK_MOD,
};

Menu CLOCK_MOD  = {
    &MainMenu,
    "  ON                ",
    "  OFF               ",NULL,
    "  BACK              ",NULL,
    "                    ",NULL,
};
/*================================*/


/*========== Alarm Menu ==========*/
Menu AlarmMenu  = {
    &MainMenu,
    "    ALARM  MENU     ", 
    "  ALARM_1           ",&Alarm1Menu,
    "  ALARM_2           ",&Alarm2Menu,
    "  ALARM_3           ",&Alarm3Menu,
}; 

Menu Alarm1Menu  = {
    &AlarmMenu,
    "   ALARM 1  MENU    ", 
    "  TIME:             ",NULL,
    "  DATE:             ",NULL,
    "  CLEAR             ",NULL,
};

Menu Alarm2Menu  = {
    &AlarmMenu,
    "   ALARM 2  MENU    ", 
    "  TIME:             ",NULL,
    "  DATE:             ",NULL,
    "  CLEAR             ",NULL,
};

Menu Alarm3Menu  = {
    &AlarmMenu,
    "   ALARM 3  MENU    ",
    "  TIME:             ",NULL,
    "  DATE:             ",NULL,
    "  CLEAR             ",NULL,
};
/*================================*/


/*======= Timer Relay Menu =======*/
Menu TimerRelayMenu  = {
    &TimerMenu,
    " TIMER RELAY  MENU  ", 
    "  LIST 1            ",&List1Menu,
    "  LIST 2            ",&List2Menu,
    "  LIST 3            ",&List3Menu,
};

Menu List1Menu  = {
   &TimerRelayMenu,
    "   LIST 1  MENU    ", 
    "  RELAY 1          ",&Relay1TimerMenu,
    "  RELAY 2          ",&Relay2TimerMenu,
    "  NEXT LIST        ",&List2Menu,
};

Menu List2Menu  = {
    &TimerRelayMenu,
    "   LIST 2  MENU    ", 
    "  RELAY 3          ",&Relay3TimerMenu,
    "  RELAY 4          ",&Relay4TimerMenu,
    "  NEXT LIST        ",&List3Menu,
};

Menu List3Menu  = {
    &TimerRelayMenu,
    "   LIST 2  MENU    ", 
    "  RELAY 5          ",&Relay5TimerMenu,
    "  RELAY 6          ",&Relay6TimerMenu,
    "  NEXT LIST        ",&List1Menu,
};

Menu Relay1TimerMenu  = {
    &List1Menu,
    "   RELAY 1 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};

Menu Relay2TimerMenu  = {
    &List1Menu,
    "   RELAY 2 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};

Menu Relay3TimerMenu  = {
    &List1Menu,
    "   RELAY 3 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};

Menu Relay4TimerMenu  = {
    &List2Menu,
    "   RELAY 4 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};

Menu Relay5TimerMenu  = {
    &List2Menu,
    "   RELAY 5 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};

Menu Relay6TimerMenu  = {
    &List2Menu,
    "   RELAY 6 MENU    ",  
    "  START:           ",NULL,
    "  END:             ",NULL,
    "  INVERTER         ",NULL,
};
/*================================*/


/*======= Relay ON/OFF Menu ======*/
Menu RelayStatusMenu  = {
    &UserMenu,
    " TIMER On Off MENU  ", 
    "  LIST 1            ",&List4Menu,
    "  LIST 2            ",&List5Menu,
    "  LIST 3            ",&List6Menu,
};

Menu List4Menu  = {
   &TimerRelayMenu,
    "   LIST 1  MENU    ", 
    "  RELAY 1          ",&Relay1OnOffMenu,
    "  RELAY 2          ",&Relay2OnOffMenu,
    "  NEXT LIST        ",&List5Menu,
};

Menu List5Menu  = {
    &TimerRelayMenu,
    "   LIST 2  MENU    ", 
    "  RELAY 3          ",&Relay3OnOffMenu,
    "  RELAY 4          ",&Relay4OnOffMenu,
    "  NEXT LIST        ",&List6Menu,
};

Menu List6Menu  = {
    &TimerRelayMenu,
    "   LIST 2  MENU    ", 
    "  RELAY 5          ",&Relay5OnOffMenu,
    "  RELAY 6          ",&Relay6OnOffMenu,
    "  NEXT LIST        ",&List4Menu,
};
Menu Relay1OnOffMenu  = {
    &List4Menu,
    "   RELAY 1 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};
Menu Relay2OnOffMenu  = {
    &List4Menu,
    "   RELAY 2 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};
Menu Relay3OnOffMenu  = {
    &List5Menu,
    "   RELAY 3 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};
Menu Relay4OnOffMenu  = {
    &List5Menu,
    "   RELAY 4 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};
Menu Relay5OnOffMenu  = {
    &List6Menu,
    "   RELAY 5 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};
Menu Relay6OnOffMenu  = {
    &List6Menu,
    "   RELAY 6 MENU    ",  
    "  ON               ",NULL,
    "  OFF              ",NULL,
    "  INVERTER         ",NULL,
};

/*================================*/

/*========= Setting Menu =========*/
Menu SettingMenu  = {
    &UserMenu,
    "                    ",
    "                    ",&SeTimeMenu,
    "                    ",&FormaTimeMenu,
    "                    ",&DisplayMenu,
};
Menu SeTimeMenu  = {
    NULL,
    "                    ",
    "                    ",NULL,
    "                    ",NULL,
    "                    ",NULL,
};
Menu FormaTimeMenu  = {
    NULL,
    "                    ",
    "                    ",NULL,
    "                    ",NULL,
    "                    ",NULL,
};
Menu DisplayMenu  = {
    NULL,
    "                    ",
    "                    ",NULL,
    "                    ",NULL,
    "                    ",NULL,
};
/*================================*/
