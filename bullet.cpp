#include"bullet.h"
#include"commonFc.h"
bool BULLET::animation_bullet(SDL_Renderer* render) {
	char path[50];
	for (int i = 0; i < 4; i++) {
		sprintf_s(path, "picture/Blue Effect Bullet_gun%d.png", i);
		effect_apple3[i] = Loadsprite(path, render);
		if (effect_apple3[i] == NULL) {
			return false;
		}
	}

	for (int i = 0; i < 4; i++) {
		sprintf_s(path, "picture/Blue Effect Bullet_gun_right%d.png", i);
		effect_apple3_right[i] = Loadsprite(path, render);
		if (effect_apple3_right[i] == NULL) {
			return false;
		}
	}


	for (int i = 0; i < 4; i++) {
		sprintf_s(path, "picture/Blue Effect_aim%d .png", i);
		hit_animation[i] = Loadsprite(path, render);
		if (hit_animation[i] == NULL) {
			return false;
		}
	}
	
	sprite_bullet_special_right = Loadsprite("picture/Blue Effect_special_right.png", render);
	if (sprite_bullet_special_right == NULL) {
		return false;
	}

	sprite_bullet_special_left = Loadsprite("picture/Blue Effect_special_left.png", render);
	if (sprite_bullet_special_left == NULL) {
		return false;
	}


	return true;
}


void BULLET::update_bullet(camera cam) {
	if (active_bullet) {
		bullet_x += speed_bullet * direction_bullet;
		if (bullet_x < cam.camera_x || bullet_x > cam.camera_x + cam.camera_w) {
			active_bullet = false;
		}
	}


}

void BULLET::bullet_gun(SDL_Renderer* render, player p1, camera cam) {
	Uint32 currentime = SDL_GetTicks();
	if (currentime - time_frame_bullet > 80) {
		frame_bullet = (frame_bullet + 1) % 4;
		time_frame_bullet = SDL_GetTicks();
	}
	if (currentime - time_frame_bullet_special > 80) {
		frame_bullet_special = (frame_bullet_special + 1) % 4;
		time_frame_bullet_special = SDL_GetTicks();
	}
	if (active_bullet&&!bullet_special) {
		if (direction_bullet == 1) {
			SDL_Rect rect_bullet = { bullet_x - cam.camera_x,bullet_y - cam.camera_y-20,bullet_w,bullet_h };
			SDL_RenderCopy(render, effect_apple3_right[frame_bullet], NULL, &rect_bullet);
		}
		else {
			SDL_Rect rect_bullet = { bullet_x - cam.camera_x,bullet_y - cam.camera_y-20,bullet_w,bullet_h };
			SDL_RenderCopy(render, effect_apple3[frame_bullet], NULL, &rect_bullet);
		}
	}
	else if (active_bullet && bullet_special) {
		if (direction_bullet == 1) {
			SDL_Rect rect_picture = { 34 * frame_bullet_special,0,34,34 };
			SDL_Rect rect_bullet = { bullet_x - cam.camera_x,bullet_y - cam.camera_y - 20,bullet_w,bullet_h };
			SDL_RenderCopy(render, sprite_bullet_special_right, &rect_picture, &rect_bullet);
		}
		else {
			SDL_Rect rect_picture = { 34 * frame_bullet_special,0,34,34 };
			SDL_Rect rect_bullet = { bullet_x - cam.camera_x,bullet_y - cam.camera_y - 20,bullet_w,bullet_h };
			SDL_RenderCopy(render, sprite_bullet_special_left, &rect_picture, &rect_bullet);
		}
	}

}




