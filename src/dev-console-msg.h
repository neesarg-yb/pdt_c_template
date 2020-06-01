#pragma once

void DevConsoleMessagesPush(char const *msg, int maxNumMsg);
void DevConsoleMessagesClearAll(void);

int         GetDevConsoleMessagesCount(void);
char const* GetDevConsoleMessage(int index);