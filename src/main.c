#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include "draw.h"

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000
#define WHITE 0xFFFFFF

#define PI 3.14159265358979323846

#define WIDTH 800
#define HEIGHT 600


int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("BEANTOWN",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT, 0);
    if (!window) {
        SDL_Quit();
        return -1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Create a texture
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             800, 600);

	// Circle
	double circle_x = WIDTH/2.0;
	double circle_y = HEIGHT/2.0;
	double circle_r = 50;

    // Main loop
    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

		double speed = 0.2;
		double next_pos = circle_y + circle_r + speed;
		if(next_pos < 0 || next_pos >= HEIGHT)
			speed *= -1;
		circle_y += speed;
		
		Screen* screen = enableDrawMode(texture, WIDTH, HEIGHT);
		
		bufferRect(0, 0, WIDTH, HEIGHT, BLACK, screen);
		bufferCircle(circle_x, circle_y, circle_r, BLUE, screen);

        SDL_UnlockTexture(texture);

        // Clear the renderer and copy the texture
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

