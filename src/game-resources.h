#pragma once
#include "pd_api.h"

// Declare common resources, shared by game code
//-----------------------------------------------
extern PlaydateAPI* g_pd;   // Set right before GameStart
extern LCDFont* g_font;     // Set by GameStart