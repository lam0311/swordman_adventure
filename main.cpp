#define SDL_MAIN_HANDLED
#include"commonFc.h"
#include"base oj.h"
#include"map.h"
#include"player.h"
#include"attack.h"
#include"enemy.h"
#include"interface.h"
#include"game status.h"
#include"bullet.h"
#include"boss.h"
#include"sound.h"

player p1;
camera cam;
attack at;
vector<enemy> goblin_enemy(100);
interface inter;
status_game status;
bullet_manager bullets_sword;
BOSS bigmonster;
sound_manager sound;
map mp;
base background;
base game_over_;
base game_menu;

bool setup() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << SDL_GetError();
		return false;
	}
    if (TTF_Init() == -1) {
        cout << TTF_GetError() << std::endl;
        return false;
    }
	window = SDL_CreateWindow("samurai_adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h,SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << SDL_GetError();
		return false;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (render == NULL) {
		cout << SDL_GetError();
		return false;
	}
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	return true;
}

void close() {
	background.free();
	for (int i = 0; i < 10; i++) {
		SDL_DestroyTexture(style_map[i]);
	}
	for (int i = 0; i < 17; i++) {
		SDL_DestroyTexture(sprite_runright[i]);
	}
	for (int i = 0; i < 17; i++) {
		SDL_DestroyTexture(sprite_runleft[i]);
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool setbackground() {
	bool back = background.loadimg("picture/Pixel Art forest #2.jpg", render,1280,640);
    bool over = game_over_.loadimg("picture/retry.png", render, 1280, 640);
	bool menu = game_menu.loadimg("picture/Preview.png", render, 1280, 640);
	return back || over || menu;
}

bool stylemap() {
	mp.readfile();
	bool st = mp.loadTile(render, "picture/map1.png", 1);
	bool st1 =mp.loadTile(render, "picture/map2.png", 2);
    bool st2 = mp.loadTile(render, "picture/cua.png", 3);
    return st || st1 || st2;
}

void resetgame() {

    p1.player_x = PLAYER_START_X;
    p1.player_y = PLAYER_START_Y;
    p1.player_heath = PLAYER_MAX_HEALTH;
    p1.x_val = 0;
    p1.y_val = 0;
    p1.player_died = false;
    p1.player_hit = false;
    at.frame_hit = 0;
    bigmonster.boss_health = 20;
	bigmonster.check_boss_died = false;
	bigmonster.boss_hit = false;
	bigmonster.atacking = false;
	inter.check_eat_apple = 0;
	inter.apple_x = 18040;
	inter.apple_y = 290;
    status.kill_count = 0;
    
    status.score = 0;
	for (int i = 0; i < bigmonster.boss_bullets.size(); i++) {
		bigmonster.boss_bullets[i].active_bullet = false;
	}


    for (int i = 0; i < 37; i++) {
        goblin_enemy[i].enemy_x = 600 + 700 * i;
        goblin_enemy[i].enemy_y = 40;
        goblin_enemy[i].goblin_heath = 3;
        goblin_enemy[i].goblin_dead = false;
        goblin_enemy[i].kt_died_goblin = false;
        goblin_enemy[i].goblin_hit = false;
        goblin_enemy[i].frame_died_goblin = 0;
        for (auto& bomb : goblin_enemy[i].stack_bomb) {
            bomb.active_bullet = false;
        }
        goblin_enemy[i].stack_bomb.clear();
    }
    for (int i = 37; i < 60; i++) {
        goblin_enemy[i].enemy_x = 600 + 800 * (i - 37);
        goblin_enemy[i].enemy_y = 40;
        goblin_enemy[i].goblin_heath = 3;
        goblin_enemy[i].goblin_dead = false;
        goblin_enemy[i].kt_died_goblin = false;
        goblin_enemy[i].goblin_hit = false;
        goblin_enemy[i].frame_died_goblin = 0;
        for (auto& bomb : goblin_enemy[i].stack_bomb) {
            bomb.active_bullet = false;
        }
        goblin_enemy[i].stack_bomb.clear();
    }
    cam.resetcam();
}

void effect_player_charging() {
    sound.play_start_charge(p1.charging);
    inter.check_eat_apple_(p1);
    if (inter.check_eat_apple) {

        sound.play_effect_apple_sound();
        p1.Effect_apple2_player(render, cam);
        p1.Effect_apple_player(render, cam);
    }
    if (p1.charging) {
        p1.sprite_special_attack_behind(render, cam);
    }
    if (p1.charging) {
        p1.sprite_special_attack_front(render, cam);
    }
    inter.render_energy2(render, p1, cam);
}

void resuilt_game() {
    if (p1.player_heath <= 0) {
        p1.player_died_time = SDL_GetTicks();
        status.GO = GAME_OVER;
        sound.play_game_over_sound();
    }

    if (bigmonster.check_boss_died) {
        Uint32 time = SDL_GetTicks() - bigmonster.victory_start_time;
        sound.play_game_victory_sound();
        if (time > 3000) {
            status.GO = GAME_VICTORY;
        }
    }
}

void handleGoblinDeath(enemy& goblin_enemy, SDL_Renderer* render, camera& cam) {

    if (goblin_enemy.goblin_dead) {
        if (!goblin_enemy.kt_died_goblin) {
            if (goblin_enemy.direc_goblin_left) {
                goblin_enemy.sprite_enemy_goblin_died_right(goblin_enemy.frame_died_goblin, render, cam);
            }
            else {
                goblin_enemy.sprite_enemy_goblin_died_left(goblin_enemy.frame_died_goblin, render, cam);
            }

            Uint32 currentime = SDL_GetTicks();
            if (currentime - goblin_enemy.goblin_frame_died > 130) {
                if (goblin_enemy.frame_died_goblin < 3) {
                    goblin_enemy.frame_died_goblin++;
                    goblin_enemy.goblin_frame_died = SDL_GetTicks();
                }
                else {
                    goblin_enemy.kt_died_goblin = true;
                }
            }
        }
        else {

            if (goblin_enemy.direc_goblin_left) {
                goblin_enemy.sprite_enemy_goblin_died_right(3, render, cam);
            }
            else {
                goblin_enemy.sprite_enemy_goblin_died_left(3, render, cam);
            }
        }
    }
}

void handleGoblinHit(enemy& g, SDL_Renderer* render, camera& cam, status_game& status, sound_manager& sound,int &frame_hit,
Uint32 goblin_frame_hit, bool isAttack, bool direcright, bool direcleft) {
    if (isAttack && direcright && g.enemy_x - p1.player_x < 80 && g.enemy_x - p1.player_x > 0 && abs(g.enemy_y - p1.player_y) < 40) {
        if (direcright) {

            sound.play_goblin_hit_sound();
            g.goblin_hit = true;
            g.goblin_hit_start = SDL_GetTicks();
            if (g.goblin_hit_yes) {
                g.goblin_heath -= 1;
                p1.recharge(1);
            }

        }
        g.goblin_hit_yes = false;
    }

    else if (isAttack && direcleft && g.enemy_x - p1.player_x > -80 && g.enemy_x - p1.player_x < 0 && abs(g.enemy_y - p1.player_y) < 40) {
        if (direcleft) {
            sound.play_goblin_hit_sound();
            g.goblin_hit = true;
            g.goblin_hit_start = SDL_GetTicks();
            if (g.goblin_hit_yes) {
                g.goblin_heath -= 1;
                p1.recharge(1);
            }
        }
        g.goblin_hit_yes = false;
    }
    g.enemy_goblin_health(render, cam);


    if (g.goblin_hit) {
        if (g.direc_goblin_left) {
            g.sprite_enemy_goblin_hurt_left(frame_hit, render, cam);
        }
        else {
            g.sprite_enemy_goblin_hurt_right(frame_hit, render, cam);
        }

        Uint32 currentime = SDL_GetTicks();
        if (currentime - goblin_frame_hit > 80) {
            frame_hit = (frame_hit + 1) % 4;
            goblin_frame_hit = SDL_GetTicks();
        }
        if (currentime - g.goblin_hit_start >= 200) {

            if (g.goblin_heath <= 0) {
                sound.play_goblin_died_sound();
                g.goblin_dead = true;
                g.goblin_frame_died = SDL_GetTicks();
                g.frame_died_goblin = 0;
                status.kill_count++;
                status.score += 100;
            }
            else {
                g.goblin_hit = false;
                frame_hit = 0;
            }
        }

    }
}

void checkPlayerhit(enemy& enemy_g, player& p1, sound_manager& sound, status_game& status, bool isAttack, bool direcright, bool direcleft,Uint32 attack_goblin_time_,
Uint32 time_goblin_run) {
    if (enemy_g.isattack_goblin) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - enemy_g.attack_goblin_start >= attack_goblin_time_) {
            enemy_g.isattack_goblin = false;
            enemy_g.frame_attack_goblin = 0;
        }
        if (abs(enemy_g.enemy_x - p1.player_x) < 75 && abs(enemy_g.enemy_y - p1.player_y) < 40) {
            if (!enemy_g.prep_attack) {
                enemy_g.prep_attack = true;
                enemy_g.attack_goblin_start = SDL_GetTicks();
            }

            else {
                Uint32 currentTime1 = SDL_GetTicks();
                if (currentTime1 - enemy_g.attack_goblin_start >= 350) {
                    if (enemy_g.enemy_x - p1.player_x < 75 && enemy_g.enemy_x - p1.player_x >0 && enemy_g.direc_goblin_left && abs(enemy_g.enemy_y - p1.player_y) < 40) {

                        if (!p1.player_hit && !p1.charging&&at.is_Attacking_Animation_Done) {
                            p1.player_hit = true;
                            cam.start_shake(5, 200);
                            p1.player_hit_start = SDL_GetTicks();
                            sound.check_sound_player_hit = true;
                            if (sound.check_sound_player_hit) {
                                sound.play_hit_sound();
                            }
                            at.frame_hit = 0;
                            p1.player_heath--;
                        }
                    }
                    else if (enemy_g.enemy_x - p1.player_x > -75 && enemy_g.enemy_x - p1.player_x < 0 && enemy_g.direc_goblin_right && abs(enemy_g.enemy_y - p1.player_y) < 40) {
                        if (!p1.player_hit && !p1.charging&&at.is_Attacking_Animation_Done) {
                            p1.player_hit = true;
                            cam.start_shake(5, 200);
                            p1.player_hit_start = SDL_GetTicks();
                            sound.check_sound_player_hit = true;
                            if (sound.check_sound_player_hit) {
                                sound.play_hit_sound();
                            }
                            at.frame_hit = 0;
                            p1.player_heath--;
                        }
                    }
                    enemy_g.prep_attack = false;
                }
            }
        }
        else {
            enemy_g.prep_attack = false;

        }
    }
}

