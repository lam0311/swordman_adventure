#pragma once
#include"commonFc.h"
#include"map.h"
#include"player.h"
class attack : public player {
public:
	vector<pair<int, int>> picture_;
	vector<pair<int, int>> picture_2;

	attack() {;}
	~attack() { ; }


	bool loadattack(SDL_Renderer* render);
	void aminationattackright(int fame, SDL_Renderer* render, camera cam,player x);
	void aminationattackleft(int fame, SDL_Renderer* render, camera cam,player x);
	void amination_hit_right(int fame, SDL_Renderer* render, camera cam, player x);
	void amination_hit_left(int fame, SDL_Renderer* render, camera cam, player x);
};