#include"interface.h"

interface::interface() {
	health = NULL;
	background_blood = NULL;
	enegy_index = NULL;
	apple_x = 18040;
	apple_y = 290;
	check_eat_apple = 0;
}
interface::~interface() { ; }


bool interface::blood_index(SDL_Renderer* render) {

	health = Loadsprite("picture/Health.png", render);
	if (health == NULL) {
		return false;
	}

	enegy_index = Loadsprite("picture/thanh nang luong.png", render);
	if (enegy_index == NULL) {
		return false;
	}

	background_blood = Loadsprite("picture/blood_index.png", render);
	if (background_blood == NULL) {
		return false;
	}


	support_player[0] = Loadsprite("picture/Food.png", render);
	if (!support_player[0]) {
		return false;
	}
	enegy_index2 = Loadsprite("picture/thanh no.png", render);
	if (!enegy_index2) {
		return false;
	}
	

	return true;

}

void interface::position_blood_index(SDL_Renderer* render,player p1) {

	SDL_Rect rect1 = { 0,0,28 * p1.player_heath+24 ,30 };
	SDL_RenderCopy(render, background_blood, NULL, &rect1);

	for (int i = 0; i < p1.player_heath; i++) {
		SDL_Rect rect = { 28 * i+9,5,24,24 };
		SDL_RenderCopy(render, health, NULL, &rect);
	}

}


void interface::render_energy(SDL_Renderer* render, player p1) {

	SDL_Rect rect = { 4, 30, 260, 15 };
	SDL_RenderCopy(render, background_blood, NULL, &rect);

	int energy_width = (25 * p1.energy); 
	SDL_Rect rect1 = { 8, 30, energy_width, 13 }; 
	SDL_RenderCopy(render, enegy_index, NULL, &rect1);	
}

void interface::render_energy2(SDL_Renderer* render, player p1,camera cam) {
	if (p1.charging) {
		SDL_Rect rect = { p1.player_x - cam.camera_x - 50, p1.player_y - cam.camera_y - 160, 153, 15 };
		SDL_RenderCopy(render, background_blood, NULL, &rect);

		Uint32 charge_duration = SDL_GetTicks() - p1.charge_start;
		int energy_width = (150 * charge_duration) / p1.charge_time;

		if (energy_width > 150) {
			energy_width = 150;
		}
		SDL_Rect charge_bar = { p1.player_x-cam.camera_x-50, p1.player_y-cam.camera_y-160, energy_width, 15 };
		SDL_RenderCopy(render, enegy_index2, NULL, &charge_bar);
	}

}

void interface::spamw_apple(SDL_Renderer* render, camera cam) {
	SDL_Rect rect = {  apple_x- cam.camera_x, apple_y- cam.camera_y, 34, 34 };
	SDL_RenderCopy(render, support_player[0], NULL, &rect);
}


void interface::check_eat_apple_(player& p1) {
	if (apple_x < p1.player_x + p1.player_w && apple_x + 34 > p1.player_x && apple_y < p1.player_y + p1.player_h && apple_y + 34 > p1.player_y) {
		apple_x = 0;
		apple_y = 0;
		p1.player_heath += 5;
		check_eat_apple = 1;
	}
}