#pragma once
#include <stdio.h>

void DevWindowInit(void);
void DevWindowTerminate(void);

void DevWindowUpdate(float const deltaSeconds);
void DevWindowRender(void);

void DevWindowPrint(char const* msg);
