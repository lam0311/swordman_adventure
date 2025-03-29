#include"player.h"
#include"commonFc.h"
#include"map.h"
#include"attack.h"
using namespace std;

player::player() {
    player_x = PLAYER_START_X;
    player_y = PLAYER_START_Y;
    player_w = PLAYER_WEIGHT;
    player_h = PLAYER_HEIGHT;
    player_heath = PLAYER_MAX_HEALTH;
    picture_w = 0; picture_h = 0;
    x_val = 0;  y_val = 0;
    player_hit_start = 0;
    frame_effect_apple = 0;
    time_apple = 0;
    time_apple2 = 0;
    player_died_time = 0;
    frame_player_idle = 0;
    time_player_idle = 0;
    dashStartTime = 0;
    dashDuration = 140;
    dashSpeed = 15;
    time_run = 0;
    reload_dash =600;
      last_special_attack = 0;
     frame_special_attack = 0;
    frame_special_attack1 = 0;
    frame_special_attack2 = 0;
    frame_special_attack3 = 0;
    charge_time = 3000;
    energy = 0; max_energy = 10;
    charge_start = 0;
    charge_frame = 0;
    frame_run = 0;
    charge_time_frame = 0;
    check_player_hit_bomb = false;
    can_use_special = false;
    using_special = false;
    attack_corec = false;
    player_died = false;
    player_hit = false;
    on_ground = false;
    isDashing = false;
    charging = false;
}

void player::box(SDL_Renderer* render,camera cam){
	SDL_Rect rect = { player_x-cam.camera_x,player_y-cam.camera_y,50,50 };
	SDL_RenderFillRect(render, &rect);
}

void player::aminationrunright( SDL_Renderer* render, camera cam) {


    if (SDL_GetTicks() - time_run > 40) {
        frame_run = (frame_run + 1) % 16;
        if (frame_run == 0) {
            frame_run = 1;
        }
        time_run = SDL_GetTicks();
    }

    // làm mờ hình ảnh 
    if (isDashing) {
        SDL_SetTextureAlphaMod(sprite_runright[frame_run], 150); 
        SDL_SetTextureAlphaMod(sprite_runleft[frame_run], 150);
    }
    else {
        SDL_SetTextureAlphaMod(sprite_runright[frame_run], 255); 
        SDL_SetTextureAlphaMod(sprite_runleft[frame_run], 255);
    }

    if (on_ground) {
        SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
        SDL_RenderCopy(render, sprite_runright[frame_run], NULL, &rect);
    }
    else {
        SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
        SDL_RenderCopy(render, sprite_runright[10], NULL, &rect);
    }
}

void player::aminationrunleft(SDL_Renderer* render, camera cam) {
    if (SDL_GetTicks() - time_run > 40) {
        frame_run = (frame_run + 1) % 16;
        if (frame_run == 0) {
            frame_run = 1;
        }
        time_run = SDL_GetTicks();
    }

    // làm mờ hình ảnh 
    if (isDashing) {
        SDL_SetTextureAlphaMod(sprite_runright[frame_run], 150);
        SDL_SetTextureAlphaMod(sprite_runleft[frame_run], 150);
    }
    else {
        SDL_SetTextureAlphaMod(sprite_runright[frame_run], 255);
        SDL_SetTextureAlphaMod(sprite_runleft[frame_run], 255);
    }

    if (on_ground) {
        SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
        SDL_RenderCopy(render, sprite_runleft[frame_run], NULL, &rect);
    }
    else {
        SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w,player_h };
        SDL_RenderCopy(render, sprite_runleft[10], NULL, &rect);
    }
}

void player::Effect_apple_player(SDL_Renderer* render, camera cam) {
    Uint32 curent = SDL_GetTicks();
    if (curent - time_apple >= 100) {
        frame_effect_apple = (frame_effect_apple + 1) % 3;
        time_apple = SDL_GetTicks();
    }


    SDL_Rect rect = { player_x - cam.camera_x-15,player_y - cam.camera_y-50,player_w+40,player_h+60 };
    SDL_RenderCopy(render, effect_apple[frame_effect_apple], NULL, &rect);

}

