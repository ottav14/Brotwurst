#ifndef DRAW_H
#define DRAW_H

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF

#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>

typedef struct {
	uint32_t* pixels;
	int pitch;
	int width;
	int height;
} Screen;

int validCoord(int x, int y, Screen* screen);
void bufferPixel(int x, int y, unsigned long color, Screen* screen);
void bufferCircle(double cx, double cy, double r, unsigned long color, Screen* screen);
void bufferRect(int x0, int y0, int w, int h, unsigned long color, Screen* screen);
Screen* enableDrawMode(SDL_Texture* texture, int _width, int _height);

#endif
