#pragma once
#include "pd_api.h"
#include "dev-window.h"

// Declare common resources, shared by game code
//-----------------------------------------------
extern PlaydateAPI* g_pd;               // Set by GameInit
extern LCDFont* g_font;                 // Set by GameInit
extern LCDBitmap* g_devBitmap;          // Set by DevWindowInit
extern LCDBitmap* g_devMenuBitmap;      // Set by DevWindowInit
extern DevWindowState g_devWindowState; // Used by dev-window.c
