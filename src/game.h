#pragma once
#include "pd_api.h"

void GameInit(PlaydateAPI* playdate);
void GameTerminate(void);

void GameUpdate(float const deltaSeconds);
int  GameRender(void);
void GameRenderPrompt(void);