#include"game status.h"



bool status_game::load_button(SDL_Renderer* render) {
	button_start = load_("picture/start_button1.png", render);
	button_start2 = load_("picture/start_button2.png", render);
	button_exit = load_("picture/exit_button1.png", render);
	button_exit2 = load_("picture/exit_button2.png", render);
	button_help = load_("picture/help_button1.png", render);
	button_help2 = load_("picture/help_button2.png", render);
	decore_player_menu = load_("picture/player_IDLE_menu.png", render);
	decore_player_menu1 = load_("picture/player_IDLE_menu1.png", render);

	if (!button_start || !button_start2 || !button_exit || !button_exit2 || !button_help || !button_help2
		|| !decore_player_menu || !decore_player_menu1) {
		cout << SDL_GetError();
		return false;
	}
	
		return true;
}

void status_game::GAME_OVER(SDL_Renderer* render, base game_over, TTF_Font* font) {

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    SDL_Delay(200);

    game_over.positionimg(render, NULL);

	// Hiển thị số kill
	SDL_Color red = { 255, 50, 50 };
	string kill_text = "Enemies Defeated: " + to_string(kill_count);
	SDL_Surface* kill_surface = TTF_RenderText_Solid(font, kill_text.c_str(), red);
	SDL_Texture* kill_texture = SDL_CreateTextureFromSurface(render, kill_surface);
	SDL_Rect kill_rect = { 440, 200, kill_surface->w+100, kill_surface->h+60 };
	SDL_RenderCopy(render, kill_texture, NULL, &kill_rect);

	// Hiển thị điểm số
	string score_text = "Score: " + to_string(score);
	SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_text.c_str(), { 255, 165, 0 }); 
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(render, score_surface);
	SDL_Rect score_rect = { 500, 300, score_surface->w+100, score_surface->h+60 };
	SDL_RenderCopy(render, score_texture, NULL, &score_rect);

	SDL_FreeSurface(kill_surface);
	SDL_FreeSurface(score_surface);
	SDL_DestroyTexture(kill_texture);
	SDL_DestroyTexture(score_texture);
	SDL_RenderPresent(render);

	SDL_Rect start_again = { 355,450,260,100 };
	SDL_Rect menu = { 680,450,240,100 };
    
	if (mouse_x > start_again.x && mouse_x < start_again.x + start_again.w &&
		mouse_y > start_again.y && mouse_y < start_again.y + start_again.h) {
        mouse_x = 0;
        mouse_y = 0;
        GO = START_AGAIN;
    }
	if (mouse_x > menu.x && mouse_x < menu.x + menu.w &&
		mouse_y > menu.y && mouse_y < menu.y + menu.h) {
		mouse_x = 0;
		mouse_y = 0;
		GO = MENU;
	}

    SDL_RenderPresent(render);
}

void status_game::GAME_VICTORY_(SDL_Renderer* render, TTF_Font* font) {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render); 

	SDL_Texture* victory_texture = load_("picture/background_victory.png",render);
	SDL_RenderCopy(render, victory_texture, NULL, NULL);

	// Hiển thị số kill
	SDL_Color red = { 255, 50, 50 };
	string kill_text = "Enemies Defeated: " + to_string(kill_count);
	SDL_Surface* kill_surface = TTF_RenderText_Solid(font, kill_text.c_str(), red);
	SDL_Texture* kill_texture = SDL_CreateTextureFromSurface(render, kill_surface);
	SDL_Rect kill_rect = { 450, 350, kill_surface->w+140, kill_surface->h+50 };
	SDL_RenderCopy(render, kill_texture, NULL, &kill_rect);

	// Hiển thị điểm số
	string score_text = "Score: " + to_string(score);
	SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_text.c_str(), { 255, 215, 0 });
	SDL_Texture* score_texture = SDL_CreateTextureFromSurface(render, score_surface);
	SDL_Rect score_rect = { 510, 450, score_surface->w+140, score_surface->h+50 };
	SDL_RenderCopy(render, score_texture, NULL, &score_rect);

	// Hiển thị hướng dẫn quay lại menu
	SDL_Color green = { 245, 66, 191 };
	std::string instruction_text = "Press ENTER to return to menu";
	SDL_Surface* instruction_surface = TTF_RenderText_Solid(font, instruction_text.c_str(), green);
	SDL_Texture* instruction_texture = SDL_CreateTextureFromSurface(render, instruction_surface);
	SDL_Rect instruction_rect = { 430, 550, instruction_surface->w, instruction_surface->h };
	SDL_RenderCopy(render, instruction_texture, NULL, &instruction_rect);

	SDL_FreeSurface(kill_surface);
	SDL_FreeSurface(score_surface);
	SDL_FreeSurface(instruction_surface);
	SDL_DestroyTexture(kill_texture);
	SDL_DestroyTexture(score_texture);
	SDL_DestroyTexture(instruction_texture);
	SDL_RenderPresent(render);
}

void status_game::render_decore_menu(SDL_Renderer* render) {
	Uint32 current_time = SDL_GetTicks();
	if (current_time - time_menu_player > 100) {
		frame_menu_player = (frame_menu_player + 1) % 10;
		time_menu_player = current_time;
	}

	SDL_Rect rect1 = { 96*frame_menu_player,0,96,96 };
	SDL_Rect rect = { -70, -30, 700, 700};
	SDL_RenderCopy(render, decore_player_menu, &rect1, &rect);

	SDL_Rect rect2 = { 96 * (9-frame_menu_player),0,96,96 };
	SDL_Rect rect3 = { 670, -30, 700, 700 };
	SDL_RenderCopy(render, decore_player_menu1, &rect2, &rect3);
}

void status_game::GAME_MENU(SDL_Renderer* render, base game_menu) {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);

	game_menu.positionimg(render, NULL);
	render_decore_menu(render);

	int mouse_x_new, mouse_y_new;
	SDL_GetMouseState(&mouse_x_new, &mouse_y_new);
	
	SDL_Rect rect_start = { 520, 240, 250, 60 };
	SDL_Rect rect_exit = { 520, 330, 250, 60 };
	SDL_Rect rect_help = { 520, 420, 250, 60 };

	if (mouse_x_new > rect_start.x && mouse_x_new < rect_start.x + rect_start.w &&
		mouse_y_new > rect_start.y && mouse_y_new < rect_start.y + rect_start.h) {
		SDL_RenderCopy(render, button_start2, NULL, &rect_start);
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) GO = START;
	}
	else {
		SDL_RenderCopy(render, button_start, NULL, &rect_start);
	}

	if (mouse_x_new > rect_exit.x && mouse_x_new < rect_exit.x + rect_exit.w &&
		mouse_y_new > rect_exit.y && mouse_y_new < rect_exit.y + rect_exit.h) {
		SDL_RenderCopy(render, button_exit2, NULL, &rect_exit);
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) GO = QUIT;
	}
	else {
		SDL_RenderCopy(render, button_exit, NULL, &rect_exit);
	}

	if (mouse_x_new > rect_help.x && mouse_x_new < rect_help.x + rect_help.w &&
		mouse_y_new > rect_help.y && mouse_y_new < rect_help.y + rect_help.h) {
		SDL_RenderCopy(render, button_help2, NULL, &rect_help);
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) GO = HELP;
	}
	else {
		SDL_RenderCopy(render, button_help, NULL, &rect_help);
	}
	mouse_x_new = 0;
	mouse_y_new = 0;
	SDL_RenderPresent(render);
}
