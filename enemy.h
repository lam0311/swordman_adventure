#pragma once
#include"commonFc.h"
#include"player.h"
#include"bullet.h"
enum state_goblin {
	STANDUP,
	RUNLEFT,
	RUNRIGHT,
	ATTACK_GOBLIN,
	ATTACK_BOMB
};
class enemy:public player {
public:
	// tính chất goblin =====
	int enemy_x;
	int enemy_y;
	int enemy_w;
	int enemy_h;
	int enemy_x_val;
	float enemy_y_val;
	int knockback;
	float knockback_val_x;

	// kiểm tra hành vi, vị trí =======
	bool enemy_on_ground;
	bool direc_goblin_right;
	bool direc_goblin_left;
	bool isattack_goblin;
	bool goblin_hit_yes;
	int goblin_heath;
	bool goblin_dead;
	bool goblin_hit;
	bool kt_died_goblin;
	bool is_attacking_bomb;
	bool prep_attack;
	bool enemy_hit_aim;
	bool enemy_attack_bomb;
	bool bomb_thrown;
	bool isknocked_back;

	// biến frame goblin ======
	int frame_died_goblin;
	int frame_attack_goblin;
	int frame_run_goblin;
	int frame_goblin_bomb;
	int frame_bomb1;
	int frame_bomb2;
	int frame_goblin_idle;

	// biến thời gian ======
	Uint32 hit_time;
	Uint32 time_goblin_idle;
	Uint32 time_attak_bomb_start;
	Uint32 frame_bomb_time;
	Uint32 frame_bomb_time_explore;
	Uint32  cooldown_bomb;
	Uint32  attack_goblin_time;
	Uint32 run_goblin_time;
	Uint32 goblin_hit_start;
	Uint32 goblin_frame_died;
  

	state_goblin goblin;
	Uint32 attack_goblin_start;
	SDL_Texture* load_enemy(const char* path, SDL_Renderer* render);
	
	vector<BULLET> stack_bomb;
	enemy();


	
	void checkvar2(const int tile_map[MAX_ROWS][MAX_COLS]);
	void update(const int tile_map[MAX_ROWS][MAX_COLS]);


	void followPlayer(player p1, const int tile_map[MAX_ROWS][MAX_COLS], SDL_Renderer* render, camera cam);
	
	bool amination_enemy_goblin(SDL_Renderer* render);
	
	void sprite_enemy_goblin_left(SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_right(SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_attack_right( SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_attack_left( SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_hurt_left(int frame, SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_hurt_right(int frame, SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_died_right(int frame, SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_died_left(int frame, SDL_Renderer* render, camera& cam);
	
	void sprite_enemy_goblin_attack_bomb_right(SDL_Renderer* render, camera& cam, player p1);
	
	void sprite_enemy_goblin_attack_bomb_left(SDL_Renderer* render, camera& cam, player p1);
	
	void sprite_enemy_goblin_idle_right(SDL_Renderer* render, camera cam);
	
	void sprite_enemy_goblin_idle_left(SDL_Renderer* render, camera cam);
	
	void sprite_bomb_right(SDL_Renderer* render, camera& cam,BULLET &bomb);
	
	void sprite_bomb_left(SDL_Renderer* render, camera& cam,BULLET &bomb);
	
	void enemy_goblin_health(SDL_Renderer* render, camera& cam);
	
	void loaded_bomb(player& p1);
	
	void update_bomb(const int tile_map[MAX_ROWS][MAX_COLS],player &p1,camera cam,sound_manager sound);
	
	bool check_map_bomb(const int tile_map[MAX_ROWS][MAX_COLS],BULLET bomb);
	
	bool check_aim_player(SDL_Rect rect_bullet, SDL_Rect player);
	
	void render_bomb(SDL_Renderer* render,camera cam, player p1);
};