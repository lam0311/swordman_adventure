#include"game status.h"



bool status_game::load_button(SDL_Renderer* render) {
	button_start = load_("picture/_Pngtree_the_start_button_2152504-removebg-preview.png", render);
	if (button_start == NULL) {
		return false;
	}

	decore_player_menu = load_("picture/player_IDLE_menu.png", render);
	if (decore_player_menu == NULL) {
		return false;
	}
	decore_player_menu1 = load_("picture/player_IDLE_menu1.png", render);
	if (decore_player_menu1 == NULL) {
		return false;
	}

	return true;
}

void status_game::GAME_OVER(SDL_Renderer* render, base game_over) {

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    SDL_Delay(200);

    game_over.positionimg(render, NULL);


    if (mouse_x > 355 && mouse_x < 355 + 260 && mouse_y>450 && mouse_y < 450 + 100) {
        mouse_x = 0;
        mouse_y = 0;
        GO = START_AGAIN;
    }
	if (mouse_x > 680 && mouse_x < 680 + 240 && mouse_y>450 && mouse_y < 450 + 100) {
		mouse_x = 0;
		mouse_y = 0;
		GO = MENU;
	}

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
    
    
	SDL_Rect rect = { 520,170,250,150 };
	SDL_RenderCopy(render, button_start, NULL, &rect);
    if (mouse_x > 520 && mouse_x < 520 + 250 && mouse_y>170 && mouse_y < 170 + 150) {
		mouse_x = 0;
		mouse_y = 0;
		GO = START;
    }
    
    
    
    
    
    
    
    SDL_RenderPresent(render);


}