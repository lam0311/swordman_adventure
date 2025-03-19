#include"commonFc.h"
#include"map.h"
#include"player.h"
int num_rows = 0; 

void map:: readfile() {
	std::ifstream file("map.txt");
	if (!file) {
		return;
	}

	std::string line;
	while (std::getline(file, line) && num_rows < MAX_ROWS) {
		std::istringstream iss(line);
		int n;
		int col = 0;
		while (iss >> n && col < MAX_COLS) {
			tile_map[num_rows][col] = n;
			col++;
		}
		num_rows++;
	}

	file.close();
}

bool map:: loadTile(SDL_Renderer* render, const char* path,int i) {
	SDL_Surface* surface = IMG_Load(path);
	if (!surface) {
		cout << IMG_GetError();
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
	if (!texture) {
		cout << SDL_GetError();
		return false;
	}
	style_map[i] = texture;

	SDL_FreeSurface(surface);
	return true;
}

void map:: rendermap(SDL_Renderer* render, camera cam) {
	int startX = cam.camera_x / tile_block;
	int startY = cam.camera_y / tile_block;
	int endX = (cam.camera_x + cam.camera_w) / tile_block + 1;
	int endY = (cam.camera_y + cam.camera_h) / tile_block + 1;

	
	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX > MAX_COLS) endX = MAX_COLS;
	if (endY > MAX_ROWS) endY = MAX_ROWS;


	for (int i = startY; i < endY; i++) {
		for (int j = startX; j < endX; j++) {
			int tileType = tile_map[i][j];

			if (tileType > 0) {
				SDL_Rect dstRect = {
					j * tile_block - cam.camera_x, 
					i * tile_block - cam.camera_y, 
					tile_block,
					tile_block
				};
				SDL_RenderCopy(render, style_map[tileType], NULL, &dstRect);
			}
		}
	}
}
