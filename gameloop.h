#ifndef gameloop_h
#define gameloop_h
#include"khaibao.h"
#include"image.h"
extern int window_r;
extern int window_h;
extern int backgroundset;

extern SDL_Texture* metal[100];
extern SDL_Texture* back;
extern SDL_Window* window;
extern SDL_Renderer* render;




void gameloop() {
	int quit = 0;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = 1;
			}
		}
		backgroundset -= 1;
		if (backgroundset < -800) {
			backgroundset = 0;
		}
		SDL_SetRenderDrawColor(render, 80, 55, 137, 255);
		SDL_RenderClear(render);
		// lop1
		SDL_RenderCopy(render, back, NULL, NULL);
		// lop 2
		movebackground(backgroundset);
		SDL_Delay(10);
		// lop3
		inmeta();
		SDL_RenderPresent(render);
	}
}


#endif // !gameloop_h

