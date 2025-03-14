#ifndef image_h
#define image_h
#include"khaibao.h"
#include<iostream>
using namespace std;
extern SDL_Texture* back;
extern SDL_Texture* metal[100];
extern SDL_Renderer* render;
bool upload() {
	int m = IMG_INIT_PNG;
	if (!(IMG_Init(m) & m)) {
		cout << IMG_GetError();
		return false;
	}
	SDL_Surface* surface = IMG_Load("Purple.png");
	if (surface==NULL) {
		cout << IMG_GetError();
		return false;
	}
	back = SDL_CreateTextureFromSurface(render, surface);
	if (!back) {
		cout << SDL_GetError();
		return false;
	}
	return true;
}
// xay dung map-------------------------------------------------------------------<>----------------------------------------------------------------------
SDL_Texture* loadmeta(const char *path) {
	SDL_Texture* meta = NULL;
	int m = IMG_INIT_PNG;
	if (!(IMG_Init(m) & m)) {
		cout << IMG_GetError();
	}
	SDL_Surface* surface1 = IMG_Load(path);
	if (surface1 == NULL) {
		cout << IMG_GetError();
	}
	else {
		meta = SDL_CreateTextureFromSurface(render, surface1);
		if (!meta) {
			cout << SDL_GetError();
		}
	}
	return meta;
}

int loading() {
	metal[0] = loadmeta("Terrain (16x16).png");
	if (metal[0]==NULL) {
		cout << SDL_GetError();
		return 0;
	}
	metal[1] = loadmeta("Brown.png");
	if (metal[1] == NULL) {
		cout << SDL_GetError();
		return 0;
	}
		metal[2] = loadmeta("Terrain (16x16)3.png");
	if (metal[2] == NULL) {
		cout << SDL_GetError();
		return 0;
	}
	return 1;
}
int wood_x = 50;
int wood_w = 60;
void inmeta() {
	SDL_Rect rect = { 50,-20,100,60 };
	SDL_RenderCopy(render, metal[0], NULL, &rect);

	for (int i = 1; i < 14; i++) {
		rect = { wood_x + i*wood_w,-20,100,60 };
		SDL_RenderCopy(render, metal[0], NULL, &rect);
	}

	rect = { wood_x + 14 * wood_w,-20,70,60 };
	SDL_RenderCopy(render, metal[0], NULL, &rect);
		
	SDL_Rect rect1 = { 50,675,150,150 };
	SDL_RenderCopy(render, metal[2], NULL, &rect1);
}


void movebackground(int set) {
	SDL_Rect rect1 = { 80,set,840,800 };
	SDL_RenderCopy(render, metal[1], NULL, &rect1);
	if (set < 800) {
		SDL_Rect rect2 = { 80,set+800,840,800 };
		SDL_RenderCopy(render, metal[1], NULL, &rect2);
	}
}


#endif // !image_h

