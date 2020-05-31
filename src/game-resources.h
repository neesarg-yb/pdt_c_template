#pragma once
#include "stdbool.h"
#include "pd_api.h"
#include "dev-window.h"

// Declare common resources, shared by game code
//-----------------------------------------------
extern PlaydateAPI* g_pd;               // Set by AppInit
extern LCDFont* g_font;                 // Set by AppInit
extern LCDBitmap* g_devBitmap;          // Set by DevWindowInit
extern LCDBitmap* g_devMenuBitmap;      // Set by DevWindowInit
extern DevWindowState g_devWindowState; // Used by dev-window.c

extern bool g_isOptionsMenuOpen;        // Defined by options-menu.c
extern bool g_isDevWindowActive;        // Defined by dev-window.c
extern bool g_isStepThroughOn;          // Defined by app.c