void player::Effect_apple2_player(SDL_Renderer* render, camera cam) {
    Uint32 curent = SDL_GetTicks();
    if (curent - time_apple2 >= 100) {
        frame_effect_apple = (frame_effect_apple + 1) % 4;
        time_apple2 = SDL_GetTicks();
    }


    SDL_Rect rect = { player_x - cam.camera_x + 7,player_y - cam.camera_y - 55,70,70 };
    SDL_RenderCopy(render, effect_apple2[frame_effect_apple], NULL, &rect);



}

void player::render_player_idle_left(SDL_Renderer* render, camera cam) {
	Uint32 curent = SDL_GetTicks();
	if (curent - time_player_idle >= 100) {
		frame_player_idle = (frame_player_idle + 1) % 10;
		time_player_idle = SDL_GetTicks();
	}
    SDL_Rect rec2 = { 36+(9 - frame_player_idle) * 96,46,27,36 };
	SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w+5,player_h+5 };
	SDL_RenderCopy(render, idle_left, &rec2, &rect);
}

void player::render_player_idle_right(SDL_Renderer* render, camera cam) {
    Uint32 curent = SDL_GetTicks();
    if (curent - time_player_idle >= 100) {
        frame_player_idle = (frame_player_idle + 1) % 10;
        time_player_idle = SDL_GetTicks();
    }

    SDL_Rect rec2 = { 35+frame_player_idle * 96, 46, 26, 37 };
    SDL_Rect rect = { player_x - cam.camera_x,player_y - cam.camera_y,player_w+5,player_h+5 };
    SDL_RenderCopy(render, idle_right, &rec2, &rect);
}


SDL_Texture* player:: Loadsprite(const char* path,SDL_Renderer* render) {
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
        picture_w = surface3->w;
        picture_h = surface3->h;
		SDL_FreeSurface(surface3);
		if (!sprite) {
			cout << "khong the tai anh";
			cout << SDL_GetError();
		}
	}
	return sprite;
}
bool player::spriterun(SDL_Renderer* render) {
	char path[50];
	for (int i = 0; i < 17; i++) {
		sprintf_s(path, "picture/walk%d.png", i);
		sprite_runright[i] = Loadsprite(path, render);
		if (sprite_runright[i] == NULL) {
			cout << SDL_GetError();
			return 0;
		}
	}

	char path_[50];
	for (int i = 0; i < 17; i++) {
		sprintf_s(path_, "picture/runleft%d.png", i);
		sprite_runleft[i] = Loadsprite(path_, render);
		if (sprite_runleft[i] == NULL) {
			cout << SDL_GetError();
			return 0;
		}
	}

    for (int i = 0; i < 3; i++) {
        sprintf_s(path_, "picture/Blue Effect Bullet%d.png", i);
        effect_apple[i] = Loadsprite(path_, render);
        if (!effect_apple[i]) {
            cout << SDL_GetError();
            return 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path_, "picture/Blue Effect_two%d.png", i);
        effect_apple2[i] = Loadsprite(path_, render);
        if (!effect_apple2[i]) {
            cout << SDL_GetError();
            return 0;
        }
    }

    idle_left = Loadsprite("picture/player_IDLE_menu1.png", render);
    idle_right = Loadsprite("picture/player_IDLE_menu.png", render);
    effect_attack_special[0] = Loadsprite("picture/effect_attack_special.png", render);
    effect_attack_special[1] = Loadsprite("picture/effect1_attack_special.png", render);
    effect_attack_special[2] = Loadsprite("picture/effect2_attack_special.png", render);
    effect_attack_special[3] = Loadsprite("picture/effect3_attack_special.png", render);
    sprite_attack_special_right = Loadsprite("picture/ATTACK_special_right.png", render);
    sprite_attack_special_left = Loadsprite("picture/ATTACK_special_left.png", render);
    smoke_texture_left = Loadsprite("picture/smoke-left.png", render);
    smoke_texture_right = Loadsprite("picture/smoke-right.png", render);

    if (!idle_left || !idle_right ||
        !effect_attack_special[0] || !effect_attack_special[1] ||
        !effect_attack_special[2] || !effect_attack_special[3] ||
        !sprite_attack_special_right || !sprite_attack_special_left ||
        !smoke_texture_left || !smoke_texture_right) {

        cout << SDL_GetError() << endl;
        return 0;
    }
	return 1;
}



