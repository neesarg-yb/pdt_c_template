#pragma once
#include "pd_api.h"

void AppInit(PlaydateAPI* playdate);
void AppTerminate(void);

void AppUpdate(void);
int  AppRender(void);