void handleGoblinAI(enemy& enemy_g, player& p1, const int tile_map[MAX_ROWS][MAX_COLS], SDL_Renderer* render,
camera& cam,int frame_attack_goblin) {

    enemy_g.followPlayer(p1, tile_map, render, cam);
    enemy_g.update(tile_map);
    enemy_g.update_bomb(tile_map, p1, cam, sound);
    enemy_g.render_bomb(render, cam, p1);

    if (!enemy_g.goblin_hit) {
        if (enemy_g.goblin == STANDUP && !enemy_g.enemy_attack_bomb) {

            if (enemy_g.direc_goblin_left) enemy_g.sprite_enemy_goblin_idle_left(render, cam);

            else if (enemy_g.direc_goblin_right) enemy_g.sprite_enemy_goblin_idle_right(render, cam);
        }
        else if (enemy_g.goblin == RUNLEFT) {
            enemy_g.sprite_enemy_goblin_left( render, cam);
        }
        else if (enemy_g.goblin == RUNRIGHT) {
            enemy_g.sprite_enemy_goblin_right( render, cam);
        }
        else if (enemy_g.goblin == ATTACK_GOBLIN) {
            if (enemy_g.direc_goblin_left) {
                enemy_g.sprite_enemy_goblin_attack_left( render, cam);
            }
            else if (enemy_g.direc_goblin_right) {
                enemy_g.sprite_enemy_goblin_attack_right( render, cam);
            }
        }
    }
}





