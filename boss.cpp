#include "boss.h"
#include"commonFc.h"
bool BOSS ::load_inmage_boss(SDL_Renderer* render) {

	char path[50];

	sprite_boss_idle = load_enemy("picture/boss_Idle.png", render);
	if (!sprite_boss_idle) {
		cout << SDL_GetError();
		return false;
	}

	sprite_boss_attacking = load_enemy("picture/boss_Attack_loat.png", render);
	if (!sprite_boss_attacking) {
		cout << SDL_GetError();
		return false;
	}

	shield_boss = load_enemy("picture/shield_boss.png", render);
	if (!shield_boss) {
		cout << SDL_GetError();
		return false;
	}

	sprite_boss_died = load_enemy("picture/boss_Death.png", render);
	if (!sprite_boss_died) {
		cout << SDL_GetError();
		return false;
	}


	sprite_boss_take_hit = load_enemy("picture/boss_take_hit.png", render);
	if (!sprite_boss_take_hit) {
		cout << SDL_GetError();
		return false;
	}



	for (int i = 0; i < 3; i++) {
		sprintf_s(path, "picture/bullet_sprite_boss%d.png", i);
		sprite_bullet_boss[i] = load_enemy(path, render);
		if (!sprite_bullet_boss[i]) {
			cout << SDL_GetError();
			return false;
		}

	}

	


	return true;
}


void BOSS::boss_shot(player p1,camera &cam) {
	Uint32 current_time = SDL_GetTicks();

	int range = abs(boss_x - p1.player_x);


	if (range < shot_range && current_time - last_level_time > 4400) {
		level_bullet++;
		last_level_time = SDL_GetTicks();
	}

	else if(range >= shot_range){
		level_bullet = 0;
		atacking = false;
	}
	else {
		atacking = true;
	}

	if(level_bullet>=8) {
		level_bullet = 8;
	}

	if (range<shot_range&&current_time - last_shot_time > 850) { 
		if (!check_boss_died) {
			cam.start_shake(10, 300);
		}
		last_shot_time = current_time;

		last_idle_time = current_time;

		int bullet_count = 12 + level_bullet;

		for (int i = 0; i < bullet_count; i++) {

			double angle = (2 * PI / bullet_count) * i; 
			double dx = cos(angle);
			double dy = sin(angle);

			BULLET new_bullet;
			new_bullet.bullet_x = boss_x + 110;
			new_bullet.bullet_y = boss_y +145;
			new_bullet.speed_bullet = 4;
			new_bullet.direction_x = dx;
			new_bullet.direction_y = dy;
			new_bullet.active_bullet = true;

			boss_bullets.push_back(new_bullet);
		}
	}
}

void BOSS::boss_update(player p1,camera &cam) {
	boss_shot(p1,cam);

	if (is_defending && SDL_GetTicks() - defense_start_time > 5000) {
		is_defending = false;
	}

	// Cập nhật vị trí đạn
	for (auto& bullet : boss_bullets) {
		bullet.bullet_x += bullet.speed_bullet * bullet.direction_x;
		bullet.bullet_y += bullet.speed_bullet * bullet.direction_y;

		if (bullet.bullet_x < cam.camera_x-400 || bullet.bullet_x > cam.camera_x + cam.camera_w+400) {
			bullet.active_bullet = false;
		}
	}


	for (int i = boss_bullets.size() - 1; i >= 0; i--) {
		if (!boss_bullets[i].active_bullet) {
			boss_bullets.erase(boss_bullets.begin() + i);
		}
	}

}

bool check_aim_boss2(SDL_Rect rect_bullet, SDL_Rect enemy) {
	if (rect_bullet.x<enemy.x + enemy.w + 30 && rect_bullet.x + rect_bullet.w - 15>enemy.x && rect_bullet.y<enemy.y + enemy.h && rect_bullet.y + rect_bullet.h>enemy.y) {
		return true;
	}
	else {
		return false;
	}
}

void BOSS::check_boss_hit_attack(bullet_manager& bullets_sword,player &p1,camera &cam,sound_manager &sound) {
	for (auto& bullet : bullets_sword.bullets) {
		SDL_Rect bullet_rect = { bullet.bullet_x, bullet.bullet_y , bullet.bullet_w , bullet.bullet_h };
		SDL_Rect boss_rect2 = { boss_x + 74, boss_y + 140, boss_w - 570 , boss_h - 630 };
		if (check_aim_boss2(bullet_rect, boss_rect2)&&!check_boss_died&&!is_defending) {
			hit_count += 1;
			if(bullet.bullet_special) {
				boss_health -= 3;
			}
			else {
				p1.recharge(1);
				boss_health -= 1;
			}
			boss_hit = true;
			frame_boss_hit = 3;
			last_hit_time = SDL_GetTicks();
			bullet.active_bullet = false;
			if (boss_health <= 0) {
				check_boss_died = true;
				cam.start_slow_motion(1000);
				victory_start_time = SDL_GetTicks();
			}
		}

		if (check_aim_boss2(bullet_rect, boss_rect2) && is_defending) {
			bullet.active_bullet = false;
		}

	}

	if (hit_count >= 5 && SDL_GetTicks() - last_hit_time < 1000) {
		is_defending = true;
		defense_start_time = SDL_GetTicks();
		hit_count = 0; 
	}



	for (auto& boss_bullet : boss_bullets) {  
		SDL_Rect bullet_rect = { boss_bullet.bullet_x, boss_bullet.bullet_y , boss_bullet.bullet_w - 70 , boss_bullet.bullet_h - 70 };
		SDL_Rect player_rect = { p1.player_x, p1.player_y, p1.player_w, p1.player_h };


		if (check_aim_boss2(bullet_rect, player_rect)&&!check_boss_died&&!p1.charging) {
			boss_bullet.active_bullet = false;  
			sound.check_sound_player_hit = true;
			if (sound.check_sound_player_hit) {
				sound.play_hit_sound();
				sound.check_sound_player_hit = false;
			}
			p1.player_frame_hit = 0;
			p1.player_hit = true;
			p1.player_hit_start = SDL_GetTicks();
			p1.player_heath -= 1;
		}
	}

}





