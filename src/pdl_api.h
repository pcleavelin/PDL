#pragma once
#include <stdbool.h>

void PDLShowWindow();
void PDLHideWindow();
void PDLResizeWindow(unsigned int width, unsigned int height);
void PDLCloseWindow();

bool PDLDoWindowMessages();
bool PDLInit();