#include <menu.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>



/*========== MainMenu ==========*/
Menu MainMenu  = {
//  "                ",
    Main_Menu,
    NULL,
    " MENU", NULL,
    "  TIMER",&TimerMenu,
    "  MANUAL",&Manual,
    "  CLOCK MOD",NULL,
};

Menu TimerMenu = {
//  "                ",
    Got_Title,
    &MainMenu, 
    " TIMER FOR RELAY",NULL,
    "  RELAY 1-4     ",&Relay14Timer,
    "  RELAY 5-8     ",&Relay58Timer,
    "  CLEAR ALL DATA",NULL,
};

Menu Manual = {
//  "                ",
    Got_Title,
    &MainMenu,
    " MANUAL SETTING ",NULL,
    "  ON/OFF RELAY  ",&OnOffState,
    "  SET TIME/DAY  ",NULL,
    "  ALARM SOUND   ",NULL,
};

Menu SetInTime = {
//  "                ",
    Got_Title,
    &Manual,
    " FORMAT:        ",NULL,
    " |              ",NULL,
    " HOURE FORMAT:  ",NULL,
    " |              ",NULL,
};

Menu OnOffState = {
//  "                ",
    Got_Title,
    &Manual,
    "SET RELAY STATES",NULL,
    "  RELAY 1-4     ",&Relay14Toggle,
    "  RELAY 5-8     ",&Relay58Toggle,
    "  TOGGLE ALL    ",NULL,
};

Menu Relay14Toggle = {
//  "                ",
    Relay14Set,
    &OnOffState,
    "  RELAY 1 |   ",NULL,
    "  RELAY 2 |   ",NULL,
    "  RELAY 3 |   ",NULL,
    "  RELAY 4 |   ",NULL,
};

Menu Relay58Toggle = {
//  "                ",
    Relay58Set,
    &OnOffState,
    "  RELAY 5 |   ",NULL,
    "  RELAY 6 |   ",NULL,
    "  RELAY 7 |   ",NULL,
    "  RELAY 8 |   ",NULL,
};

Menu Relay14Timer = {
//  "                ",
    Relay14T,
    &TimerMenu,
    "  RELAY 1       ",NULL,
    "  RELAY 2       ",NULL,
    "  RELAY 3       ",NULL,
    "  RELAY 4       ",NULL,
};

Menu Relay58Timer = {
//  "                ",
    Relay58T,
    &TimerMenu,
    "  RELAY 5       ",NULL,
    "  RELAY 6       ",NULL,
    "  RELAY 7       ",NULL,
    "  RELAY 8       ",NULL,
};