#include"attack.h"

bool attack::loadattack(SDL_Renderer* render) {
    char path[50];
    for (int i = 4; i < 8; i++) {
        sprintf_s(path, "picture/ATTACK_right%d.png", i);
        sprite_attackright[i - 4] = Loadsprite(path, render);
        picture_.push_back( {picture_w,picture_h });
        if (sprite_attackright[i - 4] == NULL) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 2; i < 6; i++) {
        sprintf_s(path, "picture/ATTACK_left%d.png", i);
        sprite_attackleft[i - 2] = Loadsprite(path, render);  
        picture_2.push_back({ picture_w,picture_h });
        if (sprite_attackleft[i - 2] == NULL) {  
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path, "picture/HURT_right_%d.png", i);
        sprite_hit_right[i] = Loadsprite(path, render);
        if (sprite_hit_right[i] == NULL) {
            cout << SDL_GetError();
            return false;
        }
    }

    for (int i = 0; i < 4; i++) {
        sprintf_s(path, "picture/HURT_left_%d.png", i);
        sprite_hit_left[i] = Loadsprite(path, render);
        if (sprite_hit_left[i] == NULL) {
            cout << SDL_GetError();
            return false;
        }
    }

    return true;

}

void attack::aminationattackright(int fame, SDL_Renderer* render, camera cam, player x) {
    SDL_Rect rect;
    rect = { x.player_x - cam.camera_x,x.player_y - cam.camera_y ,picture_[fame].first,picture_[fame].second };
    SDL_RenderCopy(render, sprite_attackright[fame], NULL, &rect);
}
void attack::aminationattackleft(int fame, SDL_Renderer* render, camera cam, player x) {
    SDL_Rect rect;
    int m;
    if (fame == 1) {
        m = 70;
    }
    else m = 0;
    rect = { x.player_x - cam.camera_x -m,x.player_y - cam.camera_y ,picture_2[fame].first,picture_2[fame].second };
  
    SDL_RenderCopy(render, sprite_attackleft[fame], NULL, &rect);
}
void attack::amination_hit_right(int fame, SDL_Renderer* render, camera cam, player x) {
    SDL_Rect rect = { x.player_x - cam.camera_x,x.player_y - cam.camera_y ,player_w,player_h };
    SDL_RenderCopy(render, sprite_hit_right[fame], NULL, &rect);
}
void attack::amination_hit_left(int fame, SDL_Renderer* render, camera cam, player x) {
    SDL_Rect rect = { x.player_x - cam.camera_x,x.player_y - cam.camera_y ,player_w,player_h};
    SDL_RenderCopy(render, sprite_hit_left[fame], NULL, &rect);
}

