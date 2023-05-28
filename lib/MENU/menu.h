#ifndef MENU_H
#define MENU_H

#define Default 0
#define Main_Menu 1

typedef struct Linker {
    char MenuID;
    struct Linker *pre;
    char Title[17] ;
    char List1[17] ; struct Linker *Menulist1;
    char List2[17] ; struct Linker *Menulist2;
    char List3[17] ; struct Linker *Menulist3;
} Menu;

extern Menu MainMenu, TimerMenu, Manual;

#endif

