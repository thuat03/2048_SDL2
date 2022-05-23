#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<fstream>
#include<string>
#include<iostream>

#include"const.h"
#include"LTexture.h"
#include"LButton.h"
#include"LButtonSprite.h"
#include"function.h"

void init(SDL_Window*& window, SDL_Renderer*& renderer) {
	//Create window
	window = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);

	//Create vsynced renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, WHITE_COLOR.r, WHITE_COLOR.g, WHITE_COLOR.b, WHITE_COLOR.a);

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);

	//Initialize SDL_ttf
	TTF_Init();

	//Initialize SDL_Mixer
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer*& renderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

void loadFont(TTF_Font*& gFont) {
	//load font for use
	gFont = TTF_OpenFont("2048_Data/font.ttf", 32);
	if (gFont == NULL) {
		std::cout << "Unable to load Font!" << SDL_GetError() << std::endl;
	}
}

void setupButton(LButton& button, const std::string& title, const int& x, const int& y, SDL_Renderer*& renderer, TTF_Font*& gFont) {
	button.setTexture(title, DEFAULT_STATUS, GREEN_COLOR, renderer, gFont);
	button.setTexture(title, TRIGGERED_STATUS, RED_COLOR, renderer, gFont);

	button.setPosition(x, y);
}

void loadPicture(SDL_Texture** gTexture, SDL_Renderer*& renderer) {
	//load RectPicture for use
	gTexture[0] = loadTexture("2048_Data/background.png", renderer);
	gTexture[1] = loadTexture("2048_Data/2.png", renderer);
	gTexture[2] = loadTexture("2048_Data/4.png", renderer);
	gTexture[3] = loadTexture("2048_Data/8.png", renderer);
	gTexture[4] = loadTexture("2048_Data/16.png", renderer);
	gTexture[5] = loadTexture("2048_Data/32.png", renderer);
	gTexture[6] = loadTexture("2048_Data/64.png", renderer);
	gTexture[7] = loadTexture("2048_Data/128.png", renderer);
	gTexture[8] = loadTexture("2048_Data/256.png", renderer);
	gTexture[9] = loadTexture("2048_Data/512.png", renderer);
	gTexture[10] = loadTexture("2048_Data/1024.png", renderer);
	gTexture[11] = loadTexture("2048_Data/2048.png", renderer);
	gTexture[12] = loadTexture("2048_Data/background menu.jpg", renderer);
	for (int i = 0; i < TOTAL_PICTURE; i++) {
		if (gTexture[i] == NULL) {
			std::cout << "Unable to load image!" << SDL_GetError() << std::endl;
		}
	}
}

int loadFile(std::fstream& file) {
	//Lấy dữ liệu từ file (file chỉ gồm 1 dòng duy nhất chứa score)
	int n;
	file >> n;
	return n;
}

void loadMatrix(std::fstream& file, int** matrix, bool& isDataEmpty) {
	int num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			file >> num;
			matrix[i][j] = num;
			if (num != 0)isDataEmpty = false;
		}
	}
}

void saveScore(const int& score, const std::string& path) {

	//Xoá dữ liệu trong file chuẩn bị cho việc lưu dữ liệu mới 
	std::ofstream ofs;
	ofs.open(path, std::ios::out, std::ios::trunc);
	ofs.close();

	//Lưu dữ liệu mới 
	std::ofstream saveData(path);
	saveData << score;
	saveData.close();
}

void saveMatrix(int** matrix) {
	//Xoá dữ liệu trong file chuẩn bị cho việc lưu dữ liệu mới 
	std::ofstream ofs;
	ofs.open("2048_Data/du lieu ma tran.txt", std::ios::out, std::ios::trunc);
	ofs.close();

	//Lưu dữ liệu mới 
	std::ofstream saveData("2048_Data/du lieu ma tran.txt");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			saveData << matrix[i][j] << ' ';
		}
	}
	saveData.close();
}

void loadSound(Mix_Chunk*& gSFX) {
	//Load sound effect
	gSFX = Mix_LoadWAV("2048_Data/sfx.wav");
	if (gSFX == NULL) {
		std::cout << "Unable to load sound effect!" << SDL_GetError() << std::endl;
	}
}

void loadMusic(Mix_Music*& gMusic, const char* path) {
	gMusic = Mix_LoadMUS(path);
	if (gMusic == NULL) {
		std::cout << "Unable to load music!" << SDL_GetError() << std::endl;
	}
}

