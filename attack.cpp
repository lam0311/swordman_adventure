#include"attack.h"

bool attack::loadattack(SDL_Renderer* render) {
    char path[50];
  
        sprite_attackright = Loadsprite("picture/player_ATTACK_right.png", render);
        if (sprite_attackright == NULL) {
            cout << SDL_GetError();
            return false;
        }

        sprite_attackleft = Loadsprite("picture/player_ATTACK_left.png", render);
        if (sprite_attackleft == NULL) {
            cout << SDL_GetError();
            return false;
        }


        sprite_hit_right = Loadsprite("picture/player_HURT_right.png", render);
        if (!sprite_hit_right) {
            cout << SDL_GetError();
            return false;
        }
        sprite_hit_left = Loadsprite("picture/player_HURT_left.png", render);
        if (!sprite_hit_left) {
            cout << SDL_GetError();
            return false;
        }

    return true;

}

void attack::aminationattackright( SDL_Renderer* render, camera cam, player x,bool &isattack) {
    SDL_Rect picture_rect = { 96 * frame_attack,0,96,96 };
    SDL_Rect rect = { x.player_x - cam.camera_x - 85,x.player_y - cam.camera_y - 100,player_w + 160 ,player_h + 130 };
    SDL_RenderCopy(render, sprite_attackright, &picture_rect, &rect);

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - time_frame_attack > 20) {
        frame_attack = (frame_attack + 1) ;
        time_frame_attack = SDL_GetTicks();
    }

    if (frame_attack >= attackFrame_trigger) {
        is_Attacking_Animation_Done = true;
    }

    if (frame_attack >= 7) {
        isattack = false;
        is_Attacking_Animation_Done = true;
        frame_attack = 0;
    }
}

void attack::aminationattackleft( SDL_Renderer* render, camera cam, player x,bool &isattack) {
    SDL_Rect picture_rect = { 96 * (6-frame_attack),0,96,96 };
    SDL_Rect rect = { x.player_x - cam.camera_x - 85,x.player_y - cam.camera_y - 100,player_w + 160 ,player_h + 130 };
    SDL_RenderCopy(render, sprite_attackleft, &picture_rect, &rect);

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - time_frame_attack > 20) {
        frame_attack = (frame_attack + 1);
        time_frame_attack = SDL_GetTicks();

    }

    if (frame_attack >= attackFrame_trigger) {
        is_Attacking_Animation_Done = true;
    }

    if (frame_attack >= 7) {
        isattack = false;
        is_Attacking_Animation_Done = true;
        frame_attack = 0;
    }
}

void attack::amination_hit_right(player &p1, SDL_Renderer* render, camera cam) {

    SDL_Rect picture_rect = { 96*frame_hit,0,96,96 };
    SDL_Rect rect = { p1.player_x - cam.camera_x-85,p1.player_y - cam.camera_y-100,player_w+160 ,player_h+130 };
    SDL_RenderCopy(render, sprite_hit_right, &picture_rect, &rect);

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - time_frame_hit > 200) {
        frame_hit = (frame_hit + 1);
        time_frame_hit = SDL_GetTicks();
    }
    if (frame_hit >= 4) {
        p1.player_hit = false;
        time_frame_hit = 0;
    }
}

void attack::amination_hit_left(player &p1, SDL_Renderer* render, camera cam) {

    SDL_Rect picture_rect = { 96 * (3-frame_hit),0,96,96 };
    SDL_Rect rect = { p1.player_x - cam.camera_x-85,p1.player_y - cam.camera_y-100,player_w+160,player_h+130};
    SDL_RenderCopy(render, sprite_hit_left, &picture_rect, &rect);

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - time_frame_hit > 200) {
        frame_hit = (frame_hit + 1);
        time_frame_hit = SDL_GetTicks();
    }
    if (frame_hit >= 4) {
        p1.player_hit = false;
        frame_hit = 0;
    }
}

