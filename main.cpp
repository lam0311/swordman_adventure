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
vector<enemy> enemy_g(100);
interface inter;
status_game status;
bullet_manager bullets_sword;
BOSS bigmonster;
sound_manager sound;

map mp;
base background;
base game_over_;
base game_menu;
// shift+alt+.

bool setup() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << SDL_GetError();
		return false;
	}
	window = SDL_CreateWindow("natra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h,SDL_WINDOW_SHOWN);
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




void move_(int framerun,camera cam,SDL_Renderer* render,player &p1,bool left,bool right,bool direcleft,bool direcright,bool isattack,attack at,int framattack) {
	if (right) {
        if (p1.on_ground) {
            p1.aminationrunright(framerun, render, cam);
        }
        else {
            p1.aminationrunright(10, render, cam);
        }
	}

    else if (left) {
        if (p1.on_ground) {
            p1.aminationrunleft(framerun, render, cam);
        }
        else {
            p1.aminationrunleft(10, render, cam);
        }
    }

    else if(isattack)  {
        if (direcright) {
            at.aminationattackright(framattack, render, cam,p1);
        }
        else if (direcleft) {
            at.aminationattackleft(framattack, render, cam,p1);
        }
    }

    else if (p1.player_hit) {
        if (direcright) {
            at.amination_hit_right(p1.player_frame_hit, render, cam, p1);
        }
        else if (direcleft) {
            at.amination_hit_left(p1.player_frame_hit, render, cam, p1);
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




void resetgame() {

    p1.player_x = PLAYER_START_X;
    p1.player_y = PLAYER_START_Y;
    p1.player_heath = PLAYER_MAX_HEALTH;
    p1.x_val = 0;
    p1.y_val = 0;
    p1.player_died = false;
    p1.player_hit = false;
    p1.player_frame_hit = 0;
    bigmonster.boss_health = 20;
	bigmonster.check_boss_died = false;
	bigmonster.boss_hit = false;
	bigmonster.atacking = false;
	inter.check_eat_apple = 0;
	inter.apple_x = 18040;
	inter.apple_y = 290;

	for (int i = 0; i < bigmonster.boss_bullets.size(); i++) {
		bigmonster.boss_bullets[i].active_bullet = false;
	}


    for (int i = 0; i < 37; i++) {
        enemy_g[i].enemy_x = 600 + 700 * i;
        enemy_g[i].enemy_y = 40;
        enemy_g[i].goblin_heath = 3;
        enemy_g[i].goblin_dead = false;
        enemy_g[i].kt_died_goblin = false;
        enemy_g[i].goblin_hit = false;
        enemy_g[i].frame_died_goblin = 0;
        enemy_g[i].stack_bomb.clear();
    }
    for (int i = 37; i < 60; i++) {
        enemy_g[i].enemy_x = 600 + 800 * (i - 37);
        enemy_g[i].enemy_y = 40;
        enemy_g[i].goblin_heath = 3;
        enemy_g[i].goblin_dead = false;
        enemy_g[i].kt_died_goblin = false;
        enemy_g[i].goblin_hit = false;
        enemy_g[i].frame_died_goblin = 0;
        enemy_g[i].stack_bomb.clear();
    }
    cam.resetcam();
}




int main(int argc, char* argv[]) {
    const int(&mapArray)[MAX_ROWS][MAX_COLS] = mp.getmap();



    playerstate p1state = STAND;
    state_goblin goblin = STANDUP;


    // thời gian chạy frame tấn công 
    bool isAttack = false;
    Uint32 attackStart = 0;
    const Uint32 attacktime = 200;
    int frameattack = 1;
    int frame_hit = 0;
    Uint32 time_hit = 0;



    enemy enemy;
    BULLET sword_;

    // spamw vị trí của goblin 
    for (int i = 0; i < 37; i++) {
        enemy_g[i].enemy_x = 600 + 700 * i;
        enemy_g[i].enemy_y = 40;
    }
    for (int i = 37; i < 60; i++) {
		enemy_g[i].enemy_x = 600 + 800 * (i - 37);
		enemy_g[i].enemy_y = 40;
    }
    // biến tấn công của goblin
    Uint32 attack_goblin_time = 500;
    int frame_attack_goblin = 0;
    bool goblin_hit_yes = false;



    const int vantoc = 4;
    const int vector_y = 1;

    bool right = false, left = false;
    bool checkjump = false;
    bool direcright = false, direcleft = false;
    bool hit = false;


    // thời gian chạy frame di chuyển
    int frame_goblin_run = 0;
    Uint32 time_goblin_run = 0;
    int framerun = 0;
    Uint32 timerun = 0;

    if (!setup() || !setbackground() || !stylemap() || !p1.spriterun(render) || !at.loadattack(render) || !enemy.amination_enemy_goblin(render)
        || !inter.blood_index(render) || !sword_.animation_bullet(render) || !bigmonster.load_inmage_boss(render) || !status.load_button(render)
        || !sound.load_sound()) {
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
                    p1.x_val = vantoc;
                    direcright = true;
                    direcleft = false;
					p1.charging = false;
                    break;
                case SDLK_LEFT:
                    left = true;
                    right = false;
                    p1.x_val = -vantoc;
                    direcright = false;
                    direcleft = true;
					p1.charging = false;
                    break;
                case SDLK_UP:
                    p1.jump();
					p1.charging = false;

                    break;
				case SDLK_SPACE:
                    if (!p1.charging&&p1.can_use_special) {
						p1.charge_start = SDL_GetTicks();
						p1.charging = true;
						p1.charge_frame = 0;
                       
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
                    goblin_hit_yes = true;
                }
                else if (e.button.button == SDL_BUTTON_RIGHT && delay_attack - attackStart >= 600 && inter.check_eat_apple) {
                    isAttack = true;
                    attackStart = SDL_GetTicks();
                    goblin_hit_yes = true;
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
                            bullets_sword.add_bullet_special(p1.player_x + x, p1.player_y - y, check_direc);
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


        // nhan vat dieu khien
        p1.checkvar(mapArray);
        p1.player_x += p1.x_val;
        p1.player_y += p1.y_val;
        cam.updateCamera(p1);

        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);



        if (status.GO == MENU) {
            sound.play_game_menu_sound();
            status.GAME_MENU(render, game_menu);
            if (status.GO == START) {
                sound.stop_game_menu_sound();
                resetgame();
            }
        }

        else if (status.GO == GAME_OVER) {
			sound.stop_game_start_sound();
            Uint32 currentime = SDL_GetTicks();
            if (currentime - p1.player_died_time > 1000) {
                status.GAME_OVER(render, game_over_);
                if (status.GO == START_AGAIN) {
                    resetgame();
                    status.GO = START;
                }
				if (status.GO == MENU) {
					resetgame();
				}

            }

        }

        else if (status.GO == START) {
            sound.play_game_start_sound();
            background.positionimg(render, NULL);
            mp.rendermap(render, cam);


            cam.update_shake();

            if (sound.check_sound_player_attack) {
                sound.check_sound_player_attack = false;
                sound.play_attack_sound();

            }


            Uint32 goblin_frame_hit = 0;
            // nhan vat: hieu ung  
            inter.check_eat_apple_(p1);
            if (inter.check_eat_apple) {

				sound.play_effect_apple_sound();
                p1.Effect_apple2_player(render, cam);
                p1.Effect_apple_player(render, cam);
            }

			if (p1.charging) {
				p1.sprite_special_attack_behind(render, cam);
			}

            move_(framerun, cam, render, p1, left, right, direcleft, direcright, isAttack, at, frameattack);
            if (p1.charging) {
                p1.sprite_special_attack_front(render, cam);
            }

			inter.render_energy2(render, p1,cam);

            for (int i = 0; i < 60; i++) {

                if (enemy_g[i].goblin_dead) {
                    if (!enemy_g[i].kt_died_goblin) {
                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_died_right(enemy_g[i].frame_died_goblin, render, cam);
                        }
                        else {
                            enemy_g[i].sprite_enemy_goblin_died_left(enemy_g[i].frame_died_goblin, render, cam);
                        }

                        Uint32 currentime = SDL_GetTicks();
                        if (currentime - enemy_g[i].goblin_frame_died > 130) {
                            if (enemy_g[i].frame_died_goblin < 3) {
                                enemy_g[i].frame_died_goblin++;
                                enemy_g[i].goblin_frame_died = SDL_GetTicks();
                            }
                            else {
                                enemy_g[i].kt_died_goblin = true;
                            }
                        }
                    }
                    else {

                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_died_right(3, render, cam);
                        }
                        else {
                            enemy_g[i].sprite_enemy_goblin_died_left(3, render, cam);
                        }
                    }

                    continue;
                }




                if (isAttack && direcright && enemy_g[i].enemy_x - p1.player_x < 80 && enemy_g[i].enemy_x - p1.player_x > 0 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                    if (direcright) {
                   
                        sound.play_goblin_hit_sound();
                        enemy_g[i].goblin_hit = true;
                        enemy_g[i].goblin_hit_start = SDL_GetTicks();
                        if (goblin_hit_yes) {
                            enemy_g[i].goblin_heath -= 1;
                            p1.recharge(1);
                            goblin_hit_yes = false;
                        }

                    }
                }

                else if (isAttack && direcleft && enemy_g[i].enemy_x - p1.player_x > -80 && enemy_g[i].enemy_x - p1.player_x < 0 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                    if (direcleft) {
                        sound.play_goblin_hit_sound();
                        enemy_g[i].goblin_hit = true;
                        enemy_g[i].goblin_hit_start = SDL_GetTicks();
                        if (goblin_hit_yes) {
                            enemy_g[i].goblin_heath -= 1;
                            p1.recharge(1);
                            goblin_hit_yes = false;
                        }

                    }
                }
                enemy_g[i].enemy_goblin_health(render, cam);


                if (enemy_g[i].goblin_hit) {
                    enemy_g[i].enemy_attack_bomb = false;
                    if (enemy_g[i].frame_goblin_bomb < 12) {
                        enemy_g[i].stack_bomb.clear();
                    }
                    if (enemy_g[i].direc_goblin_left) {
                        enemy_g[i].sprite_enemy_goblin_hurt_left(frame_hit, render, cam);
                    }
                    else {
                        enemy_g[i].sprite_enemy_goblin_hurt_right(frame_hit, render, cam);
                    }

                    Uint32 currentime = SDL_GetTicks();
                    if (currentime - goblin_frame_hit > 80) {
                        frame_hit = (frame_hit + 1) % 4;
                        goblin_frame_hit = SDL_GetTicks();
                    }
                    if (currentime - enemy_g[i].goblin_hit_start >= 200) {

                        if (enemy_g[i].goblin_heath <= 0) {
                            sound.play_goblin_died_sound();
                            enemy_g[i].goblin_dead = true;
                            enemy_g[i].goblin_frame_died = SDL_GetTicks();
                            enemy_g[i].frame_died_goblin = 0;
                        }
                        else {
                            enemy_g[i].goblin_hit = false;
                            frame_hit = 0;
                        }
                    }

                }



                enemy_g[i].followPlayer(p1, mapArray, goblin, frame_goblin_run, render, cam);
                enemy_g[i].update(mapArray);  
                
                if (!enemy_g[i].goblin_hit) {
                    enemy_g[i].update_bomb(mapArray, p1,cam);
                    enemy_g[i].render_bomb(render, cam,p1);
                    if (goblin == STANDUP&&!enemy_g[i].enemy_attack_bomb) {

						if (enemy_g[i].direc_goblin_left) enemy_g[i].sprite_enemy_goblin_idle_left(render, cam);
					
                        else if (enemy_g[i].direc_goblin_right) enemy_g[i].sprite_enemy_goblin_idle_right(render, cam);
                    }
                    else if (goblin == RUNLEFT) {
                        enemy_g[i].sprite_enemy_goblin_left(frame_goblin_run, render, cam);
                    }
                    else if (goblin == RUNRIGHT) {
                        enemy_g[i].sprite_enemy_goblin_right(frame_goblin_run, render, cam);
                    }
                    else if (goblin == ATTACK_GOBLIN) {
                        if (enemy_g[i].direc_goblin_left) {
                            enemy_g[i].sprite_enemy_goblin_attack_left(frame_attack_goblin, render, cam);
                        }
                        else if (enemy_g[i].direc_goblin_right) {
                            enemy_g[i].sprite_enemy_goblin_attack_right(frame_attack_goblin, render, cam);
                        }
                    }


                    if (goblin == RUNLEFT || goblin == RUNRIGHT) {
                        Uint32 currentTime_ = SDL_GetTicks();
                        if (currentTime_ - time_goblin_run > 80) {
                            frame_goblin_run = (frame_goblin_run + 1) % 8;
                            time_goblin_run = SDL_GetTicks();
                        }
                    }


                    if (enemy_g[i].isattack_goblin) {
                        Uint32 currentTime = SDL_GetTicks();
                        if (currentTime - time_goblin_run > 120) {
                            frame_attack_goblin = (frame_attack_goblin + 1) % 6;
                            time_goblin_run = SDL_GetTicks();
                        }
                        if (currentTime - enemy_g[i].attack_goblin_start >= attack_goblin_time) {
                            enemy_g[i].isattack_goblin = false;
                            frame_attack_goblin = 0;
                        }
                        if (abs(enemy_g[i].enemy_x - p1.player_x) < 75 && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                            if (!enemy_g[i].prep_attack) {
                                enemy_g[i].prep_attack = true;
                                enemy_g[i].attack_goblin_start = SDL_GetTicks();
                            }

                            else {
                                Uint32 currentTime1 = SDL_GetTicks();
                                if (currentTime1 - enemy_g[i].attack_goblin_start >= 370) {
                                    if (enemy_g[i].enemy_x - p1.player_x < 75 && enemy_g[i].enemy_x - p1.player_x >0 && enemy_g[i].direc_goblin_left && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {

                                        if (!p1.player_hit&&!p1.charging) {
                                            p1.player_hit = true;
                                            cam.start_shake(5, 200);
                                            p1.player_hit_start = SDL_GetTicks();
                                            sound.check_sound_player_hit = true;
                                            if (sound.check_sound_player_hit) {
                                                sound.play_hit_sound();
                                            }
                                            p1.player_frame_hit = 0;
                                            p1.player_heath--;
                                        }
                                    }
                                    else if (enemy_g[i].enemy_x - p1.player_x > -75 && enemy_g[i].enemy_x - p1.player_x < 0 && enemy_g[i].direc_goblin_right && abs(enemy_g[i].enemy_y - p1.player_y) < 40) {
                                        if (!p1.player_hit&&!p1.charging) {
                                            p1.player_hit = true;
											cam.start_shake(5, 200);
                                            p1.player_hit_start = SDL_GetTicks();
                                            sound.check_sound_player_hit = true;
                                            if (sound.check_sound_player_hit) {
                                                sound.play_hit_sound();
                                            }
                                            p1.player_frame_hit = 0;
                                            p1.player_heath--;
                                        }
                                    }
                                    enemy_g[i].prep_attack = false;
                                }
                            }
                        }
                        else {
                            enemy_g[i].prep_attack = false;

                        }
                    }
                }
            }
            if (p1.player_heath <= 0) {
                p1.player_died_time = SDL_GetTicks();
                status.GO = GAME_OVER;
            }


            //boss
            bigmonster.check_boss_hit_attack(bullets_sword, p1, cam, sound);
            bigmonster.boss_update(p1, cam);
            bigmonster.spawn_boss(render, cam);

            // ten
            bullets_sword.bullets_attack(render, p1, cam);
            bullets_sword.update_bullet(cam, enemy_g,p1,sound);
            bullets_sword.bullet_gun_hit(render, cam, enemy_g);

			
            inter.spamw_apple(render, cam);
            inter.position_blood_index(render, p1);
            inter.render_energy(render, p1);

            // slow motion--------------
            cam.update_slow_motion();




            SDL_RenderPresent(render);




            if (right || left) {
                if (SDL_GetTicks() - timerun > 40) {
                    framerun = (framerun + 1) % 16;
                    if (framerun == 0) {
                        framerun = 1;
                    }
                    timerun = SDL_GetTicks();
                }
            }



            else if (isAttack) {
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - timerun > 100) {
                    frameattack = (frameattack + 1) % 4;
                    if (frameattack == 0) {
                        frameattack = 1;
                    }
                    timerun = SDL_GetTicks();

                }
                if (currentTime - attackStart >= attacktime) {
                    isAttack = false;
                }
            }
            else if (p1.player_hit) {
                Uint32 currentTime = SDL_GetTicks();
                if (currentTime - timerun > 200) {
                    p1.player_frame_hit++;
                    timerun = SDL_GetTicks();
                }

                if (p1.player_frame_hit >= 4) {
                    p1.player_hit = false;
                    p1.player_frame_hit = 0;
                }
            }
            else {
                framerun = 0;
            }


            SDL_Delay(16);

            if (cam.is_slow_motion) {
                SDL_Delay(48);
            }
        }
    }

    close();
    return 0;
}
