#pragma once
#include <stdio.h>

typedef enum DevWindowState
{
    kDevWindowOptionsMenu = 0,
    kDevWindowConsole = 1,
    kDevWindowClosed = 2
} DevWindowState;

void DevWindowInit(void);
void DevWindowTerminate(void);

void DevWindowUpdate(float const deltaSeconds);
void DevWindowUpdate_OptionsMenu(void);
void DevWindowUpdate_Console(void);

void DevWindowRender(void);
void DevWindowRender_OptionsMenu(void);
void DevWindowRender_Console(void);

void DevWindowPrint(char const* msg);
