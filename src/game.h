#pragma once
#include "pd_api.h"

void GameInit(PlaydateAPI* playdate);
void GameTerminate(void);

void GameUpdate(void);
int  GameRender(void);