void player::behavior_player( camera cam, SDL_Renderer* render, bool left, bool right,
    bool direcleft, bool direcright, bool &isattack, attack &at,sound_manager &sound,player &p1) {

    if ((right || left) && p1.on_ground) {
        sound.play_run_player_sound();
    }
    else {
        sound.stop_run_sound();
    }

    if (right||(direcright&&isDashing)) {
        p1.aminationrunright(render, cam);
    }

    else if (left||(direcleft && isDashing)) {
        p1.aminationrunleft(render, cam);
    }

    else if (isattack) {
        if (direcright) {
            at.aminationattackright( render, cam, p1,isattack);
        }
        else if (direcleft) {
            at.aminationattackleft( render, cam, p1,isattack);
        }
    }
    else if (p1.player_hit) {
        if (direcright) {
            at.amination_hit_right(p1, render, cam);
        }
        else if (direcleft) {
            at.amination_hit_left(p1, render, cam);
        }
    }
    else if (p1.charging) {
        if (direcright) {
            p1.using_attack_special_right(render, cam);
        }
        else if (direcleft) {
            p1.using_attack_special_left(render, cam);
        }
    }
    else if (p1.using_special) {
        if (direcright) {
            p1.using_attack_special_right(render, cam);
        }
        else if (direcleft) {
            p1.using_attack_special_left(render, cam);
        }
    }
    else {
        if (direcright) {
            p1.render_player_idle_right(render, cam);
        }
        else if (direcleft) {
            p1.render_player_idle_left(render, cam);
        }
        else {
            p1.render_player_idle_right(render, cam);
        }
    }
}


void player::checkvar(const int tile_map[MAX_ROWS][MAX_COLS]) {
    int min_h = min(player_h, tile_block);
    int min_w = min(player_w, tile_block);
    int new_x = player_x + x_val;
    int x1 = new_x / tile_block;
    int x2 = (new_x + player_w - 1) / tile_block;
    int y1 = player_y / tile_block;
    int y2 = (player_y + min_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
        if (x_val > 0) {
            if ((tile_map[y1][x2] != 0 || tile_map[y2][x2] != 0)&& (tile_map[y1][x2] != 3 || tile_map[y2][x2] != 3)) {
                player_x = x2 * tile_block - player_w;
                x_val = 0;
            }
            else {
                player_x += x_val;
            }
        }
        else if (x_val < 0) {
            if ((tile_map[y1][x1] != 0 || tile_map[y2][x1] != 0)&& (tile_map[y1][x1] != 3 || tile_map[y2][x1] != 3)) {
                player_x = (x1 + 1) * tile_block;
                x_val = 0;
            }
            else {
                player_x += x_val;
            }
        }
    }

    int new_y = player_y + y_val;
    x1 = player_x / tile_block;
    x2 = (player_x + min_w - 1) / tile_block;
    y1 = new_y / tile_block;
    y2 = (new_y + player_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
        if (y_val > 0) {
            if ((tile_map[y2][x1] != 0 || tile_map[y2][x2] != 0)&& (tile_map[y2][x1] != 3 || tile_map[y2][x2] != 3)) {
                player_y = y2 * tile_block - player_h;
                y_val = 0;
                on_ground = true;
            }
            else {
                on_ground = false;
            }
        }
        else if (y_val < 0) {
            if ((tile_map[y1][x1] != 0 || tile_map[y1][x2] != 0)&& (tile_map[y1][x1] != 3 || tile_map[y1][x2] != 3)) {
                player_y = (y1 + 1) * tile_block;
                y_val = 0;
            }
            else {
                player_y += y_val;
                on_ground = false;
            }
        }
    }

    if (player_x < 0) player_x = 0;
    else if (player_x + player_w > MAX_COLS * tile_block) player_x = MAX_COLS * tile_block - player_w;

    if (player_y < 0) player_y = 0;
    else if (player_y + player_h > MAX_ROWS * tile_block) {
        player_x -= 150;
        player_y = 0;
        player_heath--;
        SDL_Delay(250);
    }
}

