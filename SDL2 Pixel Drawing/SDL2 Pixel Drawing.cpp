#include <iostream>
#include <SDL.h>
using namespace std;

int main(int argc, char* argv[]) {
	bool leftMouseButtonDown = false;
	bool quit = false;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("SDL2 Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);

	int* pixels = new int[640 * 480 * sizeof(Uint32)];

	memset(pixels, 255, 640 * 480 * sizeof(Uint32));

	Uint32 color;
	Uint8 red, green, blue;


	while (!quit) {
		int ticks = SDL_GetTicks();
		red = (1 + sin(ticks * 0.0002)) * 128;
		green = (1 + sin(ticks * 0.0001)) * 128;
		blue = (1 + sin(ticks * 0.0003)) * 128;
		color = 0xFF;
		color <<= 8;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftMouseButtonDown = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				leftMouseButtonDown = true;
			}
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown) {
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				for (int i = -2; i < 3; i++) {
					for (int j = -2; j < 3; j++) {
						int x = mouseX + i;
						int y = mouseY + j;
						if (x < 0 || x>640 || y < 0 || y>480) {
							continue;
						} else {
							pixels[(mouseX + i) + ((mouseY + j) * 640)] = color;
						}
					}
				}
				/*pixels[mouseX + (mouseY * 640)] = 0;
				pixels[(mouseX + 1) + (mouseY * 640)] = 0;
				pixels[(mouseX - 1) + (mouseY * 640)] = 0;
				pixels[mouseX + ((mouseY + 1) * 640)] = 0;
				pixels[(mouseX + 1) + ((mouseY + 1) * 640)] = 0;
				pixels[(mouseX - 1) + ((mouseY + 1) * 640)] = 0;
				pixels[mouseX + ((mouseY - 1) * 640)] = 0;
				pixels[(mouseX + 1) + ((mouseY - 1) * 640)] = 0;
				pixels[(mouseX - 1) + ((mouseY - 1) * 640)] = 0;*/
			}
			break;
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	delete[] pixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
