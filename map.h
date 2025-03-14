#pragma once
#include"base oj.h"
#include"commonFc.h"
#include"player.h"
class map {
public:
	void readfile();
	bool loadTile(SDL_Renderer* render, const char* path, int i);
	void rendermap(SDL_Renderer* render, camera cam);
	const int(&getmap() const)[MAX_ROWS][MAX_COLS]{
	   return tile_map;
	}
private:
	int tile_map[MAX_ROWS][MAX_COLS];
};