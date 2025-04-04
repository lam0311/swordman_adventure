#include"commonFc.h"
#include"enemy.h"
#include"player.h"
enemy::enemy() {
	enemy_x = 0;
	enemy_y = 0;
	enemy_x_val = 0;
	enemy_y_val = 0.0;
	enemy_h = GOBLIN_H;
	enemy_w = GOBLIN_W;
    goblin_heath = GOBLIN_HEALTH;
    hit_time = 0;
    frame_goblin_idle = 0;
    time_goblin_idle = 0;
    attack_goblin_start = 0;
    goblin_hit_start = 0;
    goblin_frame_died = 0;
    frame_died_goblin = 0;
    cooldown_bomb = COOLDOWN_BOMB;
    time_attak_bomb_start = 0;
    frame_bomb_time = 0;
    frame_goblin_bomb = 0;
    frame_bomb1 = 0;
    frame_bomb2 = 8;
    frame_attack_goblin = 0;
    attack_goblin_time = 0;
    frame_run_goblin = 0;
    knockback = KNOCKBACK;
    knockback_val_x = 0;
    run_goblin_time = 0;
    frame_bomb_time_explore = 0;
    isknocked_back = false;
    isattack_goblin = false;
    direc_goblin_left = true;
    direc_goblin_right = false;
	enemy_on_ground = false;
    goblin_dead = false;
    goblin_hit = false;
     kt_died_goblin = false;
     prep_attack = false;
     enemy_hit_aim = false;
      enemy_attack_bomb = false;
      is_attacking_bomb = false;
      bomb_thrown = false;
      goblin_hit_yes = false;
      goblin = STANDUP;


}