int main(int argc, char* argv[]) {

    const int(&mapArray)[MAX_ROWS][MAX_COLS] = mp.getmap();

    playerstate p1state = STAND;


    // thời gian chạy frame tấn công 
    bool isAttack = false;
    int frame_hit = 0;
    Uint32 attackStart = 0;
      Uint32 time_hit = 0;

    enemy enemy;
    BULLET sword_;

    // spamw vị trí của goblin 
    for (int i = 0; i < 37; i++) {
        goblin_enemy[i].enemy_x = 600 + 700 * i;
        goblin_enemy[i].enemy_y = 40;
    }
    for (int i = 37; i < 60; i++) {
        goblin_enemy[i].enemy_x = 600 + 800 * (i - 37);
        goblin_enemy[i].enemy_y = 40;
    }
    // biến tấn công của goblin
    Uint32 attack_goblin_time_ = 500;

    const int vector_y = 1;

    bool right = false, left = false;
    bool checkjump = false;
    bool direcright = false, direcleft = false;
  


    // thời gian chạy frame di chuyển
    int frame_goblin_run = 0;
    Uint32 time_goblin_run = 0;

    if (!setup() || !setbackground() || !stylemap() || !p1.spriterun(render) || !at.loadattack(render) || !enemy.amination_enemy_goblin(render)
        || !inter.load_picture(render) || !sword_.animation_bullet(render) || !bigmonster.load_inmage_boss(render) || !status.load_button(render)
        || !sound.load_sound_all()) {
        cout << SDL_GetError();
        return 1;
    }

    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
                break;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {

                case SDLK_RIGHT:
                    right = true;
                    left = false;
                    direcright = true;
                    direcleft = false;
                    p1.charging = false;
                    p1.x_val = VANTOC_PLAYER_X;
                    break;

                case SDLK_LEFT:
                    left = true;
                    right = false;
                    direcright = false;
                    direcleft = true;
                    p1.charging = false;
                    p1.x_val = -VANTOC_PLAYER_X;
                    break;

                case SDLK_UP:
                    p1.jump();
                    p1.charging = false;

                    break;

                case SDLK_SPACE:
                    if (!p1.charging && p1.can_use_special) {
                        p1.charge_start = SDL_GetTicks();
                        p1.charging = true;
                        p1.charge_frame = 0;

                    }
                }

                if (status.GO == GAME_VICTORY) {

                    if (e.key.keysym.sym == SDLK_RETURN) {
                        resetgame();
                        status.GO = MENU;

                    }
                }
            }

            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                Uint32 delay_attack = SDL_GetTicks();
                if (e.button.button == SDL_BUTTON_LEFT && !right && !left && delay_attack - attackStart >= 400) {
                    if (status.GO == START) {
                        sound.check_sound_player_attack = true;
                    }
                    isAttack = true;
                    attackStart = SDL_GetTicks();
                    for (int i = 0; i < 60; i++) goblin_enemy[i].goblin_hit_yes = true;
                }
                else if (e.button.button == SDL_BUTTON_RIGHT && delay_attack - attackStart >= 600 && inter.check_eat_apple) {
                    isAttack = true;
                    attackStart = SDL_GetTicks();
                    for (int i = 0; i < 60; i++) goblin_enemy[i].goblin_hit_yes = true;
                    sound.play_attack_apple_sound();

                    int check_direc = 0;
                    if (direcleft) {
                        check_direc = -1;
                    }
                    else {
                        check_direc = 1;
                    }
                    bullets_sword.add_bullet(p1.player_x + 20, p1.player_y + 2, check_direc);
                }



                int m;
                int n;
                SDL_GetMouseState(&m, &n);

                status.mouse_x = m;
                status.mouse_y = n;


            }

            else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_RIGHT:
                    right = false;
                    if (!right) p1.x_val = 0;
                    break;
                case SDLK_LEFT:
                    left = false;
                    if (!left) p1.x_val = 0;
                    break;
                case SDLK_SPACE:
                    if (p1.charging) {
                        Uint32 current_time = SDL_GetTicks();
                        if (current_time - p1.charge_start >= p1.charge_time) {
                            p1.using_special = true;
                            int check_direc = 0;
                            int x = 0;
                            int y = 50;
                            if (direcleft) {
                                check_direc = -1;
                                x = -10;
                            }
                            else {
                                check_direc = 1;
                                x = -100;
                            }
                            bullets_sword.add_bullet_special(p1.player_x + x, p1.player_y - y, check_direc,sound);
                            p1.special_attack_frame = 4;
                            p1.energy = 0;
                            p1.can_use_special = false;
                            cam.start_shake(10, 400);
                            cam.start_slow_motion(600);
                        }
                        p1.charging = false;
                    }
                }


                if (!left && !right) {
                    p1state = STAND;
                }
            }

        }

        if (!p1.on_ground) {
            p1.y_val += 0.5;
            if (p1.y_val > 7) {
                p1.y_val = 7;
            }
        }
        else {
            p1.y_val = 1;
        }

        // thay đổi vị trí nhân vật
        p1.checkvar(mapArray);
        p1.player_x += p1.x_val;
        p1.player_y += p1.y_val;
        cam.updateCamera(p1);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);



        if (status.GO == MENU) {
            sound.play_game_menu_sound();
            status.GAME_MENU(render, game_menu,quit);
            if (status.GO == START) {
                sound.stop_game_menu_sound();
                resetgame();
                direcright = true;
                isAttack = false;
            }
        }

        else if (status.GO == HELP) {
            status.GAME_HELP(render);
        }

        else if (status.GO == GAME_OVER) {
            sound.stop_game_start_sound();
            sound.stop_run_sound();
            Uint32 currentime = SDL_GetTicks();
            if (currentime - p1.player_died_time > 1000) {
                status.GAME_OVER(render, game_over_, inter.font);
                if (status.GO == START_AGAIN) {
                    resetgame();
                    status.GO = START;
                    direcright = true;
                    isAttack = false;
                }
                if (status.GO == MENU) {
                    resetgame();
                }
            }
        }

        else if (status.GO == GAME_VICTORY) {
            sound.stop_game_start_sound();
            status.GAME_VICTORY_(render, inter.font);
        }

        else if (status.GO == START) {
            
            sound.play_game_start_sound();
            background.positionimg(render, NULL);
            mp.rendermap(render, cam);
            if (sound.check_sound_player_attack) {
                sound.check_sound_player_attack = false;
                sound.play_attack_sound();
            }

            cam.update_shake();

            effect_player_charging();

            p1.behavior_player( cam, render, left, right, direcleft, direcright, isAttack, at, sound, p1);



            Uint32 goblin_frame_hit = 0;
            for (int i = 0; i < 60; i++) {
                if (goblin_enemy[i].goblin_dead) {
                    handleGoblinDeath(goblin_enemy[i], render, cam);
                    continue;
                }

                checkPlayerhit(goblin_enemy[i], p1, sound, status, isAttack, direcright, direcleft,attack_goblin_time_,time_goblin_run);

                handleGoblinHit(goblin_enemy[i], render, cam, status, sound, frame_hit, goblin_frame_hit,isAttack,direcright,direcleft);
                handleGoblinAI(goblin_enemy[i], p1, mapArray, render, cam,frame_goblin_run);

            }

            resuilt_game();
            inter.render_kill_count(render, status.kill_count, status.score);


            //boss ==================
            bigmonster.check_boss_hit_attack(bullets_sword, p1, cam, sound, status,at);
            bigmonster.boss_update(p1, cam,sound);
            bigmonster.spawn_boss(render, cam,p1);

            // kĩ năng chuột phải ==============
            bullets_sword.bullets_attack(render, p1, cam);
            bullets_sword.update_bullet(cam, goblin_enemy, p1, sound, status);
            bullets_sword.bullet_gun_hit(render, cam, goblin_enemy);

            // render giao diện màn hình nhân vật ==========
            inter.spamw_apple(render, cam);
            inter.position_blood_index(render, p1);
            inter.render_energy(render, p1);
            inter.render_button_sound(render, cam, sound, status);

            // slow motion =================
            cam.update_slow_motion();




            SDL_RenderPresent(render);
     
            SDL_Delay(16);

            if (cam.is_slow_motion) {
                SDL_Delay(48);
            }
        }
    }

    close();
    return 0;
}