void player::jump() {
    if (on_ground) {
        y_val = -9;
        on_ground = false;
    }
}

bool player::check_map_dash(const int tile_map[MAX_ROWS][MAX_COLS], bool direc_left,bool direc_right) {
    int min_h = min(player_h, tile_block);
    int min_w = min(player_w, tile_block);


    int new_x = player_x + dashSpeed;
    int x1 = new_x / tile_block;
    int x2 = (new_x + player_w - 1) / tile_block;
    int y1 = player_y / tile_block;
    int y2 = (player_y + min_h - 1) / tile_block;

    if (x1 >= 0 && x2 < MAX_COLS && y1 >= 0 && y2 < MAX_ROWS) {
        if (direc_right) {
            if ((tile_map[y1][x2] != 0 || tile_map[y2][x2] != 0) && (tile_map[y1][x2] != 3 || tile_map[y2][x2] != 3)) {
                player_x = x2 * tile_block - player_w;
                return false;
            }
        }
        else if (direc_left) {
            if ((tile_map[y1][x1] != 0 || tile_map[y2][x1] != 0) && (tile_map[y1][x1] != 3 || tile_map[y2][x1] != 3)) {
                player_x = (x1 + 1) * tile_block;
                return false;
            }
        }
    }
    return true;
}

void player::update_dash(bool direcRight,bool direcLeft, const int tile_map[MAX_ROWS][MAX_COLS]) {
    if (isDashing) {
        if (SDL_GetTicks() - dashStartTime < dashDuration) {

            if (check_map_dash(tile_map,direcLeft,direcRight)) {
                if (direcRight) {

                    smoke_effect smoke;
                    smoke.smoke_x = player_x;
                    smoke.smoke_y = player_y + player_h / 2;
                    smoke.startTime_smoke = SDL_GetTicks();
                    smoke.active_smoke = true;
                    smoke.direc_right_smokef = true;
                    smoke_effects.push_back(smoke);

                    player_x += dashSpeed;
                }
                if (direcLeft) {

                    smoke_effect smoke;
                    smoke.smoke_x = player_x;
                    smoke.smoke_y = player_y + player_h / 2;
                    smoke.startTime_smoke = SDL_GetTicks();
                    smoke.active_smoke = true;
                    smoke.direc_right_smokef = false;
                    smoke_effects.push_back(smoke);

                    player_x -= dashSpeed;
                }
            }
            else {
                isDashing = false;
            }

        }
        else {
            isDashing = false; 
        }
    }
}

