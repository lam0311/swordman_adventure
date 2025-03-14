#pragma once
#include"commonFc.h"
class base {
public:
	base();
	~base();

	void setrect(const int& x, const int& y) { rect.x = x; rect.y = y; }

	SDL_Rect getrect() const { return rect; }

	SDL_Texture* getbase_oj() const { return base_oj; }

	bool loadimg(const char* path, SDL_Renderer* render,int w,int h);
	void positionimg(SDL_Renderer* render,int set);
	void free();

private:
	SDL_Texture* base_oj;
	SDL_Rect rect;
};