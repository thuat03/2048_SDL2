#pragma once

#include"const.h"

void init(SDL_Window*& window, SDL_Renderer*& renderer);

SDL_Texture* loadTexture(const std::string& path, SDL_Renderer*& renderer);

void loadFont(TTF_Font*& gFont);

void setupButton(LButton& button, const std::string& title, const int& x, const int& y, SDL_Renderer*& renderer, TTF_Font*& gFont);

void loadPicture(SDL_Texture** gTexture, SDL_Renderer*& renderer);

int loadFile(std::fstream& file);

void loadMatrix(std::fstream& file, int** matrix, bool& isDataEmpty);

void saveScore(const int& highscore, const std::string& path);

void saveMatrix(int** matrix);

void loadSound(Mix_Chunk*& gSFX);

void loadMusic(Mix_Music*& gMusic, const char* path);

void setPositionOfPicture(SDL_Rect* picure);

void Render_Copy(SDL_Renderer*& renderer, SDL_Texture** Texture, SDL_Rect* RectPicture, int** matran, const int& mode, const int& player);

void freeButtons(LButton& button);

void freeTexture(LTexture& renderTexture);

void freeSoundEffects(Mix_Chunk*& gSFX);

void freeMusic(Mix_Music*& gMusic);

void freeFont(TTF_Font*& gFont);

void freeWindowAndRenderer(SDL_Window*& window, SDL_Renderer*& renderer);

void quit();