void player::render_smoke(SDL_Renderer* render, camera cam) {
    Uint32 currentTime = SDL_GetTicks();

    for (auto& smoke : smoke_effects) {
        if (!smoke.active_smoke) continue;

      
        if (currentTime - smoke.startTime_smoke > 200) {
            smoke.active_smoke = false;
        }

        if (smoke.direc_right_smokef) {
            SDL_Rect smoke_rect = { smoke.smoke_x - cam.camera_x, smoke.smoke_y - cam.camera_y, 40, 40 };
            SDL_RenderCopy(render, smoke_texture_right, NULL, &smoke_rect);
        }
        else {
            SDL_Rect smoke_rect = { smoke.smoke_x - cam.camera_x, smoke.smoke_y - cam.camera_y, 40, 40 };
            SDL_RenderCopy(render, smoke_texture_left, NULL, &smoke_rect);
        }
    }

    for (int i = smoke_effects.size() - 1; i >= 0; i--) {
        if (!smoke_effects[i].active_smoke) {
            smoke_effects.erase(smoke_effects.begin() + i);
        }
    }
}


void player::recharge(int index_energy) {
	energy += index_energy;
	if (energy >= max_energy) {
		energy = max_energy;
		can_use_special = true;
	}
}

void player::sprite_special_attack_behind(SDL_Renderer* render, camera cam) {
	if (can_use_special) {
		Uint32 current_time = SDL_GetTicks();
        int lightning_x = 0;
        int lightning_y = 0;


		if (current_time - last_special_attack > 100) {
			frame_special_attack = (frame_special_attack + 1) % 8;
			frame_special_attack2 = (frame_special_attack2 + 1) % 10;
			frame_special_attack1 = (frame_special_attack1 + 1) % 8;
            frame_special_attack3 = (frame_special_attack3 + 1) % 16;
            if (frame_special_attack3 == 0) {
                lightning_x = (rand() % 120) - 60;
                lightning_y = (rand() % 60) - 30;
            }
            last_special_attack = SDL_GetTicks();
		}
		SDL_Rect rect_picture = { 64 * frame_special_attack,0,64,64 };
		SDL_Rect rect = { player_x - cam.camera_x - 50,player_y - cam.camera_y - 110,player_w + 100,player_h + 100 };
		SDL_RenderCopy(render, effect_attack_special[0], &rect_picture, &rect);


        SDL_Rect rect_picture2 = { 64 * frame_special_attack2,0,64,64 };
        SDL_Rect rect2 = { player_x - cam.camera_x - 21,player_y - cam.camera_y - 70,player_w + 40,player_h + 40 };
        SDL_RenderCopy(render, effect_attack_special[2], &rect_picture2, &rect2);

        SDL_Rect rect_picture3 = { 63 * frame_special_attack3,0,40,63 };
        SDL_Rect rect3 = { player_x - cam.camera_x - 50 + lightning_x,player_y - cam.camera_y - 100 + lightning_y,player_w + 100,player_h + 100 };
        SDL_RenderCopy(render, effect_attack_special[3], &rect_picture3, &rect3);

	}
}

void player::sprite_special_attack_front(SDL_Renderer* render, camera cam) {
    if (can_use_special) {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_special_attack1 > 40) {
            frame_special_attack1 = (frame_special_attack1 + 1) % 8;
            last_special_attack1 = SDL_GetTicks();
        }

        SDL_Rect rect_picture1 = { 64 * frame_special_attack1,0,64,64 };
        SDL_Rect rect1 = { player_x - cam.camera_x +2,player_y - cam.camera_y - 10,player_w + 25,player_h + 25 };
        SDL_RenderCopy(render, effect_attack_special[1], &rect_picture1, &rect1);
		SDL_Rect rect_picture2 = { 64 * (7-frame_special_attack1),0,64,64 };
        SDL_Rect rect2 = { player_x - cam.camera_x - 19,player_y - cam.camera_y - 10,player_w + 25,player_h + 25 };
        SDL_RenderCopy(render, effect_attack_special[1], &rect_picture2, &rect2);


    }
}

