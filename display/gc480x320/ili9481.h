#ifndef ILI9481_H
#define ILI9481_H

#include <inttypes.h>

#include "../glcd.h"

void ili9481Init(GlcdDriver **driver);

void ili9481Sleep(void);
void ili9481Wakeup(void);

void ili9481DrawPixel(int16_t x, int16_t y, uint16_t color);
void ili9481DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

void ili9481DrawImage(tImage *img);

#endif // ILI9481_H