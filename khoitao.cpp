#include"khaibao.h"
#include"image.h"

int window_r = 1000;
int window_h = 800;
int backgroundset = 0;

SDL_Texture* metal[100];
SDL_Texture* back = NULL;
SDL_Window* window = NULL;
SDL_Renderer* render = NULL;


void huy() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(back);
	SDL_DestroyTexture(metal[0]);
	SDL_Quit();
}



bool khoitao() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << SDL_GetError();
		return false;
	}
	window = SDL_CreateWindow("Pixel Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_r, window_h, SDL_WINDOW_SHOWN);
	if (!window) {
		cout << SDL_GetError();
		return false;
	}
	render = SDL_CreateRenderer(window, -1, 0);
	if (!render) {
		cout << SDL_GetError();
		return false;
	}
	return true;
}