void enemy::checkvar2(const int tile_map[MAX_ROWS][MAX_COLS]) {
    int min_w = min(enemy_w, tile_block);
    int min_h = min(enemy_h, tile_block);

    int new_y = enemy_y + enemy_y_val;
    int x1 = enemy_x / tile_block;
    int x2 = (enemy_x + min_w - 1) / tile_block;
    int y1 = new_y / tile_block;
    int y2 = (new_y + min_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {

        if (enemy_y_val > 0) {
            if (tile_map[y2][x1] != 0 || tile_map[y2][x2] != 0) {

                enemy_y = (y2)*tile_block - min_h;
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

    if (isknocked_back) {
        int min_h = min(enemy_x, tile_block);
        int min_w = min(enemy_y, tile_block);


        int new_x = enemy_x + knockback_val_x;
        int x1 = new_x / tile_block;
        int x2 = (new_x + enemy_w - 1) / tile_block;
        int y1 = enemy_y / tile_block;
        int y2 = (enemy_y + min_h - 1) / tile_block;

        if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
            if (knockback_val_x > 0) {
                if ((tile_map[y1][x2] != 0 || tile_map[y2][x2] != 0)) {
                    enemy_x = x2 * tile_block - enemy_w;
                    knockback_val_x = 0;
                }
            }
            else if (knockback_val_x < 0) {
                if ((tile_map[y1][x1] != 0 || tile_map[y2][x1] != 0)) {
                    enemy_x = (x1 + 1) * tile_block;
                    knockback_val_x = 0;
                }
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
    if (isknocked_back) {
        enemy_x += knockback_val_x;
        knockback_val_x *= 0.8; 
        enemy_x_val = 0;
        enemy_y_val = 0;
        if (abs(knockback_val_x) < 1) isknocked_back = false; 
    }

	enemy_x += enemy_x_val;
	enemy_y += enemy_y_val;

    checkvar2(tile_map);
}


bool enemy::amination_enemy_goblin(SDL_Renderer* render) {
   
    sprite_goblin_idle = load_enemy("picture/goblin_idle_right.png", render);
    sprite_goblin_idle1 = load_enemy("picture/goblin_idle_left.png", render);
    sprite_goblin_runright = load_enemy("picture/goblin_Run_right.png", render);
    sprite_goblin_runleft = load_enemy("picture/goblin_Run_left.png", render);
    sprite_goblin_attackright = load_enemy("picture/goblin_Attack_vip_right.png", render);
    sprite_goblin_attackleft = load_enemy("picture/goblin_Attack_vip_left.png", render);
    goblin_index_health = load_enemy("picture/thanh mau.png", render);
    sprite_goblin_attack_bomb_right = load_enemy("picture/goblin_attack_bomer_right.png", render);
    sprite_goblin_attack_bomb_left = load_enemy("picture/goblin_attack_bomer_left.png", render);
    sprite_bomb_explode_right = load_enemy("picture/Bomb_sprite_right.png", render);
    sprite_bomb_explode_left = load_enemy("picture/Bomb_sprite_left.png", render);

    if (!sprite_goblin_idle || !sprite_goblin_idle1 || !sprite_goblin_runright || !sprite_goblin_runleft ||
        !sprite_goblin_attackright || !sprite_goblin_attackleft || !goblin_index_health ||
        !sprite_goblin_attack_bomb_right || !sprite_goblin_attack_bomb_left ||
        !sprite_bomb_explode_right || !sprite_bomb_explode_left) {
        cout << SDL_GetError();
        return false;
    }

    char path[50];
    for (int i = 0; i < 4; i++) {
        sprintf_s(path, "picture/Take Hit_goblin_%d.png", i);
        sprite_goblin_hit_right[i] = load_enemy(path, render);

        sprintf_s(path, "picture/Take Hit_goblin_left_%d.png", i);
        sprite_goblin_hit_left[i] = load_enemy(path, render);

        sprintf_s(path, "picture/Death_goblin_left%d.png", i);
        sprite_goblin_died_left[i] = load_enemy(path, render);

        sprintf_s(path, "picture/Death_goblin_right%d.png", i);
        sprite_goblin_died_right[i] = load_enemy(path, render);

        if (!sprite_goblin_hit_right[i] || !sprite_goblin_hit_left[i] ||
            !sprite_goblin_died_left[i] || !sprite_goblin_died_right[i]) {
            cout << SDL_GetError();
            return false;
        }
    }

    return true;
}



void enemy::sprite_enemy_goblin_left(SDL_Renderer* render, camera& cam) {
    Uint32 currentTime_ = SDL_GetTicks();
    if (currentTime_ - run_goblin_time > 80) {
        frame_run_goblin = (frame_run_goblin + 1) % 8;
        run_goblin_time = SDL_GetTicks();
    }
    SDL_Rect rect_picture = { 150 * (7-frame_run_goblin),0,150,150 };
    SDL_Rect rect = { enemy_x - cam.camera_x - 100, enemy_y - cam.camera_y - 100 ,enemy_w + 210,enemy_h + 170 };
    SDL_RenderCopy(render, sprite_goblin_runleft, &rect_picture, &rect);
}

void enemy::sprite_enemy_goblin_right(SDL_Renderer* render, camera& cam) {
    Uint32 currentTime_ = SDL_GetTicks();
    if (currentTime_ - run_goblin_time > 80) {
        frame_run_goblin = (frame_run_goblin + 1) % 8;
        run_goblin_time = SDL_GetTicks();
    }
    SDL_Rect rect_picture = { 150 * frame_run_goblin,0,150,150 };
    SDL_Rect rect = { enemy_x - cam.camera_x - 100, enemy_y - cam.camera_y - 100 ,enemy_w + 210,enemy_h + 170 };
    SDL_RenderCopy(render, sprite_goblin_runright, &rect_picture, &rect);
}

void enemy::sprite_enemy_goblin_attack_right( SDL_Renderer* render, camera& cam) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - attack_goblin_time > 85) {
        frame_attack_goblin = (frame_attack_goblin + 1) % 8;
        attack_goblin_time = SDL_GetTicks();
    }

    SDL_Rect rect_picture = { 150*frame_attack_goblin,0,150,150 };
    SDL_Rect rect = { enemy_x - cam.camera_x -100, enemy_y - cam.camera_y-100 ,enemy_w+210,enemy_h+170 };
    SDL_RenderCopy(render, sprite_goblin_attackright, &rect_picture, &rect);
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

void enemy::sprite_enemy_goblin_attack_left( SDL_Renderer* render, camera& cam) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - attack_goblin_time > 85) {
        frame_attack_goblin = (frame_attack_goblin + 1) % 8;
        attack_goblin_time = SDL_GetTicks();
    }

    SDL_Rect rect_picture = { 150*(7-frame_attack_goblin),0,150,150};
    SDL_Rect rect = { enemy_x - cam.camera_x -100, enemy_y - cam.camera_y-100 ,enemy_w+210,enemy_h+170 };
    SDL_RenderCopy(render, sprite_goblin_attackleft, &rect_picture, &rect);
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

void enemy::sprite_enemy_goblin_attack_bomb_right(SDL_Renderer* render, camera& cam,player p1) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - frame_bomb_time > 80) {
        frame_goblin_bomb = frame_goblin_bomb + 1;
        frame_bomb_time = SDL_GetTicks();
    }

    if (frame_goblin_bomb == 11 && !bomb_thrown) {
        is_attacking_bomb = true;
        frame_bomb1 = 0;
        frame_bomb2 = 8;
        bomb_thrown = true; 
        loaded_bomb(p1);  
    }


    if (frame_goblin_bomb >= 12) { 
        enemy_attack_bomb = false;
        bomb_thrown = false;  
        frame_goblin_bomb = 0;
    }
    SDL_Rect rect_picture = { 150*frame_goblin_bomb,0,150,150 };
    SDL_Rect rect = { enemy_x - cam.camera_x -102, enemy_y - cam.camera_y-94,280, 240 };
    SDL_RenderCopy(render, sprite_goblin_attack_bomb_right, &rect_picture, &rect);
}

void enemy::sprite_enemy_goblin_attack_bomb_left(SDL_Renderer* render, camera& cam,player p1) {
    Uint32 current_time = SDL_GetTicks();
    if (current_time - frame_bomb_time > 100) {
        frame_goblin_bomb = frame_goblin_bomb + 1;
        frame_bomb_time = SDL_GetTicks();
    }

    if (frame_goblin_bomb == 11 && !bomb_thrown) {
        is_attacking_bomb = true;
        frame_bomb1 = 0;
        frame_bomb2 = 8;
        bomb_thrown = true;  
        loaded_bomb(p1); 
    }



    if (frame_goblin_bomb >= 12) {  
        enemy_attack_bomb = false;
        bomb_thrown = false;  
        frame_goblin_bomb = 0;
    }
    SDL_Rect rect_picture = { 150*(11-frame_goblin_bomb),0,150,150};
    SDL_Rect rect = { enemy_x - cam.camera_x-102 , enemy_y - cam.camera_y-94,280, 240 };
    SDL_RenderCopy(render, sprite_goblin_attack_bomb_left, &rect_picture, &rect);
}

void enemy::sprite_bomb_right(SDL_Renderer* render, camera& cam,BULLET &bomb) {
    Uint32 current_time = SDL_GetTicks();
    if (!bomb.bomb_explore) {
        if (current_time - frame_bomb_time_explore > 100 && frame_bomb1 < 8) {
            frame_bomb1 = frame_bomb1 + 1;
            frame_bomb_time_explore += 200;
        }

        SDL_Rect rect_picture = {frame_bomb1*100,0,100,100 };
        SDL_Rect rect = { bomb.bullet_x - cam.camera_x - 40, bomb.bullet_y - cam.camera_y - 90,200,200 };
        SDL_RenderCopy(render, sprite_bomb_explode_right, &rect_picture, &rect);

    }
    else {
        if (current_time - frame_bomb_time_explore > 100) {
            frame_bomb2 = frame_bomb2 + 1;
            frame_bomb_time_explore += 200;
        }
        if (frame_bomb2 >= 18) {
            is_attacking_bomb = false;
            bomb.active_bullet = false;
            frame_bomb2 = 8;
        }

        SDL_Rect rect_picture = { frame_bomb2*100,0,100,100 };
        SDL_Rect rect = { bomb.bullet_x - cam.camera_x - 90 , bomb.bullet_y - cam.camera_y - 90,200,200 };
        SDL_RenderCopy(render, sprite_bomb_explode_right, &rect_picture, &rect);
    }
}

void enemy::sprite_bomb_left(SDL_Renderer* render, camera& cam, BULLET &bomb) {
    Uint32 current_time = SDL_GetTicks();
    if (!bomb.bomb_explore) {
        if (current_time - frame_bomb_time_explore > 100 && frame_bomb1 < 8) {
            frame_bomb1 = frame_bomb1 + 1;
            frame_bomb_time_explore += 200;
        }

        SDL_Rect rect_picture = { (18-frame_bomb1)*100,0,100,100};
        SDL_Rect rect = { bomb.bullet_x - cam.camera_x-90 , bomb.bullet_y - cam.camera_y-90,200,200 };
        SDL_RenderCopy(render, sprite_bomb_explode_left, &rect_picture, &rect);

    }
    else {
        if (current_time - frame_bomb_time_explore > 100) {
            frame_bomb2 = frame_bomb2 + 1;
            frame_bomb_time_explore += 200;
        }
        if (frame_bomb2 >= 18) {
            is_attacking_bomb = false;
            bomb.active_bullet = false;
            frame_bomb2 = 8;
        }
   
        SDL_Rect rect_picture = { (18 - frame_bomb2) * 100,0,100,100 };
        SDL_Rect rect = { bomb.bullet_x - cam.camera_x -90, bomb.bullet_y - cam.camera_y-90,200,200 };
        SDL_RenderCopy(render, sprite_bomb_explode_left, &rect_picture, &rect);
    }
}

void enemy::enemy_goblin_health(SDL_Renderer* render, camera& cam) {
    SDL_Rect rect = { enemy_x - cam.camera_x , enemy_y - cam.camera_y - 27,25 * goblin_heath, 40 };
    SDL_RenderCopy(render, goblin_index_health, NULL, &rect);
}

void enemy::check_bomb(player p1) {
    int dx = abs(p1.player_x - enemy_x);

    if (dx <= 500 && SDL_GetTicks() - time_attak_bomb_start > cooldown_bomb && dx >= 350 && !goblin_hit) {
        throw_bomb(p1);
    }

    if (goblin_hit && enemy_attack_bomb) {
        enemy_attack_bomb = false;
    }
}

void enemy::throw_bomb(player p1) {
    enemy_attack_bomb = true;
    time_attak_bomb_start = SDL_GetTicks();
    frame_goblin_bomb = 0;
    goblin = ATTACK_BOMB;

    if (enemy_x < p1.player_x) {
        direc_goblin_right = true;
        direc_goblin_left = false;
    }
    else {
        direc_goblin_left = true;
        direc_goblin_right = false;
    }

    enemy_x_val = 0;
    enemy_y_val = 0;
}

void enemy::followPlayer(player p1, const int tile_map[MAX_ROWS][MAX_COLS], SDL_Renderer* render, camera cam) {
    enemy_y_val += 0.6;
    if (enemy_y_val > 6) {
        enemy_y_val = 6;
    }
  
    int foot_new = enemy_x + enemy_x_val;
    int foot_x1 = foot_new / tile_block;
    int foot_x2 = (foot_new + enemy_w - 1) / tile_block;
    int foot_y = (enemy_y + enemy_h) / tile_block;

    if (foot_x1 >= 0 && foot_x2 < MAX_COLS && foot_y < MAX_ROWS) {
        check_bomb(p1);

        if (goblin_hit && enemy_attack_bomb) {
            enemy_attack_bomb = false; 
        }

        if (!enemy_attack_bomb) {

            if (tile_map[foot_y][foot_x1] != 0 || tile_map[foot_y][foot_x2] != 0) {
                if (abs(enemy_x - p1.player_x) < 350 && enemy_on_ground && abs(enemy_y - p1.player_y) <= 2*tile_block ) {

                    if (abs(enemy_x - p1.player_x)<75) {
                        enemy_x_val = 0;
                        goblin = ATTACK_GOBLIN;
                        isattack_goblin = true;
                    }
                    else if (enemy_x < p1.player_x) {
                        enemy_x_val = 2;
                        goblin = RUNRIGHT;
                        direc_goblin_left = false; direc_goblin_right = true;
                    }
                    else {
                        goblin = RUNLEFT;
                        enemy_x_val = -2;
                        direc_goblin_left = true; direc_goblin_right = false;
                    }
                }
                else {
                    enemy_x_val = 0; goblin = STANDUP;
                }
            }
            else {
                enemy_x_val = 0; goblin = STANDUP;
            }
        }
    }
    else {
        enemy_x_val = 0; goblin = STANDUP;
    }

    enemy_x += enemy_x_val; enemy_y += enemy_y_val;

    checkvar2(tile_map);
}



void enemy::loaded_bomb(player& p1) {
    BULLET bomb;
    bomb.bullet_x = enemy_x;
    bomb.bullet_y = enemy_y;
    bomb.x_val = (p1.player_x - enemy_x) / 50; 
    bomb.y_val = -5; 
    bomb.active_bullet = true;
    if (!goblin_hit) {
        stack_bomb.push_back(bomb);
    }
}

bool enemy::check_aim_player(SDL_Rect rect_bullet, SDL_Rect player) {
    return (rect_bullet.x < player.x + player.w &&     
        rect_bullet.x + rect_bullet.w > player.x &&
        rect_bullet.y < player.y + player.h &&     
        rect_bullet.y + rect_bullet.h > player.y);  
}
bool enemy::check_map_bomb(const int tile_map[MAX_ROWS][MAX_COLS],BULLET bomb) {
    int tile_x = bomb.bullet_x / tile_block;
    int tile_y = bomb.bullet_y / tile_block;

    if (tile_x >= 0 && tile_x < MAX_COLS && tile_y >= 0 && tile_y < MAX_ROWS) {
        if (tile_map[tile_y][tile_x] != 0) { 
            return true; 
        }
    }
    return false;
}
void enemy:: update_bomb(const int tile_map[MAX_ROWS][MAX_COLS],player &p1,camera cam,sound_manager sound) {
    for (auto& bomb : stack_bomb) {
        if (!bomb.bomb_explore) {
            bomb.bullet_x += bomb.x_val;
            bomb.bullet_y += bomb.y_val;
            bomb.y_val += 0.2;
        }
        SDL_Rect bullet_rect = { bomb.bullet_x-10, bomb.bullet_y , bomb.bullet_w-78 , bomb.bullet_h-78 };
        SDL_Rect player_rect2 = { p1.player_x+15 ,p1.player_y,p1.player_w-30 , p1.player_h };
        if (check_map_bomb(tile_map, bomb)) {
            bomb.bomb_explore = true;
            sound.play_goblin_bomb_explosion();
        }
        else if (check_aim_player(bullet_rect, player_rect2)) {
            bomb.bomb_explore = true;
            sound.play_goblin_bomb_explosion();
            if (!p1.charging&&!p1.check_player_hit_bomb) {
                p1.player_heath -= 1;
                p1.player_hit = true;
                p1.check_player_hit_bomb = true;
                p1.player_hit_start = SDL_GetTicks();
                sound.play_hit_sound();
            }
        }

    }
    if (SDL_GetTicks() - p1.player_hit_start > 250) {
        p1.check_player_hit_bomb = false;
    }
   

    for (int i = stack_bomb.size() - 1; i >= 0; i--) {
        if (stack_bomb[i].bomb_explore && !stack_bomb[i].active_bullet) {
            stack_bomb.erase(stack_bomb.begin() + i);
        }
    }
}

void enemy::render_bomb(SDL_Renderer* render,camera cam,player p1) {
    if (enemy_attack_bomb) {
        if (direc_goblin_right) {
            sprite_enemy_goblin_attack_bomb_right(render, cam,p1);
        }
        else {
            sprite_enemy_goblin_attack_bomb_left(render, cam,p1);
        }
    }
 
    for (auto& bomb : stack_bomb) {
        if (bomb.x_val < 0) {
            sprite_bomb_left(render, cam, bomb);
        }
        else {
            sprite_bomb_right(render, cam, bomb);
        }
    }
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

