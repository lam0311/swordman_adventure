#pragma once
#include"commonFc.h"
#include"enemy.h"
#include"bullet.h"
#include"player.h"
#include"sound.h"
#include"attack.h"

#define PI 3.14159265



class BOSS : public enemy {
public:              
	// biến tình chất =====
	int boss_x, boss_y; 
	int boss_w, boss_h;  
	int boss_health;  
	int shot_range;
	int hit_count;
	int phase;

	// biến frame =====
	int frame_sprite_boss_shot;
	int frame_bullet_boss_shot;
	int frame_sprite_idle;
	int frame_boss_die;
	int frame_boss_hit;
	int frame_boss_shield;

	// biến kiểm tra =====
	bool atacking;
	bool check_boss_died;
	bool boss_hit;
	bool is_defending;
	bool used_ultimate;  

	// biến thời gian ======
	Uint32 last_frame_boss;
	Uint32 last_hit_boss;
	Uint32 last_shot_time;
	Uint32 last_level_time;
	Uint32 last_idle_time;
	Uint32 frame_bullet_time;
	Uint32 last_boss_die;
	Uint32 last_hit_time;
	Uint32 defense_start_time;
	Uint32 defense_duration;
	Uint32 time_frame_shiled;
	Uint32 victory_start_time;
	Uint32 stun_start_time;

	vector<BULLET> boss_bullets;

	BOSS() {
		boss_x = 28000;
		boss_y = 20;
		boss_w = 700;
		boss_h = 800;
		boss_health = 20;
		last_shot_time = 0;
		shot_range = 1300;
		frame_sprite_boss_shot = 8;
		frame_bullet_boss_shot = 0;
		frame_sprite_idle = 3;
		last_frame_boss = 0; 
		last_level_time = 0;
		last_idle_time = 0;
		frame_boss_hit = 3;
		last_hit_boss = 0;
		frame_bullet_time = 0;
		frame_boss_die = 3;
		last_boss_die = 0;
		last_hit_time = 0;
		phase = 0;
		hit_count = 0;
		hit_count = 0;
		defense_start_time = 0;
		defense_duration = 0;
		time_frame_shiled = 0;
		frame_boss_shield = 0;
		victory_start_time = 0;
		check_boss_died = false;
		boss_hit = false;
		atacking = false;
		is_defending = false;
		used_ultimate = false;
	}

	bool load_inmage_boss(SDL_Renderer* render);
	void sprite_defending_boss(SDL_Renderer* render, camera cam, Uint32 current);
	void sprite_boss_idle_(SDL_Renderer* render, camera cam, Uint32 current);
	void sprite_boss_hit(SDL_Renderer* render, camera cam, Uint32 currentt);
	void sprite_boss_attack(SDL_Renderer* render, camera cam, Uint32 current);
	void sprite_boss_died_(SDL_Renderer* render, camera cam, Uint32 current);
	void boss_shot(player p1,camera &cam,sound_manager sound);
	void boss_update(player p1,camera &cam,sound_manager sound);
	void spawn_boss(SDL_Renderer* render,camera cam,player p1);
	void enemy_boss_health(SDL_Renderer* render, camera& cam);
	void check_boss_hit_attack(bullet_manager& bullets_sword,player &p1,camera &cam,sound_manager &sound,status_game &status,attack &at);


};