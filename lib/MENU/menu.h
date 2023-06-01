#ifndef MENU_H
#define MENU_H

#define Default 0
#define Got_Title 1
#define Main_Menu 2
#define Relay14Set 3
#define Relay58Set 4
#define Relay14T 5
#define Relay58T 6 
#define SetTime 7 
#define OnOffRelay 8
#define TimerRelay 9


typedef struct Linker {
    char MenuID;
    struct Linker *pre;
    char List0[16] ; struct Linker *Menulist0;
    char List1[16] ; struct Linker *Menulist1;
    char List2[16] ; struct Linker *Menulist2;
    char List3[16] ; struct Linker *Menulist3;
} Menu;

extern Menu MainMenu, TimerMenu, Manual, 
            OnOffState, 
            Relay14Toggle, Relay58Toggle, 
            Relay14Timer, Relay58Timer ;

#endif

