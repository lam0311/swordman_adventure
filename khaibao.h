#ifndef khaibao
#define khaibao
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<iostream>
#include"khaibao.h"
#include"gameloop.h"
using namespace std;


extern SDL_Window* window ;
extern SDL_Renderer* render;
extern int window_r;
extern int window_h;
extern int backgroundset;

extern SDL_Texture* metal[100];
extern SDL_Texture* back;



void gameloop();
bool khoitao();
void huy();
bool upload();
int loading();


#endif

