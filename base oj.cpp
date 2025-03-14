#include"commonFc.h"
#include"base oj.h"
base::base() {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	base_oj = NULL;
}


base::~base() {
	free();
}


bool base::loadimg(const char* path, SDL_Renderer* render,int w,int h) {
	SDL_Texture* newpicture = NULL;
	int m = IMG_INIT_PNG;
	if (!(IMG_Init(m) & m)) {
		cout << IMG_GetError();
		return false;
	}

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		cout << IMG_GetError();
		return false;
	}


	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, KEY_R, KEY_G, KEY_B));


	newpicture = SDL_CreateTextureFromSurface(render, surface);

	if (!newpicture) {
		cout << SDL_GetError();
		return false;
	}

	rect.w = w;
	rect.h = h;
	SDL_FreeSurface(surface);



	base_oj = newpicture;
	if (!base_oj) {
		cout << SDL_GetError();
		return false;
	}
	return true;

}



void base::positionimg(SDL_Renderer* render,int set) {
	/*SDL_Rect rectps = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(render, base_oj, clip, &rectps);*/
	
		SDL_Rect rec1 = { set,0,window_w,window_h };
		SDL_RenderCopy(render, base_oj, NULL, &rec1);
		if (set < 800) {
			SDL_Rect rec2 = { set + window_w,0,window_w,window_h };
			SDL_RenderCopy(render, base_oj, NULL, &rec2);
		}
}


void base::free() {

	if (base_oj == NULL) {
		SDL_DestroyTexture(base_oj);
		rect.x = 0;
		rect.y = 0;
		rect.w = 0;
		rect.h = 0;
	}
}