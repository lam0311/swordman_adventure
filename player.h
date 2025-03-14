#pragma once
#include"commonFc.h"
struct camera;
struct player {
	int player_x;
	int player_y;
	int player_w;
	int player_h;
	int x_val;
	int tileX; 
	int tileY; 
	int energy;
	int max_energy;
	int picture_w;
	int picture_h;
	int player_heath;
	int player_frame_hit;
	int frame_effect_apple;
	int frame_player_idle;
	int frame_special_attack;
	int frame_special_attack1;
	int frame_special_attack2;
	int frame_special_attack3;
	float y_val;
	bool on_ground;
	bool attack_corec;
	bool player_hit;
	bool player_died;
	bool can_use_special;
	bool using_special;
	bool charging;
	int charge_frame;
	int special_attack_frame;
	Uint32 player_hit_start;
	Uint32 time_apple;
	Uint32 player_died_time;
	Uint32 time_player_idle;  
	Uint32 last_special_attack;
	Uint32 last_special_attack1;      
	Uint32 charge_start ;   
    Uint32 charge_time ; 
	Uint32 charge_time_frame;

	player() {
		player_x = PLAYER_START_X;
		player_y = PLAYER_START_Y;
		player_heath = PLAYER_MAX_HEALTH;
		player_w = 70;
		player_h = 63;
		picture_w = 0;
		picture_h = 0;
		x_val = 0;
		y_val = 0;
		player_hit_start = 0;
		player_frame_hit = 0;
	    frame_effect_apple = 0;
		time_apple = 0;
		player_died_time = 0;
		frame_player_idle = 0;
		time_player_idle = 0;
		energy = 0;
		max_energy = 10;
		charge_start = 0;
		charge_time = 3000;
		last_special_attack = 0;
		frame_special_attack = 0;
		frame_special_attack1 = 0;
		frame_special_attack2 = 0;
		frame_special_attack3 = 0;
		charge_frame = 0;
		charge_time_frame = 0;
		on_ground = false;
		attack_corec = false;
		player_hit = false;
		player_died = false;
		can_use_special = false;
		using_special = false;
		charging = false;
	}
	



	void checkvar(const int tile_map[MAX_ROWS][MAX_COLS]);
	void updateTilePosition() {
		tileX = player_x / tile_block;
		tileY = player_y / tile_block;
	}




	void box(SDL_Renderer* render,camera cam);




	SDL_Texture* Loadsprite(const char* path,SDL_Renderer* render);
	
	bool spriterun(SDL_Renderer* render);
	void aminationrunright(int fame, SDL_Renderer* render, camera cam);
	void aminationrunleft(int fame, SDL_Renderer* render, camera cam);
	void Effect_apple_player(SDL_Renderer* render, camera cam);
	void Effect_apple2_player(SDL_Renderer* render, camera cam);
	void render_player_idle_right(SDL_Renderer* render, camera cam);
	void render_player_idle_left(SDL_Renderer* render, camera cam);
	void recharge(int index_energy);
	void sprite_special_attack_behind(SDL_Renderer* render, camera cam);
	void sprite_special_attack_front(SDL_Renderer* render, camera cam);
	void using_attack_special_left(SDL_Renderer* render, camera cam);
	void using_attack_special_right(SDL_Renderer* render, camera cam);
	void jump();

};

enum playerstate {
	STAND,
	JUMP,
	ATTACK,
	HIT
};


struct camera {
	int camera_x;
	int camera_y;
	int camera_w;
	int camera_h;
	int shake;
	bool is_shaking;
	bool is_slow_motion;
	Uint32 shake_start_time ;
	Uint32 shake_duration ; 
	Uint32 slow_motion_time_start;
	Uint32 slow_motion_time;

	camera() {
		camera_x = 0;
		camera_y = 0;
		camera_w = window_w;
		camera_h = window_h;
		is_shaking = false;
		is_slow_motion = false;
		shake = 0;
		shake_start_time = 0;
		shake_duration = 0;
		slow_motion_time = 0;
		slow_motion_time_start = 0;
	}
	

	void updateCamera(player x);

	void start_shake(int shake_, Uint32 duration);
	void update_shake();
	void start_slow_motion(Uint32 slow_motion_time);
	void update_slow_motion();
	void resetcam();
};



