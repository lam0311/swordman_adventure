#pragma once
#include"commonFc.h"
#include"map.h"
#include"player.h"
class attack : public player {
public:
	vector<pair<int, int>> picture_;
	vector<pair<int, int>> picture_2;
	int frame_attack;
	int frame_hit;
	int attackFrame_trigger;
	Uint32 time_frame_attack;
	Uint32 time_frame_hit;
	bool is_Attacking_Animation_Done;


	attack() {
		frame_attack = 0;
		frame_hit = 0;
		time_frame_attack = 0;
		time_frame_hit = 0;
		attackFrame_trigger = 6;
		is_Attacking_Animation_Done = false;
	}
	~attack() { ; }


	bool loadattack(SDL_Renderer* render);
	void aminationattackright( SDL_Renderer* render, camera cam,player x,bool &isattack);
	void aminationattackleft( SDL_Renderer* render, camera cam,player x,bool &isattack);
	void amination_hit_right(player &p1, SDL_Renderer* render, camera cam);
	void amination_hit_left( player &p1, SDL_Renderer* render, camera cam);
};