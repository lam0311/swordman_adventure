#pragma once
#include"commonFc.h"
#include"player.h"
#include"sound.h"
#include"game status.h"
class enemy;
class BULLET :public player {
public:
	int bullet_x;
	int bullet_y;
	int bullet_w;
	int bullet_h;
	int speed_bullet;
	bool active_bullet;
	bool bullet_special;
	int direction_bullet;
	double direction_x;
	double direction_y;
	int frame_bullet;
	int bullet_x_start;
	int frame_bullet_special;
	Uint32 time_frame_bullet;
	Uint32 time_hit_bullet;
	Uint32 time_frame_bullet_special;
	int frame_hit_bullet;
	bool bomb_explore;


	BULLET() {
		bullet_x = 0;
		bullet_y = 0;
		bullet_w = 100;
		bullet_h = 100;
		speed_bullet = 10;
		active_bullet = false;
		direction_bullet = 0;
		frame_bullet = 0;
		time_frame_bullet = 0;
		time_hit_bullet = 0;
		frame_hit_bullet = 0;
		direction_x = 0;
		direction_y = 0;
		bullet_special = false;
		bullet_x_start = 0;
		bomb_explore = false;


	}
	~BULLET() { ; }
	bool animation_bullet(SDL_Renderer* render);
	void  update_bullet(camera cam);
	void bullet_gun(SDL_Renderer* render, player p1, camera cam);
	void bullet_gun_hit(SDL_Renderer* render, camera cam, vector<enemy>& enemy_g);
	
};


class bullet_manager:public BULLET {
public:

	vector<BULLET> bullets;
	void add_bullet(int x, int y, int direction);
	void add_bullet_special(int x, int y, int direction, sound_manager sound);
	void update_bullet(camera cam, vector<enemy> &enemy_g,player &p1,sound_manager sound,status_game &status);
	void bullets_attack(SDL_Renderer* render, player p1, camera cam);

};