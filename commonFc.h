#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include"math.h"
using namespace std;

static SDL_Window* window = NULL;
static SDL_Renderer* render = NULL;
static SDL_Event e;



static SDL_Texture* style_map[10];
static SDL_Texture* sprite_runright[16];
static SDL_Texture* sprite_runleft[16];
static SDL_Texture* sprite_attackright[10];
static SDL_Texture* sprite_attackleft[10];
static SDL_Texture* sprite_hit_right[4];
static SDL_Texture* sprite_hit_left[4];
static SDL_Texture* support_player[10];
static SDL_Texture* effect_apple[3];
static SDL_Texture* effect_apple2[4];
static SDL_Texture* effect_apple3[4];
static SDL_Texture* effect_apple3_right[4];
static SDL_Texture* idle_left = NULL;
static SDL_Texture* idle_right = NULL;
static SDL_Texture* effect_attack_special[5];
static SDL_Texture* sprite_attack_special_right = NULL;
static SDL_Texture* sprite_attack_special_left = NULL;
static SDL_Texture* sprite_bullet_special_right = NULL;
static SDL_Texture* sprite_bullet_special_left = NULL;

// goblin
static SDL_Texture* sprite_goblin_idle = NULL;
static SDL_Texture* sprite_goblin_idle1 = NULL;
static SDL_Texture* sprite_goblin_runright[9];
static SDL_Texture* sprite_goblin_runleft[9];
static SDL_Texture* sprite_goblin_attackright[7];
static SDL_Texture* sprite_goblin_attackleft[7];
static SDL_Texture* sprite_goblin_hit_right[4];
static SDL_Texture* sprite_goblin_hit_left[4];
static SDL_Texture* sprite_goblin_died_right[4];
static SDL_Texture* sprite_goblin_died_left[4];
static SDL_Texture* sprite_goblin_attack_bomb_right = NULL;
static SDL_Texture* sprite_goblin_attack_bomb_left = NULL;
static SDL_Texture* sprite_bomb_explode_right = NULL;
static SDL_Texture* sprite_bomb_explode_left = NULL;
static SDL_Texture* goblin_index_health = NULL;
static SDL_Texture* hit_animation[4];


// BOSS
static SDL_Texture* sprite_bullet_boss[3];
static SDL_Texture* sprite_boss_idle = NULL;
static SDL_Texture* sprite_boss_attacking = NULL;
static SDL_Texture* sprite_boss_hit[4];
static SDL_Texture* sprite_boss_died = NULL;
static SDL_Texture* sprite_boss_take_hit = NULL;
static SDL_Texture* shield_boss = NULL;



// interface
static SDL_Texture* button_start = NULL;
static SDL_Texture* button_start2 = NULL;
static SDL_Texture* button_help = NULL;
static SDL_Texture* button_help2 = NULL;
static SDL_Texture* button_exit = NULL;
static SDL_Texture* button_exit2 = NULL;
static SDL_Texture* decore_player_menu = NULL;
static SDL_Texture* decore_player_menu1 = NULL;


// sound
static Mix_Chunk* sound_player_attack = NULL;
static Mix_Chunk* sound_player_hit = NULL;	
static Mix_Music* sound_game_menu = NULL;
static Mix_Music* sound_game_start = NULL;
static Mix_Chunk* sound_goblin_hit = NULL;
static Mix_Chunk* sound_goblin_died = NULL;
static Mix_Chunk* sound_attack_apple = NULL;
static Mix_Chunk* sound_effect_apple = NULL;
static Mix_Chunk* sound_attack_hit_apple = NULL;
static Mix_Chunk* sound_run_player = NULL;
static Mix_Chunk* sound_game_over = NULL;
static Mix_Chunk* sound_explosion = NULL;
static Mix_Chunk* sound_game_victory = NULL;


// bien hang
const int window_w = 1280;
const int window_h = 640;
const int BBF = 32;
const int KEY_R = 167;
const int KEY_G = 175;
const int KEY_B = 180;
const int tile_block = 64;
const int MAX_ROWS = 12;
const int MAX_COLS = 460;

// biến hằng tính chất nhân vật 
const int PLAYER_START_X = 26000;
const int PLAYER_START_Y = 15;
const int PLAYER_MAX_HEALTH = 12;
const int PLAYER_WEIGHT = 70;
const int PLAYER_HEIGHT = 63;

