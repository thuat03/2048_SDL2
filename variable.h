#pragma once

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

TTF_Font* gFont = NULL;

Mix_Chunk* gSFX = NULL;

Mix_Music* gMusicMenu = NULL;

Mix_Music* gMusicGamePlay = NULL;

std::fstream HighScore("2048_Data/highscore.txt");

std::fstream Matrix("2048_Data/du lieu ma tran.txt");

std::fstream CurrentScore("2048_Data/current score.txt");

LTexture renderTexture;

SDL_Texture* gTexture[TOTAL_PICTURE];

SDL_Rect RectPicture[TOTAL_RECT];

LButton gButton[TOTAL_BUTTON];


int score = 0;
int score_player1 = 0;
int score_player2 = 0;

int highscore = 0;

bool isDataEmpty = true;

bool isSaveData = false;

Settings settings;

int** data_save = createData();

int** data = createData();

int** data_check = createData();

int** data_player1 = createData();
int** data_player2 = createData();
int** data_check_player1 = createData();
int** data_check_player2 = createData();

int mode;