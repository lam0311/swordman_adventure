#include"interface.h"

interface::interface() {
	health = NULL;
	background_blood = NULL;
	enegy_index = NULL;
	apple_x = APPLE_X;
	apple_y = APPLE_Y;
	status_sound = true;
	check_eat_apple = 0;
	font = NULL;
}
interface::~interface() { ; }


bool interface::load_picture(SDL_Renderer* render) {
	health = Loadsprite("picture/Health.png", render);
	enegy_index = Loadsprite("picture/thanh nang luong.png", render);
	background_blood = Loadsprite("picture/blood_index.png", render);
	support_player[0] = Loadsprite("picture/Food.png", render);
	enegy_index2 = Loadsprite("picture/thanh no.png", render);
	button_sound_on = Loadsprite("picture/music_on.png", render);
	button_sound_off = Loadsprite("picture/music_off.png", render);

	return health && enegy_index && background_blood && support_player[0] && enegy_index2 && button_sound_off && button_sound_on;
}


void interface::render_button_sound(SDL_Renderer* render, camera cam, sound_manager& sound, status_game& status) {
	SDL_Rect rect_sound = { 1200, 0, 50, 50 };
	int mouse_x_new, mouse_y_new;
	Uint32 mouse_state = SDL_GetMouseState(&mouse_x_new, &mouse_y_new);

	if ((mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
		mouse_x_new > rect_sound.x && mouse_x_new < rect_sound.x + rect_sound.w &&
		mouse_y_new > rect_sound.y && mouse_y_new < rect_sound.y + rect_sound.h) {

		status_sound = !status_sound; 
		SDL_Delay(150);
	}

	if (status_sound) {
		sound.play_game_start_sound();
		SDL_RenderCopy(render,  button_sound_on, NULL, &rect_sound);
	}
	else {
		sound.stop_game_start_sound();
		SDL_RenderCopy(render, button_sound_off, NULL, &rect_sound);
	}
}


void interface::position_blood_index(SDL_Renderer* render,player p1) {

	SDL_Rect rect1 = { 0,0,360 ,30 };
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
		if (p1.player_heath > 12) {
			p1.player_heath = 12;
		}
		check_eat_apple = 1;
	}
}

void interface::render_kill_count(SDL_Renderer* render, int kill,int score) {

     font = TTF_OpenFont("VHANTIQ.TTF", 24);
	if (!font) {
		cout << TTF_GetError() << std::endl;
	}

	SDL_Color gold = { 255, 215, 0 };  
	SDL_Color red = { 255, 50, 50 };  

	string score_text = "Score: " +to_string(score);
	string kill_text = "Kills: " + to_string(kill);

	SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_text.c_str(), gold);
	SDL_Surface* kill_surface = TTF_RenderText_Solid(font, kill_text.c_str(), red);

	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(render, score_surface);
	SDL_Texture* kill_texture = SDL_CreateTextureFromSurface(render, kill_surface);

	SDL_Rect score_rect = { 800, 10, score_surface->w, score_surface->h };
	SDL_Rect kill_rect = { 10, 50, kill_surface->w, kill_surface->h };

	SDL_RenderCopy(render, score_texture, NULL, &score_rect);
	SDL_RenderCopy(render, kill_texture, NULL, &kill_rect);

	SDL_FreeSurface(score_surface);
	SDL_FreeSurface(kill_surface);
	SDL_DestroyTexture(score_texture);
	SDL_DestroyTexture(kill_texture);
}