void BOSS::spawn_boss(SDL_Renderer* render, camera cam) {
	Uint32 current_time = SDL_GetTicks();




	if (check_boss_died) {
		if (frame_boss_die <= 0) {
			frame_boss_die = 0;
		}
		else {
			if (current_time - last_boss_die > 160) {
				frame_boss_die = (frame_boss_die - 1);
				last_boss_die = current_time;
			}
		}
		SDL_Rect boss_picture = { frame_boss_die * 150, 0, 150, 150 };
		SDL_Rect boss_rect = { boss_x - cam.camera_x - 200, boss_y - cam.camera_y - 230, boss_w, boss_h };

		SDL_RenderCopy(render, sprite_boss_died,&boss_picture, &boss_rect);

	}
	 else {

		 if (boss_hit) {
			 if (current_time - last_hit_boss > 130) {
				 frame_boss_hit = (frame_boss_hit - 1);
				 if (frame_boss_hit == 0) {
					 boss_hit = false;
					 frame_boss_hit = 3;
				 }
				 last_hit_boss = current_time;
			 }

			 SDL_Rect boss_picture = { frame_boss_hit * 150, 0, 150, 150 };
			 SDL_Rect boss_rect = { boss_x - cam.camera_x - 200, boss_y - cam.camera_y - 230, boss_w, boss_h };

			 SDL_RenderCopy(render, sprite_boss_take_hit, &boss_picture, &boss_rect);
		 }

		 else if (!atacking || current_time - last_idle_time > 1500) {
			 if (current_time - last_idle_time > 90) {
				 frame_sprite_idle = (frame_sprite_idle - 1);
				 if (frame_sprite_idle < 0) {
					 frame_sprite_idle = 3;
				 }
				 last_idle_time = current_time;
			 }
			 SDL_Rect boss_picture = { frame_sprite_idle * 150, 0, 150, 150 };
			 SDL_Rect boss_rect = { boss_x - cam.camera_x - 200, boss_y - cam.camera_y - 230, boss_w, boss_h };

			 SDL_RenderCopy(render, sprite_boss_idle, &boss_picture, &boss_rect);
		 }

		 else {
			 if (current_time - last_frame_boss > 90) {
				 frame_sprite_boss_shot = (frame_sprite_boss_shot - 1);
				 if (frame_sprite_boss_shot < 0) {
					 frame_sprite_boss_shot = 8;
				 }
				 last_frame_boss = current_time;
			 }
			 SDL_Rect boss_picture = { frame_sprite_boss_shot * 150, 0, 150, 150 };
			 SDL_Rect boss_rect = { boss_x - cam.camera_x - 200, boss_y - cam.camera_y - 230, boss_w, boss_h };

			 SDL_RenderCopy(render, sprite_boss_attacking, &boss_picture, &boss_rect);
		 }


		 if (current_time - frame_bullet_time > 90) {
			 frame_bullet_boss_shot = (frame_bullet_boss_shot + 1) % 3;
			 frame_bullet_time = SDL_GetTicks();
		 }

		 // Vẽ đạn của boss
		 for (auto& bullet : boss_bullets) {
			 SDL_Rect bullet_rect = { bullet.bullet_x - cam.camera_x, bullet.bullet_y - cam.camera_y, 30, 30 };
			 SDL_RenderCopy(render, sprite_bullet_boss[frame_bullet_boss_shot], NULL, &bullet_rect);
		 }

		 if (is_defending) {
			 Uint32 current = SDL_GetTicks();
			 if (current - time_frame_shiled > 40) {
				 frame_boss_shield = (frame_boss_shield + 1) % 13;
				 time_frame_shiled = SDL_GetTicks();
			 }
			 SDL_Rect boss_picture = { frame_boss_shield * 63, 0, 63, 63 };
			 SDL_Rect boss_rect = { boss_x - cam.camera_x + 7 , boss_y - cam.camera_y + 30 , 300, 300 };
			 SDL_RenderCopy(render, shield_boss, &boss_picture, &boss_rect);
		 }
	 }
}








