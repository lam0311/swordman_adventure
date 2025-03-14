#include"commonFc.h"
#include"enemy.h"
#include"player.h"
enemy::enemy() {
	enemy_x = 0;
	enemy_y = 0;
	enemy_x_val = 0;
	enemy_y_val = 0.0;
	enemy_h = 70;
	enemy_w = 70;
    attack_goblin_start = 0;
    isattack_goblin = false;
    direc_goblin_left = true;
    direc_goblin_right = false;
	enemy_on_ground = false;
    goblin_heath = 3;
    goblin_dead = false;
    goblin_hit = false;
    goblin_hit_start = 0;
    goblin_frame_died = 0;
     kt_died_goblin = false;
     frame_died_goblin = 0;
     prep_attack = false;
     enemy_hit_aim = false;
      hit_time = 0;
	  frame_goblin_idle = 0;
	  time_goblin_idle = 0;
      enemy_attack_bomb = false;
      cooldown_bomb = 2000;
      time_attak_bomb_start = 0;

    picture_attack_left.push_back({ 60,79 });
    picture_attack_left.push_back({ 60,80 });
    picture_attack_left.push_back({ 60,71 });
    picture_attack_left.push_back({ 60,70 });
    picture_attack_left.push_back({ 160,80 });
    picture_attack_left.push_back({ 110,90 });


}


void enemy::checkvar2(const int tile_map[MAX_ROWS][MAX_COLS]) {
    int min_w = min(enemy_w, tile_block);
    int min_h = min(enemy_h, tile_block);

    int new_y = enemy_y + enemy_y_val;
    int x1 = enemy_x / tile_block;
    int x2 = (enemy_x + min_w -1) / tile_block;
    int y1 = new_y / tile_block;
    int y2 = (new_y + min_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
       
        if (enemy_y_val > 0) {
            if (tile_map[y2][x1] != 0 || tile_map[y2][x2] != 0) {
            
                enemy_y = (y2) * tile_block - min_h;
                enemy_y_val = 0;
                enemy_on_ground = true;
            }
            else {
                enemy_on_ground = false;
            }
        }
     
        else if (enemy_y_val < 0) {
            if (tile_map[y1][x1] != 0 || tile_map[y1][x2] != 0) {
              
                enemy_y = (y1 + 1) * tile_block;
                enemy_y_val = 0;
            }
        }
    }
}




void enemy::update(const int tile_map[MAX_ROWS][MAX_COLS]) {
    if (!enemy_on_ground) {
        enemy_y_val += 0.6;
        if (enemy_y_val > 6) {
            enemy_y_val = 6;
        }
    }


	enemy_x += enemy_x_val;
	enemy_y += enemy_y_val;

    checkvar2(tile_map);
}

