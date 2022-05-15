#pragma once

class TheGame {
	std::string status_next;
	int status;
public:
	TheGame() {
		this->status_next = "menu";
		this->status = MAIN_MENU_STATUS;
	}

	int getStatusPresent();

	void updateStatus();

	void render();
};

std::string main_menu();

void setupGame();

std::string game_play();

std::string pause();

std::string win();

std::string lose();

int TheGame::getStatusPresent() {
	return this->status;
}

void TheGame::updateStatus() {
	if (this->status_next == "start") {
		if (this->status == MAIN_MENU_STATUS) {
			setupGame();
			this->status = GAME_PLAY_STATUS;
		}
		return;
	}
	if (this->status_next == "continue_saveGame") {
		if (this->status == MAIN_MENU_STATUS) {
			

			this->status = GAME_PLAY_STATUS;
		}
	}
	if (this->status_next == "win") {
		if (this->status == GAME_PLAY_STATUS) {
			this->status = WIN_STATUS;
		}
		return;
	}
	if (this->status_next == "lose") {
		if (this->status == GAME_PLAY_STATUS) {
			this->status = LOSE_STATUS;
		}
		return;
	}
	if (this->status_next == "pause") {
		if (this->status == GAME_PLAY_STATUS) {
			this->status = PAUSE_STATUS;
		}
		return;
	}
	if (this->status_next == "continue") {
		if (this->status == PAUSE_STATUS) {
			this->status = GAME_PLAY_STATUS;
		}
		return;
	}
	if (this->status_next == "again") {
		if (this->status == WIN_STATUS || this->status == LOSE_STATUS) {
			setupGame();
			this->status = GAME_PLAY_STATUS;
		}
		return;
	}
	if (this->status_next == "quit") {
		this->status = EXIT_STATUS;
		return;
	}
}

void TheGame::render() {
	switch (this->status) {
		case MAIN_MENU_STATUS:
		{
			this->status_next = main_menu();
			break;
		}
		case GAME_PLAY_STATUS:
		{
			this->status_next = game_play();
			break;
		}
		case PAUSE_STATUS:
		{
			this->status_next = pause();
			break;
		}
		case WIN_STATUS:
		{
			this->status_next = win();
			break;
		}
		case LOSE_STATUS:
		{
			this->status_next = lose();
			break;
		}
	}
}

