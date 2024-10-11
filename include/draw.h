#ifndef DRAW_H
#define DRAW_H

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	SDL_Renderer* renderer;
	int width;
	int height;
} Screen;

void fillCircle(int cx, int cy, int r, Screen* screen);

#endif