void player::using_attack_special_right(SDL_Renderer* render, camera cam) {
	if (charging) {
		Uint32 current_time = SDL_GetTicks();
        if (current_time - charge_time_frame > 1000&&charge_frame<3) {
			charge_frame = (charge_frame + 1);
			charge_time_frame = SDL_GetTicks();
        }
    
		SDL_Rect rect_picture = { 96 * charge_frame,0,96,96 };
        SDL_Rect rect = { player_x - cam.camera_x - 80,player_y - cam.camera_y - 105,player_w + 140,player_h + 140 };
		SDL_RenderCopy(render, sprite_attack_special_right, &rect_picture, &rect);
	}
    else if (using_special) {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - charge_time_frame > 130&&charge_frame<6) {
            charge_frame = (charge_frame + 1);
            charge_time_frame = SDL_GetTicks();
        }

        SDL_Rect rect_picture = { 100*charge_frame,0,96,96 };
        SDL_Rect rect = { player_x - cam.camera_x - 46,player_y - cam.camera_y - 105,player_w + 140,player_h + 140 };
        SDL_RenderCopy(render, sprite_attack_special_right, &rect_picture, &rect);
		if (charge_frame == 6) {
			using_special = false;
			charge_frame = 0;
		}
    }
}

void player::using_attack_special_left(SDL_Renderer* render, camera cam) {
	if (charging) {
		Uint32 current_time = SDL_GetTicks();
		if (current_time - charge_time_frame > 1000 && charge_frame < 3) {
			charge_frame = (charge_frame + 1);
			charge_time_frame = SDL_GetTicks();
		}
		SDL_Rect rect_picture = {  (6-charge_frame)*96,0,96,96 };
        SDL_Rect rect = { player_x - cam.camera_x - 63,player_y - cam.camera_y - 105,player_w + 140,player_h + 140 };
		SDL_RenderCopy(render, sprite_attack_special_left, &rect_picture, &rect);
	}
    else if (using_special) {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - charge_time_frame > 130 && charge_frame < 6) {
            charge_frame = (charge_frame + 1);
            charge_time_frame = SDL_GetTicks();
        }
        int m = 0;
		if (charge_frame == 5) {
			m = 20;
		}
		if (charge_frame == 6) {
			m = 50;
		}
        SDL_Rect rect_picture = { (6 - charge_frame) * 79,0,96,96 };
        SDL_Rect rect = { player_x - cam.camera_x - 100+m,player_y - cam.camera_y - 105,player_w + 140,player_h + 140 };
        SDL_RenderCopy(render, sprite_attack_special_left, &rect_picture, &rect);
        if (charge_frame == 6) {
            using_special = false;
            charge_frame = 0;
        }
    }
}

void camera::resetcam() {
    camera_x = 0;
    camera_y = 0;
}

void camera::start_shake(int shake_, Uint32 duration) {
	is_shaking = true;
	shake = shake_;
	shake_start_time = SDL_GetTicks();
	shake_duration = duration;
}

void camera::update_shake(){
    if (is_shaking) {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - shake_start_time > shake_duration) {
            is_shaking = false;
            shake = 0;
        }
        else {
            camera_x += rand() % (2 * shake) - shake;
			camera_y += rand() % (2 * shake) - shake;
        }

    }
}

void camera::updateCamera(player x) {

    camera_x = x.player_x - (camera_w / 2);

    camera_y = x.player_y - camera_h / 2;

    if (camera_x < 0) { camera_x = 0; }

    if (camera_y < 0) { camera_y = 0; }

    if (camera_x > MAX_COLS * tile_block - camera_w) {
        camera_x = MAX_COLS * tile_block - camera_w;
    }

    if (camera_y > MAX_ROWS * tile_block - camera_h) {
        camera_y = MAX_ROWS * tile_block - camera_h;
    }
}

void camera::start_slow_motion(Uint32 time_slow_motion) {
    is_slow_motion = true;
    slow_motion_time_start = SDL_GetTicks();
    slow_motion_time = time_slow_motion;
}

void camera::update_slow_motion() {
    if (is_slow_motion) {
        Uint32 current_time = SDL_GetTicks();
        if (current_time - slow_motion_time_start > slow_motion_time) {
            is_slow_motion = false;
        }
    }
}