void BULLET::bullet_gun_hit(SDL_Renderer* render, camera cam, vector<enemy> &enemy_g) {

	Uint32 currentime = SDL_GetTicks();
	if (currentime - time_hit_bullet > 80) {
		frame_hit_bullet = (frame_hit_bullet + 1) % 4;
		time_hit_bullet = SDL_GetTicks();
	}

	for (auto& enemy : enemy_g) {
		if (enemy.enemy_hit_aim) {
			SDL_Rect hit_effect_rect = {
				enemy.enemy_x - cam.camera_x + enemy.enemy_w / 4-20,
				enemy.enemy_y - cam.camera_y + enemy.enemy_h / 4-20,
				enemy.enemy_w ,
				enemy.enemy_h 
			};
			SDL_RenderCopy(render, hit_animation[frame_hit_bullet], NULL, &hit_effect_rect);
		}

		if (enemy.enemy_hit_aim) {
			if (SDL_GetTicks() - enemy.hit_time > 200) {
				enemy.enemy_hit_aim = false;
			}
		}
	}
}








bool check_aim_enemy(SDL_Rect rect_bullet, SDL_Rect enemy) {
	if (rect_bullet.x<enemy.x + enemy.w+30 && rect_bullet.x + rect_bullet.w-15>enemy.x && rect_bullet.y<enemy.y + enemy.h && rect_bullet.y + rect_bullet.h>enemy.y) {
		return true;
	}
	else {
		return false;
	}
}





void bullet_manager::add_bullet(int x, int y, int direction) {
	BULLET temp;
	temp.bullet_x = x;
	temp.bullet_y = y;
	temp.direction_bullet = direction;
	temp.active_bullet = true;
	bullets.push_back(temp);
}

void bullet_manager::add_bullet_special(int x, int y, int direction) {
	BULLET temp;
	temp.bullet_x = x;
	temp.bullet_y = y;
	temp.direction_bullet = direction;
	temp.active_bullet = true;
	temp.bullet_w = 220;
	temp.bullet_h = 220;
	temp.bullet_special = true;
	temp.speed_bullet = 6;
	temp.bullet_x_start = x;
	bullets.push_back(temp);
}

void bullet_manager::update_bullet(camera cam, vector<enemy> &enemy_g,player &p1) {

	for (int i = bullets.size() - 1; i >= 0; i--) {
		bullets[i].update_bullet(cam);


		for (auto& enemy : enemy_g) {
			SDL_Rect bullet_rect = { bullets[i].bullet_x, bullets[i].bullet_y, bullets[i].bullet_w, bullets[i].bullet_h };
			SDL_Rect enemy_rect = { enemy.enemy_x, enemy.enemy_y, enemy.enemy_w, enemy.enemy_h };

			if (check_aim_enemy(bullet_rect, enemy_rect)&&!enemy.goblin_dead&&!bullets[i].bullet_special) {
				p1.recharge(1);
				enemy.enemy_hit_aim = true;
				enemy.goblin_hit = true;
				enemy.goblin_heath -= 1;
				enemy.hit_time = SDL_GetTicks();
				bullets[i].active_bullet = false; 
				if (enemy.goblin_heath <= 0) {
					enemy.goblin_dead = true;
				}
			}
			else if (check_aim_enemy(bullet_rect, enemy_rect) && !enemy.goblin_dead &&bullets[i].bullet_special) {
				enemy.enemy_hit_aim = true;
				enemy.goblin_hit = true;
				enemy.goblin_heath -= 3;
				enemy.hit_time = SDL_GetTicks();
				if (enemy.goblin_heath <= 0) {
					enemy.goblin_dead = true;
				}
			}
			if (bullets[i].bullet_special && abs(bullets[i].bullet_x - bullets[i].bullet_x_start) > 1500) {
				bullets[i].active_bullet = false;
			}
		}



	}





	for (int i = bullets.size() - 1; i >= 0; i--) {
		if (!bullets[i].active_bullet) {
			bullets.erase(bullets.begin() + i);
		}
	}



}


void bullet_manager::bullets_attack(SDL_Renderer* render, player p1, camera cam) {
	for (auto& bullet : bullets) {
		bullet.bullet_gun(render, p1, cam);
	}
}

