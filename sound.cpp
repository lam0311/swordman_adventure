#include"sound.h"
bool sound_manager::load_sound() {

	SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		cout << Mix_GetError();
		return false;
	}
	

	Mix_AllocateChannels(16);
	
	sound_player_attack = Mix_LoadWAV("music/sword_sound.wav");
	if (sound_player_attack == NULL) {
		cout << Mix_GetError();
		return false;
	}
	sound_player_hit = Mix_LoadWAV("music/player_hurt.wav");
	if (sound_player_hit == NULL) {
		cout << Mix_GetError();
		return false;
	}

	sound_game_menu = Mix_LoadMUS("music/nhac_nen_gamestart.wav");
	if (sound_game_menu == NULL) {
		cout << Mix_GetError();
		return false;
	}


	sound_game_start = Mix_LoadMUS("music/nhac_nen_choi.wav");
	if (sound_game_start == NULL) {
		cout << Mix_GetError();
		return false;
	}


	sound_goblin_hit = Mix_LoadWAV("music/goblin_hit.wav");
	if (sound_goblin_hit == NULL) {
		cout << Mix_GetError();
		return false;
	}

	sound_goblin_died = Mix_LoadWAV("music/goblin_death.wav");
	if (sound_goblin_died == NULL) {
		cout << Mix_GetError();
		return false;
	}

	sound_effect_apple = Mix_LoadWAV("music/sound_effect_apple.wav");
	if (sound_effect_apple == NULL) {
		cout << Mix_GetError();
		return false;
	}

	sound_attack_apple = Mix_LoadWAV("music/sound_attack_apple.wav");
	if (!sound_attack_apple) {
		cout << Mix_GetError();
		return false;
	}
	sound_attack_hit_apple = Mix_LoadWAV("music/snowball-throw-hit_7-278174.wav");
	if (!sound_attack_hit_apple) {
		cout << Mix_GetError();
		return false;
	}
	sound_run_player = Mix_LoadWAV("music/running-sounds-6003.wav");
	if (!sound_run_player) {
		cout << Mix_GetError();
		return false;
	}
	sound_game_over = Mix_LoadWAV("music/negative_beeps-6008.wav");
	if (!sound_game_over) {
		cout << Mix_GetError();
		return false;
	}


	return true;
}

void sound_manager::play_attack_sound() {
	Mix_PlayChannel(1, sound_player_attack, 0);
}

void sound_manager::play_attack_apple_hit_sound() {
	Mix_PlayChannel(6, sound_attack_hit_apple, 0);
}

void sound_manager::play_game_over_sound() {
	Mix_PlayChannel(8, sound_game_over, 0);
}

void sound_manager::play_hit_sound() {
	Mix_PlayChannel(2, sound_player_hit, 0);
}
void sound_manager::play_attack_apple_sound() {
	Mix_PlayChannel(5, sound_attack_apple, 0);
	Mix_VolumeChunk(sound_goblin_hit, 80);
}
void sound_manager::play_game_menu_sound() {

	if (!check_sound_game_menu) {
		Mix_HaltMusic(); 
		Mix_PlayMusic(sound_game_menu, -1);
		check_sound_game_menu = true;
		check_sound_game_start = false; 
	}
	
}
void sound_manager::play_run_player_sound() {
	if (!is_playing_run_sound) { 
		Mix_PlayChannel(7, sound_run_player, -1);  
		is_playing_run_sound = true;
		Mix_VolumeChunk(sound_run_player, 70);
	}
}

void sound_manager::stop_run_sound() {
	if (is_playing_run_sound) {
		Mix_HaltChannel(7);
		is_playing_run_sound = false;
	}
}

void sound_manager::play_game_start_sound() {
	if (!check_sound_game_start) {
		Mix_HaltMusic();  
		Mix_PlayMusic(sound_game_start, -1);
		check_sound_game_start = true;
		check_sound_game_menu = false; 
		Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	}
	
}

void sound_manager::play_goblin_hit_sound() {
	Mix_PlayChannel(3, sound_goblin_hit, 0);
	Mix_VolumeChunk(sound_goblin_hit, 50);
}

void sound_manager::play_goblin_died_sound() {
	Mix_PlayChannel(4, sound_goblin_died, 0);
}

void sound_manager::play_effect_apple_sound() {
	if (!check_sound_effect_apple) {
		Mix_HaltChannel(5);
		Mix_PlayChannel(5, sound_effect_apple, 0);
		check_sound_effect_apple = true;
	}
}

void sound_manager::stop_game_start_sound() {
	Mix_HaltMusic();
	check_sound_game_start = false;
}

void sound_manager::stop_game_menu_sound() {
	Mix_HaltMusic();
	check_sound_game_menu = false;
}





void sound_manager::close_sound() {
	Mix_FreeChunk(sound_player_attack);
	Mix_FreeChunk(sound_player_hit);
	Mix_FreeMusic(sound_game_start);
	Mix_FreeMusic(sound_game_menu);
	Mix_Quit();
}