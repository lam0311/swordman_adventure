#pragma once
#include"commonFc.h"
#include"base oj.h"
enum GAME {
    START,
    MENU,
    HELP,
    START_AGAIN,
	GAME_OVER
};
class status_game {
public:
    int mouse_x;
    int mouse_y;
    int frame_menu_player;
	Uint32 time_menu_player;
    GAME GO;
    status_game() {
        mouse_x = 0;
        mouse_y = 0;
		frame_menu_player = 0;
		time_menu_player = 0;
        GO = MENU;
    }

    SDL_Texture* load_(const char* path, SDL_Renderer* render) {
        int n = IMG_INIT_PNG;
        if (!(IMG_Init(n) & n)) {
            return NULL;
        }
        SDL_Texture* sprite = NULL;
        SDL_Surface* surface3 = IMG_Load(path);
        if (surface3 == NULL) {
            cout << IMG_GetError();
            return NULL;
        }

        else {
            sprite = SDL_CreateTextureFromSurface(render, surface3);
            SDL_FreeSurface(surface3);
            if (!sprite) {
                cout << "khong the tai anh";
                cout << SDL_GetError();
            }
        }
        return sprite;
    }
    bool load_button(SDL_Renderer* render);
	void render_decore_menu(SDL_Renderer* render);

    void GAME_OVER(SDL_Renderer* render, base game_over);
    void GAME_MENU(SDL_Renderer* render, base game_menu);
};