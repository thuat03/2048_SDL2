#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<iostream>
#include<fstream>

#include"const.h"
#include"LButton.h"
#include"LTexture.h"
#include"gameEngine.h"
#include"function.h"
#include"settings.h"
#include"variable.h"
#include"setup.h"
#include"theGame.h"

TheGame* thegame = new TheGame;
int main(int argc, char** args) {
	//set up SDL
	setup();

	//Game loop
	thegame->render();
	while (thegame->getStatusPresent() != EXIT_STATUS) {
		thegame->updateStatus();
		thegame->render();
	}

	//save data and quit SDL
	quitSDL();
	return 0;
}