#pragma once
#include"commonFc.h"
#include"player.h"
class interface : public player {
public:
	int check_eat_apple;
	int apple_x;
	int apple_y;

	interface();



	~interface();

	bool blood_index(SDL_Renderer* render);
	void position_blood_index(SDL_Renderer* render,player p1);
	void spamw_apple(SDL_Renderer* render, camera cam);
	void check_eat_apple_(player& p1);
	void render_energy(SDL_Renderer* render, player p1);
	void render_energy2(SDL_Renderer* render, player p1,camera cam);

private:
	SDL_Texture* health;
	SDL_Texture* background_blood;
	 SDL_Texture* enegy_index;
	 SDL_Texture* enegy_index2;

};