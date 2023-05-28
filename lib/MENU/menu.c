#include <menu.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>



/*========== MainMenu ==========*/
Menu MainMenu  = {
//  "                ",
    Main_Menu,
    NULL,
    " MENU",
    "  TIMER",&TimerMenu,
    "  MANUAL",&Manual,
    "  CLOCK MOD",NULL,
};

Menu TimerMenu = {
//  "                ",
    Default,
    &MainMenu,
    " TIMER FOR RELAY",
    "  RELAY 1-4     ",NULL,
    "  RELAY 5-8     ",NULL,
    "  CLEAR ALL DATA",NULL,
};

Menu Manual = {
//  "                ",
    Default,
    &MainMenu,
    "SET RELAY STATES",
    "  RELAY 1-4     ",NULL,
    "  RELAY 5-8     ",NULL,
    "  TOGGLE ALL    ",NULL,
};