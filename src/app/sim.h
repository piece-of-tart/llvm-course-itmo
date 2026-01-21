#pragma once

#define WIDTH_IN_PIXEL   1200
#define HEIGHT_IN_PIXEL  800
#define RADIUS           10

#define WIDTH  (WIDTH_IN_PIXEL / RADIUS)
#define HEIGHT (HEIGHT_IN_PIXEL / RADIUS)

extern "C" void Graphics_put_pixel(int x, int y, int r, unsigned argb);
extern "C" void Graphics_flush();