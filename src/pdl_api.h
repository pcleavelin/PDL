#pragma once
#include <stdbool.h>
#include <stdint.h>

void PDLShowWindow();
void PDLHideWindow();
void PDLResizeWindow(uint32_t width, uint32_t height);
void PDLCloseWindow();

void PDLBlit(uint32_t *bitmap);

uint8_t PDLGetKey(uint8_t key);

bool PDLDoWindowMessages();
bool PDLInit(const char *title, uint32_t title_len, uint32_t x, uint32_t y,
             uint32_t width, uint32_t height);