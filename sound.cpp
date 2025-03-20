#include"sound.h"

bool sound_manager::loadSound(Mix_Chunk*& sound, const std::string& path) {
	sound = Mix_LoadWAV(path.c_str());
	if (!sound) {
		cout << Mix_GetError();
		return false;
	}
	return true;
}

bool sound_manager::loadMusic(Mix_Music*& music, const std::string& path) {
	music = Mix_LoadMUS(path.c_str());
	if (!music) {
		cout << Mix_GetError();
		return false;
	}
	return true;
}

bool sound_manager::load_sound_all() {

	SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
		cout << Mix_GetError();
		return false;
	}
	Mix_AllocateChannels(16);
	

	return loadSound(sound_player_attack, "music/sword_sound.wav") &&
		loadSound(sound_player_hit, "music/player_hurt.wav") &&
		loadMusic(sound_game_menu, "music/nhac_nen_gamestart.wav") &&
		loadMusic(sound_game_start, "music/nhac_nen_choi.wav") &&
		loadSound(sound_goblin_hit, "music/goblin_hit.wav") &&
		loadSound(sound_goblin_died, "music/goblin_death.wav") &&
		loadSound(sound_effect_apple, "music/sound_effect_apple.wav") &&
		loadSound(sound_attack_apple, "music/sound_attack_apple.wav") &&
		loadSound(sound_attack_hit_apple, "music/snowball-throw-hit_7-278174.wav") &&
		loadSound(sound_run_player, "music/running-sounds-6003.wav") &&
		loadSound(sound_game_over, "music/negative_beeps-6008.wav") &&
		loadSound(sound_explosion, "music/explosion-312361.wav") &&
		loadSound(sound_game_victory, "music/success-fanfare-trumpets-6185.wav");
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

void sound_manager::play_goblin_bomb_explosion() {
	Mix_PlayChannel(9, sound_explosion, 0);
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

void sound_manager::play_game_victory_sound() {
	Mix_PlayChannel(9, sound_game_victory, 0);
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

	Mix_Chunk* soundEffects[] = {
		sound_player_attack, sound_player_hit, sound_goblin_hit, sound_goblin_died,
		sound_effect_apple, sound_attack_apple, sound_attack_hit_apple, sound_run_player,
		sound_game_over, sound_explosion, sound_game_victory
	};

	for (auto& s : soundEffects) {
		if (s) {
			Mix_FreeChunk(s);
			s = nullptr;
		}
	}
	Mix_Music* musicTracks[] = { sound_game_start, sound_game_menu };

	for (auto& m : musicTracks) {
		if (m) {
			Mix_FreeMusic(m);
			m = nullptr;
		}
	}

	Mix_Quit();
}
