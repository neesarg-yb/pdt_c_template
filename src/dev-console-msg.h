#pragma once

void DevConsoleMessagesPush(char const *msg);
void DevConsoleMessagesClearAll(void);

int         GetDevConsoleMessagesCount(void);
char const* GetDevConsoleMessage(int index);