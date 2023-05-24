#ifndef MENU_H
#define MENU_H

#include <avr/pgmspace.h>

typedef struct Linker {
    struct Linker *pre;
    char Title[21] ;
    char List1[21] ; struct Linker *Menulist1;
    char List2[21] ; struct Linker *Menulist2;
    char List3[21] ; struct Linker *Menulist3;
} Menu;

extern Menu MainMenu, TimerMenu, UserMenu, CLOCK_MOD, //CLOCK_MOD is a big clock on display
            AlarmMenu, TimerRelayMenu,                //TimerMenu (done)
            RelayStatusMenu, SettingMenu,             //UserMenu
            SeTimeMenu, FormaTimeMenu, DisplayMenu,   //SettingMenu
            Alarm1Menu, Alarm2Menu, Alarm3Menu,       //AlarmMenu (done)
            List1Menu,  List2Menu,  List3Menu,        //TimerRelayMenu (done)
            List4Menu,  List5Menu,  List6Menu,
            Relay1TimerMenu, Relay2TimerMenu,         //List*Menu , NextListMenu go to next list and it go around (done)
            Relay3TimerMenu, Relay4TimerMenu, 
            Relay5TimerMenu, Relay6TimerMenu,
            Relay1OnOffMenu, Relay2OnOffMenu,         //List*Menu , NextListMenu go to next list and it go around (done)
            Relay3OnOffMenu, Relay4OnOffMenu, 
            Relay5OnOffMenu, Relay6OnOffMenu;

#endif

