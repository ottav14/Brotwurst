#include "draw.h"

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF

#define PI 3.14159265358979323846


int validCoord(int x, int y, Screen* screen) {
	return 0 <= x && x < screen->width && 0 <= y && y < screen->height;
}

void bufferPixel(int x, int y, unsigned long color, Screen* screen) {
	screen->pixels[y * (screen->pitch / 4) + x] = color; 
}

void bufferCircle(double cx, double cy, double r, unsigned long color, Screen* screen) {

		int sample_count = 300;
		for(double t = 0; t < 2*PI; t += 2*PI/sample_count) {
			int x = (int)(cx + (r * cos(t)));
			int y = (int)(cy + (r * sin(t)));
			if(validCoord(x, y, screen))
				bufferPixel(x, y, color, screen);
		}

}


void bufferRect(int x0, int y0, int w, int h, unsigned long color, Screen* screen) {

        for (int y = y0; y < y0+h; ++y)
            for (int x = x0; x < x0+w; ++x)
				bufferPixel(x, y, color, screen);
}

Screen* enableDrawMode(SDL_Texture* texture, int _width, int _height) {

	uint32_t *_pixels;
	int _pitch;
	SDL_LockTexture(texture, NULL, (void **)&_pixels, &_pitch);

	Screen* screen = (Screen*)malloc(sizeof(Screen));
	screen->pixels = _pixels;
	screen->pitch = _pitch;
	screen->width = _width;
	screen->height = _height;

	return screen;

}
