#pragma once
#include"commonFc.h"
#include"sound.h"
struct camera;
class attack;
struct player {
// tính chất nhân vật===============
	int player_x;
	int player_y;
	int player_w;
	int player_h;
	int player_heath;
	int tileX;
	int tileY;
	float y_val;
	int x_val; 
	int dashDuration;
	int dashSpeed;

// biến kĩ năng đặc biệt============ 
	int energy;
	int max_energy;
	int picture_w;
	int picture_h;

// biến chạy frame=================
	int frame_effect_apple;
	int frame_player_idle;
	int frame_special_attack;
	int frame_special_attack1;
	int frame_special_attack2;
	int frame_special_attack3;
	int charge_frame;
	int special_attack_frame;
	int frame_run;
	
// biến kiểm tra tình chất nhân vật=====
	bool on_ground;
	bool attack_corec;
	bool player_hit;
	bool check_player_hit_bomb;
	bool player_died;
	bool can_use_special;
	bool using_special;
	bool charging;
	bool isDashing;

// biến thời gian điều chỉnh tốc độ======
	Uint32 player_hit_start;
	Uint32 time_apple;
	Uint32 player_died_time;
	Uint32 time_player_idle;  
	Uint32 last_special_attack;
	Uint32 last_special_attack1;      
	Uint32 charge_start ;   
    Uint32 charge_time ; 
	Uint32 charge_time_frame;
	Uint32 time_run;
	Uint32 dashStartTime;
	Uint32 reload_dash;


	player();

	void checkvar(const int tile_map[MAX_ROWS][MAX_COLS]);
	void updateTilePosition() {
		tileX = player_x / tile_block;
		tileY = player_y / tile_block;
	}
	void update_dash(bool direcRight, bool direcLeft, const int tile_map[MAX_ROWS][MAX_COLS]);

	void box(SDL_Renderer* render,camera cam);
	SDL_Texture* Loadsprite(const char* path,SDL_Renderer* render);
	
	void behavior_player( camera cam, SDL_Renderer* render, bool left, bool right,
		 bool direcleft, bool direcright, bool &isattack, attack &at,sound_manager &sound,player &p1);

	bool spriterun(SDL_Renderer* render);
	void aminationrunright( SDL_Renderer* render, camera cam);
	bool check_map_dash(const int tile_map[MAX_ROWS][MAX_COLS], bool direc_left, bool direc_right);
	void aminationrunleft( SDL_Renderer* render, camera cam);
	void Effect_apple_player(SDL_Renderer* render, camera cam);
	void Effect_apple2_player(SDL_Renderer* render, camera cam);
	void render_player_idle_right(SDL_Renderer* render, camera cam);
	void render_player_idle_left(SDL_Renderer* render, camera cam);
	void recharge(int index_energy); void jump();
	void sprite_special_attack_behind(SDL_Renderer* render, camera cam);
	void sprite_special_attack_front(SDL_Renderer* render, camera cam);
	void using_attack_special_left(SDL_Renderer* render, camera cam);
	void using_attack_special_right(SDL_Renderer* render, camera cam);

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
		shake = 0;
		
		shake_start_time = 0;
		shake_duration = 0;
		slow_motion_time = 0;
		slow_motion_time_start = 0;
		
		is_shaking = false;
		is_slow_motion = false;
	}
	

	void updateCamera(player x);

	void start_shake(int shake_, Uint32 duration);
	void update_shake();
	void start_slow_motion(Uint32 slow_motion_time);
	void update_slow_motion();
	void resetcam();
};



