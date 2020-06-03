#pragma once
#include "stdbool.h"
#include "pd_api.h"
#include "debug-utils/dev-window.h"

// Declare common resources, shared by game code
//-----------------------------------------------
extern PlaydateAPI* g_pd;               // Set by AppInit
extern LCDFont* g_font;                 // Set by AppInit
extern LCDBitmap* g_devWindowBitmap;    // Set by DevWindowInit
extern LCDBitmap* g_optionsMenuBitmap;  // Set by DevWindowInit

extern bool g_isOptionsMenuOpen;        // Defined by options-menu.c
extern bool g_isDevWindowActive;        // Defined by dev-window.c
extern bool g_isStepThroughOn;          // Defined by app.c