bool enemy::amination_enemy_goblin(SDL_Renderer* render) {
    char path[50] = "picture/goblin_idle_right.png";
     
    sprite_goblin_idle = Loadsprite(path, render);
    if (!sprite_goblin_idle) {
        cout << SDL_GetError();
        return false;
    }

	sprite_goblin_idle1 = Loadsprite("picture/goblin_idle_left.png", render);
	if (!sprite_goblin_idle1) {
		cout << SDL_GetError();
		return false;
	}

    char path_[50];
    for (int i = 0; i < 8; i++) {
        sprintf_s(path_, "picture/goblin_Run_left%d.png", i);
        sprite_goblin_runleft[i] = Loadsprite(path_, render);
        if (!sprite_goblin_runleft[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 8; i++) {
        sprintf_s(path_, "picture/goblin_Run%d.png", i);
        sprite_goblin_runright[i] = Loadsprite(path_, render);
        if (!sprite_goblin_runright[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 6; i++) {
        sprintf_s(path_, "picture/goblin_Attack_r%d.png", i);
        sprite_goblin_attackright[i] = load_enemy(path_, render);
        if (!sprite_goblin_attackright[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 6; i++) {
        sprintf_s(path_, "picture/goblin_Attack_l%d.png", i);
        sprite_goblin_attackleft[i] = load_enemy(path_, render);
        if (!sprite_goblin_attackleft[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path_, "picture/Take Hit_goblin_%d.png", i);
        sprite_goblin_hit_right[i] = load_enemy(path_, render);
        if (!sprite_goblin_hit_right[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path_, "picture/Take Hit_goblin_left_%d.png", i);
        sprite_goblin_hit_left[i] = load_enemy(path_, render);
        if (!sprite_goblin_hit_left[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path_, "picture/Death_goblin_left%d.png", i);
        sprite_goblin_died_left[i] = load_enemy(path_, render);
        if (!sprite_goblin_died_left[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path_, "picture/Death_goblin_right%d.png", i);
        sprite_goblin_died_right[i] = load_enemy(path_, render);
        if (!sprite_goblin_died_right[i]) {
            cout << SDL_GetError();
            return false;
        }
    }
    goblin_index_health = load_enemy("picture/thanh mau.png", render);
    if (!goblin_index_health) {
        cout << SDL_GetError();
        return false;
    }

    sprite_bomb_explode_right = load_enemy("picture/goblin_attack_bomer_right.png", render);
    if (!sprite_bomb_explode_right) {
        cout << SDL_GetError();
        return false;
    }

    sprite_bomb_explode_left = load_enemy("picture/goblin_attack_bomer_left.png", render);
    if (!sprite_bomb_explode_left) {
        cout << SDL_GetError();
        return false;
    }

    sprite_bomb_explode_right = load_enemy("picture/Bomb_sprite_right.png", render);
    if (!sprite_bomb_explode_right) {
        cout << SDL_GetError();
        return false;
    }

    sprite_bomb_explode_left = load_enemy("picture/Bomb_sprite_left.png", render);
    if (!sprite_bomb_explode_left) {
        cout << SDL_GetError();
        return false;
    }




    return true;


}






void enemy::sprite_enemy_goblin_left(int frame,SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x, enemy_y - cam.camera_y, enemy_w, enemy_h };
    SDL_RenderCopy(render, sprite_goblin_runleft[frame], NULL, &rect);
}


void enemy::sprite_enemy_goblin_right(int frame,SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x, enemy_y - cam.camera_y, enemy_w, enemy_h };
    SDL_RenderCopy(render, sprite_goblin_runright[frame], NULL, &rect);
}


void enemy::sprite_enemy_goblin_attack_right(int frame, SDL_Renderer* render, camera& cam) {
    int m = 10;
    int n = 0;
    if (frame == 4||frame==5) {
        m = 20;
        n = 20;
    }
    SDL_Rect rect = { enemy_x - cam.camera_x-n, enemy_y - cam.camera_y-m,picture_attack_left[frame].first, picture_attack_left[frame].second };
    SDL_RenderCopy(render, sprite_goblin_attackright[frame], NULL, &rect);
}

void enemy::sprite_enemy_goblin_idle_right(SDL_Renderer* render, camera cam) {
	Uint32 curent = SDL_GetTicks();
	if (curent - time_goblin_idle >= 100) {
		frame_goblin_idle = (frame_goblin_idle + 1) % 4;
		time_goblin_idle = SDL_GetTicks();
	}
	SDL_Rect rec2 = { 56+frame_goblin_idle*150, 64, 36, 39 };
	SDL_Rect rect = { enemy_x - cam.camera_x,enemy_y - cam.camera_y,enemy_w,enemy_h };
	SDL_RenderCopy(render, sprite_goblin_idle, &rec2, &rect);
}

void enemy::sprite_enemy_goblin_idle_left(SDL_Renderer* render, camera cam) {
	Uint32 curent = SDL_GetTicks();
	if (curent - time_goblin_idle >= 100) {
		frame_goblin_idle = (frame_goblin_idle + 1) % 4;
		time_goblin_idle = SDL_GetTicks();
	}
    SDL_Rect rec2 = { 56 + (3 - frame_goblin_idle)*150, 64, 36, 39 };
	SDL_Rect rect = { enemy_x - cam.camera_x,enemy_y - cam.camera_y,enemy_w,enemy_h };
	SDL_RenderCopy(render, sprite_goblin_idle1, &rec2, &rect);
}



void enemy::sprite_enemy_goblin_attack_left(int frame, SDL_Renderer* render, camera& cam) {
    int m = 10;
    int n = 0;
    if ( frame == 5) {
        m = 20;
        n = 16;
    }
    if (frame == 4) {
        m = 10;
        n = 60;
    }
    SDL_Rect rect = { enemy_x - cam.camera_x-n, enemy_y - cam.camera_y-m, picture_attack_left[frame].first, picture_attack_left[frame].second};
    SDL_RenderCopy(render, sprite_goblin_attackleft[frame], NULL, &rect);
}




void enemy::sprite_enemy_goblin_hurt_right(int frame, SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y,70, 63 };
    SDL_RenderCopy(render, sprite_goblin_hit_right[frame], NULL, &rect);
}



void enemy::sprite_enemy_goblin_hurt_left(int frame, SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y,70, 63 };
    SDL_RenderCopy(render, sprite_goblin_hit_left[frame], NULL, &rect);
}




void enemy::sprite_enemy_goblin_died_left(int frame, SDL_Renderer* render, camera& cam) {
    int m = 0;
    if (frame == 3) {
        m = 15;
    }
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y+m,70, 63 };
    SDL_RenderCopy(render, sprite_goblin_died_left[frame], NULL, &rect);
}

void enemy::sprite_enemy_goblin_died_right(int frame, SDL_Renderer* render, camera& cam) {
    int m = 0;
    if (frame == 3) {
        m = 15;
    }
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y+m,70, 63 };
    SDL_RenderCopy(render, sprite_goblin_died_right[frame], NULL, &rect);
}



void enemy::enemy_goblin_health(SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y-27,25*goblin_heath, 40 };
    SDL_RenderCopy(render, goblin_index_health, NULL, &rect);
}



void enemy::followPlayer(player p1, const int tile_map[MAX_ROWS][MAX_COLS], state_goblin& goblin, int frame, SDL_Renderer* render, camera cam) {
  
    enemy_y_val += 0.6;
    if (enemy_y_val > 6) {
        enemy_y_val = 6;
    }

  
    int foot_new = enemy_x + enemy_x_val;
    int foot_x1 = foot_new / tile_block;
    int foot_x2 = (foot_new + enemy_w - 1) / tile_block;
    int foot_y = (enemy_y + enemy_h) / tile_block;

    if (foot_x1 >= 0 && foot_x2 < MAX_COLS && foot_y < MAX_ROWS) {
       
        if (tile_map[foot_y][foot_x1] != 0 || tile_map[foot_y][foot_x2] != 0) {
            if (abs(enemy_x - p1.player_x) < 400 /*&& enemy_on_ground*/ && abs(enemy_y - p1.player_y) <= tile_block*2) {
                if (abs(enemy_x - p1.player_x) < 75) {
                    enemy_x_val = 0;
                    goblin = ATTACK_GOBLIN;
                   
                    isattack_goblin = true;
                     
                }
                else if (enemy_x < p1.player_x) {
                    enemy_x_val = 2;
                    goblin = RUNRIGHT;
                    direc_goblin_right = true;
                    direc_goblin_left = false;
                }
                else {
                    goblin = RUNLEFT;
                    enemy_x_val = -2;
                    direc_goblin_left = true;
                    direc_goblin_right = false;
                }
            }


            else {
                enemy_x_val = 0;
                goblin = STANDUP;
            }
        }
        else {
            goblin = STANDUP;
            enemy_x_val = 0;
        }
    }
    else {
        goblin = STANDUP;
        enemy_x_val = 0;
    }

    
    enemy_x += enemy_x_val;
    enemy_y += enemy_y_val;

    checkvar2(tile_map);
}




SDL_Texture* enemy::load_enemy(const char* path, SDL_Renderer* render) {
    int n = IMG_INIT_PNG;
    if (!(IMG_Init(n) & n)) {
        return NULL;
    }
    SDL_Texture* sprite = NULL;
    SDL_Surface* surface3 = IMG_Load(path);
    if (surface3 == NULL) {
        cout << IMG_GetError();
        return NULL;
    }

    else {
        sprite = SDL_CreateTextureFromSurface(render, surface3);
        enemy_w = surface3->w;
        enemy_h = surface3->h;
        SDL_FreeSurface(surface3);
        if (!sprite) {
            cout << "khong the tai anh";
            cout << SDL_GetError();
        }
    }
    return sprite;
}