std::string main_menu()
{
	SDL_Event e;
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}

			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[START].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
			if (settings.music) {
				gButton[MUSIC_ON].handleEvent(&e);
			}
			else {
				gButton[MUSIC_OFF].handleEvent(&e);
			}
			if (!isDataEmpty) {
				gButton[CONTINUE_MENU].handleEvent(&e);
			}
		}


		gButton[START].render(renderer);
		gButton[EXIT].render(renderer);
		if (settings.music) {
			gButton[MUSIC_ON].render(renderer);
		}
		else {
			gButton[MUSIC_OFF].render(renderer);
		}
		if (!isDataEmpty) {
			gButton[CONTINUE_MENU].render(renderer);
		}

		renderTexture.loadFromRenderedText("Welcome to 2048!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào start để bắt đầu 
		if (gButton[START].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[START].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			return "start";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		//
		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;

			gButton[MUSIC_ON].freeStatus();
		}

		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {

			settings.music = true;

			Mix_PlayChannel(-1, gMusic, 0);

			gButton[MUSIC_OFF].freeStatus();
		}
		//
		if (!isDataEmpty) {
			if (gButton[CONTINUE_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				if (settings.music) {
					Mix_PlayChannel(-1, gMusic, 0);
				}
				getEqualArray(data_save, data);
				getEqualArray(data_save, data);
				score = loadFile(CurrentScore);
				return "continue_saveGame";
			}
		}

		//Update screen
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

void setupGame()
{
	score = 0;
	data = createData();
	data_check = createData();
	randomUpgrade(data);
}

std::string game_play()
{
	SDL_Event e;

	while (1) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				return "quit";
			}
			if (e.key.repeat == 0 && e.type == SDL_KEYDOWN) {
				getEqualArray(data, data_check);
				switch (e.key.keysym.sym) {
					case SDLK_w: {
						updateData(data, 'w', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.music) {
								Mix_PlayChannel(-1, gMusic, 0);
							}
						}
						break;
					}
					case SDLK_a: {
						updateData(data, 'a', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.music) {
								Mix_PlayChannel(-1, gMusic, 0);
							}
						}
						break;
					}
					case SDLK_s: {
						updateData(data, 's', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.music) {
								Mix_PlayChannel(-1, gMusic, 0);
							}
						}
						break;
					}
					case SDLK_d: {
						updateData(data, 'd', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.music) {
								Mix_PlayChannel(-1, gMusic, 0);
							}
						}
						break;
					}
					case SDLK_ESCAPE: {
						if (settings.music) {
							Mix_PlayChannel(-1, gMusic, 0);
						}
						return "pause";
					}
				}

				if (score > highscore) {
					highscore = score;
				}
			}
		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);
		//Văn bản chuẩn bị xuất hiện trên nền 
		std::string currentscore = "Your score: " + std::to_string(score);
		std::string _highscore = "High score: " + std::to_string(highscore);

		//Hiển thị khung hình hiện tại 

		SDL_RenderCopy(renderer, gTexture[0], NULL, &picture[0]);// Kết xuất hình ảnh nền

		//Kết xuất từng ô một 

		Render_Copy(renderer, gTexture, picture, data);



		renderTexture.loadFromRenderedText(currentscore, BLUE_COLOR, renderer, gFont);//Nội dung cần vẽ + Màu vẽ. (vẽ chữ)
		renderTexture.render(5, 5, renderer);//Tọa độ cần vẽ (chữ): x,y;

		renderTexture.loadFromRenderedText(_highscore, BLUE_COLOR, renderer, gFont);
		renderTexture.render(5, 55, renderer);
		//Cập nhật màn hình 
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);

		if (check_win(data)) {
			SDL_Delay(750);
			return "win";
		}
		if (check_lose(data)) {
			SDL_Delay(750);
			return "lose";
		}
	}
}

std::string pause()
{
	SDL_Event e;
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}

			SDL_RenderClear(renderer);

			gButton[CONTINUE_GAMEPLAY].handleEvent(&e);
			gButton[SAVE_AND_EXIT].handleEvent(&e);

			if (settings.music) {
				gButton[MUSIC_ON].handleEvent(&e);
			}
			else {
				gButton[MUSIC_OFF].handleEvent(&e);
			}
			if (!isDataEmpty) {
				gButton[CONTINUE_MENU].handleEvent(&e);
			}


		}

		SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

		gButton[CONTINUE_GAMEPLAY].render(renderer);
		gButton[SAVE_AND_EXIT].render(renderer);

		if (settings.music) {
			gButton[MUSIC_ON].render(renderer);
		}
		else {
			gButton[MUSIC_OFF].render(renderer);
		}

		renderTexture.loadFromRenderedText("Game Paused!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;
			gButton[MUSIC_ON].freeStatus();
		}
		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {
			settings.music = true;

			Mix_PlayChannel(-1, gMusic, 0);

			gButton[MUSIC_OFF].freeStatus();
		}

		//Ấn vào continue để chơi tiếp
		if (gButton[CONTINUE_GAMEPLAY].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[CONTINUE_GAMEPLAY].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			return "continue";
		}

		//Ấn vào Save and exit để lưu và thoát.
		if (gButton[SAVE_AND_EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			isSaveData = true;
			gButton[SAVE_AND_EXIT].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			SDL_Delay(500);
			saveMatrix(data);
			saveScore(score, "2048_Data/current score.txt");
			return "quit";
		}

		SDL_RenderPresent(renderer);

		SDL_Delay(1000 / FPS);
	}
}

std::string win()
{
	SDL_Event e;
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}
			
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);

			gButton[EXIT].handleEvent(&e);
		}


		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);

		renderTexture.loadFromRenderedText("You Win!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[PLAY_AGAIN].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			return "again";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

std::string lose()
{
	SDL_Event e;
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}

			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &picture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);

			gButton[EXIT].handleEvent(&e);
		}


		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);

		renderTexture.loadFromRenderedText("You Lose!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[PLAY_AGAIN].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			return "again";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.music) {
				Mix_PlayChannel(-1, gMusic, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}
