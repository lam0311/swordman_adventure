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
	BOSS_index_health = load_enemy("picture/thanh mau.png", render);
	if (!BOSS_index_health) {
		cout << SDL_GetError();
		return false;
	}
	


	return true;
}

void BOSS::enemy_boss_health(SDL_Renderer* render, camera& cam) {
	SDL_Rect rect = { boss_x - cam.camera_x-60 , boss_y - cam.camera_y+40,20 *boss_health , 140 };
	SDL_RenderCopy(render, BOSS_index_health, NULL, &rect);
}

void BOSS::boss_shot(player p1,camera &cam,sound_manager sound) {
	Uint32 current_time = SDL_GetTicks();
	int range = abs(boss_x - p1.player_x);


	// Xác định phase của Boss dựa trên lượng máu
	if (boss_health > 12) {
		phase = 1;
	}
	else if (boss_health > 6) {
		phase = 2;
	}
	else {
		phase = 3;
	}

	if (range >= shot_range && current_time - last_shot_time < 1800) {
		atacking = false;
	}
	else {
		atacking = true;
	}

	if (range < shot_range && current_time - last_shot_time > 1800) {
		
		last_shot_time = current_time;
		last_idle_time = current_time;

		if (phase == 2) {
			// Phase 2: Bắn vòng tròn
			int bullet_count = 16;
			for (int i = 0; i < bullet_count; i++) {
				double angle = (2 * PI / bullet_count) * i;
				double dx = cos(angle);
				double dy = sin(angle);
				int rand_x = (rand() % 30) - 15;
				int rand_y = (rand() % 30) - 15;


				BULLET new_bullet;
				new_bullet.bullet_x = boss_x + 110 + rand_x;
				new_bullet.bullet_y = boss_y + 145 + rand_y;
				new_bullet.speed_bullet = 4;
				new_bullet.direction_x = dx;
				new_bullet.direction_y = dy;
				new_bullet.active_bullet = true;

				boss_bullets.push_back(new_bullet);
			}
		}

		else if (phase == 1) {
			// Phase 1: Bắn theo hàng ngang nhằm vào nhân vật 
			double dx = p1.player_x - boss_x;
			double dy = p1.player_y - boss_y;

			double length = sqrt(dx * dx + dy * dy);

			if (length != 0) {
				dx /= length; 
				dy /= length; 
			}
			int bullet_count = 6;
			double spacing = 40;

			for (int i = 0; i < bullet_count; i++) {
				// vector dx,-dy vuông góc ta tính như vậy để đạn dàn hàng ngang với khoảng cách bằng spacing
				double x = -dy * spacing * (i - bullet_count / 2);
				double y = dx * spacing * (i - bullet_count / 2);
			
				BULLET new_bullet;
				new_bullet.bullet_x = boss_x + 110 + x;
				new_bullet.bullet_y = boss_y + 145 + y;
				new_bullet.speed_bullet = 5;
				new_bullet.direction_x = dx ;
				new_bullet.direction_y = dy ;
				new_bullet.active_bullet = true;

				boss_bullets.push_back(new_bullet);
			}

		}

		else if (phase == 3) {
			// Phase 3: Bắn theo hàng dọc
			int bullet_count = 14; 
			for (int i = 0; i < bullet_count; i++) {
				BULLET new_bullet;
				int rand_x = (rand() % 40) - 20;
				new_bullet.bullet_x = boss_x + 140 * (i - bullet_count / 2) + rand_x;
				new_bullet.bullet_y = boss_y - 250;
				new_bullet.speed_bullet = 7;
				new_bullet.direction_x = 0; 
				new_bullet.direction_y = 1;
				new_bullet.active_bullet = true;

				boss_bullets.push_back(new_bullet);
			}
		}
		sound.play_boss_attack_sound();
	}
}

void BOSS::boss_update(player p1,camera &cam,sound_manager sound) {
	boss_shot(p1,cam,sound);

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
	if (rect_bullet.x<enemy.x + enemy.w  && rect_bullet.x + rect_bullet.w >enemy.x && rect_bullet.y<enemy.y + enemy.h && rect_bullet.y + rect_bullet.h>enemy.y) {
		return true;
	}
	else {
		return false;
	}
}

void BOSS::check_boss_hit_attack(bullet_manager& bullets_sword,player &p1,camera &cam,sound_manager &sound,status_game &status,attack &at) {
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
			sound.play_boss_hurt_sound();
			boss_hit = true;
			frame_boss_hit = 3;
			last_hit_time = SDL_GetTicks();
			bullet.active_bullet = false;
			if (boss_health <= 0) {
				check_boss_died = true;
				status.score += 500;
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
		SDL_Rect player_rect = { p1.player_x+15, p1.player_y, p1.player_w-30, p1.player_h };

		if (check_aim_boss2(bullet_rect, player_rect)&&!check_boss_died) {
			boss_bullet.active_bullet = false;  
			sound.check_sound_player_hit = true;
			if (sound.check_sound_player_hit && !p1.charging) {
				sound.play_hit_sound();
				sound.check_sound_player_hit = false;
			}
			if (!p1.charging) {
				at.frame_hit = 0;
				p1.player_hit = true;
				p1.player_hit_start = SDL_GetTicks();
				p1.player_heath -= 1;
			}
		}
	}

}




void BOSS::sprite_defending_boss(SDL_Renderer* render, camera cam, Uint32 current) {
	if (current - time_frame_shiled > 40) {
		frame_boss_shield = (frame_boss_shield + 1) % 13;
		time_frame_shiled = SDL_GetTicks();
	}
	SDL_Rect boss_picture = { frame_boss_shield * 63, 0, 63, 63 };
	SDL_Rect boss_rect = { boss_x - cam.camera_x + 7 , boss_y - cam.camera_y + 30 , 300, 300 };
	SDL_RenderCopy(render, shield_boss, &boss_picture, &boss_rect);
}

void BOSS::sprite_boss_idle_(SDL_Renderer* render, camera cam, Uint32 current_time) {
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

void BOSS::sprite_boss_hit(SDL_Renderer* render, camera cam, Uint32 current_time) {
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

void BOSS::sprite_boss_attack(SDL_Renderer* render, camera cam, Uint32 current_time) {
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

void BOSS::sprite_boss_died_(SDL_Renderer* render, camera cam, Uint32 current_time) {
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

	SDL_RenderCopy(render, sprite_boss_died, &boss_picture, &boss_rect);
}

void BOSS::spawn_boss(SDL_Renderer* render, camera cam, player p1) {
	Uint32 current_time = SDL_GetTicks();

	enemy_boss_health(render, cam);
	if (check_boss_died) {
		sprite_boss_died_(render, cam, current_time);
	}
	else {
		if (boss_hit) {
			sprite_boss_hit(render, cam, current_time);
		}
		else if (!atacking || current_time - last_idle_time > 1800) {
			sprite_boss_idle_(render, cam, current_time);
		}
		else {
			sprite_boss_attack(render, cam, current_time);
		}

		if (current_time - frame_bullet_time > 90) {
			frame_bullet_boss_shot = (frame_bullet_boss_shot + 1) % 3;
			frame_bullet_time = SDL_GetTicks();
		}


		for (auto& bullet : boss_bullets) {
			SDL_Rect bullet_rect = { bullet.bullet_x - cam.camera_x, bullet.bullet_y - cam.camera_y, 30, 30 };
			SDL_RenderCopy(render, sprite_bullet_boss[frame_bullet_boss_shot], NULL, &bullet_rect);
		}

		if (is_defending) {
			sprite_defending_boss(render, cam, current_time);
		}
	}
}









