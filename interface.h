#pragma once
#include"commonFc.h"
#include"player.h"
#include"sound.h"
#include"game status.h"
class interface : public player {
public:
	int check_eat_apple;
	int apple_x;
	int apple_y;
	bool status_sound;
	TTF_Font* font;
	interface();



	~interface();

	bool load_picture(SDL_Renderer* render);
	void position_blood_index(SDL_Renderer* render,player p1);
	void spamw_apple(SDL_Renderer* render, camera cam);
	void render_button_sound(SDL_Renderer* render, camera cam, sound_manager& sound, status_game& status);
	void check_eat_apple_(player& p1);
	void render_energy(SDL_Renderer* render, player p1);
	void render_energy2(SDL_Renderer* render, player p1,camera cam);
	void render_kill_count(SDL_Renderer* render, int kill,int score);

private:
	SDL_Texture* health;
	SDL_Texture* background_blood;
	 SDL_Texture* enegy_index;
	 SDL_Texture* enegy_index2;

};