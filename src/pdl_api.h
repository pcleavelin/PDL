#pragma once
#include <stdbool.h>
#include <stdint.h>

void PDLShowWindow();
void PDLHideWindow();
void PDLResizeWindow(uint32_t width, uint32_t height);
void PDLCloseWindow();

bool PDLDoWindowMessages();
bool PDLInit();