void setPositionOfPicture(SDL_Rect* RectPicture) {
	//Single player
	RectPicture[0] = { 250,100,400,400 };
	RectPicture[1] = { 260,110,87,87 };
	RectPicture[2] = { 357,110,87,87 };
	RectPicture[3] = { 454,110,87,87 };
	RectPicture[4] = { 551,110,87,87 };
	RectPicture[5] = { 260,207,87,87 };
	RectPicture[6] = { 357,207,87,87 };
	RectPicture[7] = { 454,207,87,87 };
	RectPicture[8] = { 551,207,87,87 };
	RectPicture[9] = { 260,304,87,87 };
	RectPicture[10] = { 357,304,87,87 };
	RectPicture[11] = { 454,304,87,87 };
	RectPicture[12] = { 551,304,87,87 };
	RectPicture[13] = { 260,401,87,87 };
	RectPicture[14] = { 357,401,87,87 };
	RectPicture[15] = { 454,401,87,87 };
	RectPicture[16] = { 551,401,87,87 };

	//Background game.
	RectPicture[17] = { 0,0,900,500 };

	//Multiplayer

	//Player 1
	RectPicture[18] = { 0,100,400,400 };
	RectPicture[19] = { 10,110,87,87 };
	RectPicture[20] = { 107,110,87,87 };
	RectPicture[21] = { 204,110,87,87 };
	RectPicture[22] = { 301,110,87,87 };
	RectPicture[23] = { 10,207,87,87 };
	RectPicture[24] = { 107,207,87,87 };
	RectPicture[25] = { 204,207,87,87 };
	RectPicture[26] = { 301,207,87,87 };
	RectPicture[27] = { 10,304,87,87 };
	RectPicture[28] = { 107,304,87,87 };
	RectPicture[29] = { 204,304,87,87 };
	RectPicture[30] = { 301,304,87,87 };
	RectPicture[31] = { 10,401,87,87 };
	RectPicture[32] = { 107,401,87,87 };
	RectPicture[33] = { 204,401,87,87 };
	RectPicture[34] = { 301,401,87,87 };

	//Player 2
	RectPicture[35] = { 500,100,400,400 };
	RectPicture[36] = { 510,110,87,87 };
	RectPicture[37] = { 607,110,87,87 };
	RectPicture[38] = { 704,110,87,87 };
	RectPicture[39] = { 801,110,87,87 };
	RectPicture[40] = { 510,207,87,87 };
	RectPicture[41] = { 607,207,87,87 };
	RectPicture[42] = { 704,207,87,87 };
	RectPicture[43] = { 801,207,87,87 };
	RectPicture[44] = { 510,304,87,87 };
	RectPicture[45] = { 607,304,87,87 };
	RectPicture[46] = { 704,304,87,87 };
	RectPicture[47] = { 801,304,87,87 };
	RectPicture[48] = { 510,401,87,87 };
	RectPicture[49] = { 607,401,87,87 };
	RectPicture[50] = { 704,401,87,87 };
	RectPicture[51] = { 801,401,87,87 };
}

void Render_Copy(SDL_Renderer*& renderer, SDL_Texture** Texture, SDL_Rect* RectPicture, int** matran, const int& mode, const int& player) {
	int add = 0;
	if (mode == MULTI) {
		if (player == PLAYER_1) {
			add = 18;
		}
		else {
			add = 35;
		}
	}

	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			switch (matran[i - 1][j - 1]) {
				case 2: {
					SDL_RenderCopy(renderer, Texture[1], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 4: {
					SDL_RenderCopy(renderer, Texture[2], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 8: {
					SDL_RenderCopy(renderer, Texture[3], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 16: {
					SDL_RenderCopy(renderer, Texture[4], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 32: {
					SDL_RenderCopy(renderer, Texture[5], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 64: {
					SDL_RenderCopy(renderer, Texture[6], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 128: {
					SDL_RenderCopy(renderer, Texture[7], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 256: {
					SDL_RenderCopy(renderer, Texture[8], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 512: {
					SDL_RenderCopy(renderer, Texture[9], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 1024: {
					SDL_RenderCopy(renderer, Texture[10], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
				case 2048: {
					SDL_RenderCopy(renderer, Texture[11], NULL, &RectPicture[(i - 1) * 4 + j + add]);
					break;
				}
			}
		}
	}
}

void freeButtons(LButton& button) {
	button.free();
}

void freeTexture(LTexture& renderTexture) {
	renderTexture.free();
}

void freeSoundEffects(Mix_Chunk*& gSFX) {
	//Free the sound effects
	Mix_FreeChunk(gSFX);
	gSFX = NULL;
}
void freeMusic(Mix_Music*& gMusic) {
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
}

void freeFont(TTF_Font*& gFont) {
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
}

void freeWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer) {
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
}

void quit() {
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}
