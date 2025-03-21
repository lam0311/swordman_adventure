#pragma once
#include"commonFc.h"

class sound_manager {
public:

	bool check_sound_player_attack;
	bool check_sound_player_hit;
	bool check_sound_game_menu;
	bool check_sound_game_start;
	bool check_sound_goblin_hit;
	bool check_sound_goblin_died;
	bool check_sound_effect_apple;
	bool is_playing_run_sound;

	sound_manager() {
		check_sound_player_attack = false;
		check_sound_player_hit = false;
		check_sound_game_menu = false;
		check_sound_game_start = false;
		check_sound_goblin_hit = false;
		check_sound_goblin_died = false;
		check_sound_effect_apple = false;
		is_playing_run_sound = false;
	}

	bool load_sound_all();
	bool loadSound(Mix_Chunk*& sound, const std::string& path);
	bool loadMusic(Mix_Music*& music, const std::string& path);

	void play_attack_sound();
	void play_hit_sound();
	void play_game_menu_sound();	
	void play_game_start_sound();
	void play_goblin_hit_sound();
	void play_attack_apple_sound();
	void play_goblin_died_sound();
	void play_effect_apple_sound();
	void play_attack_apple_hit_sound();
	void play_run_player_sound();
	void play_game_over_sound();
	void play_boss_attack_sound();
	void play_goblin_bomb_explosion();
	void play_game_victory_sound();
	void stop_game_start_sound();
	void stop_game_menu_sound();
	void stop_run_sound();



	void close_sound();
};