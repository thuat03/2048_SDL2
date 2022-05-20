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

std::string startup();

void setupSingleGame();

void setupMultiGame();

std::string game_play_single();

std::string game_play_multi();

std::string pause();

std::string win();

std::string lose();

int TheGame::getStatusPresent() {
	return this->status;
}

void TheGame::updateStatus() {
	if (this->status_next == "menu") {
		if (this->status == PAUSE_STATUS || this->status == WIN_STATUS || this->status == LOSE_STATUS) {
			isDataEmpty = true;
			Mix_HaltMusic();
			this->status = MAIN_MENU_STATUS;
		}
		if (this->status == STARTUP_STATUS || this->status == GAME_PLAY_MULTI_STATUS) {
			this->status = MAIN_MENU_STATUS;
		}
		return;
	}
	if (this->status_next == "startup") {
		if (this->status == MAIN_MENU_STATUS) {
			this->status = STARTUP_STATUS;
		}
		return;
	}
	if (this->status_next == "single") {
		if (this->status == STARTUP_STATUS) {
			setupSingleGame();
			mode = SINGLE;
			this->status = GAME_PLAY_SINGLE_STATUS;
		}
		return;
	}

	if (this->status_next == "multi") {
		if (this->status == STARTUP_STATUS) {
			mode = MULTI;
			setupMultiGame();
			this->status = GAME_PLAY_MULTI_STATUS;
		}
		return;
	}

	if (this->status_next == "continue_saveGame") {
		if (this->status == MAIN_MENU_STATUS) {
			mode = SINGLE;
			this->status = GAME_PLAY_SINGLE_STATUS;
		}
		return;
	}

	if (this->status_next == "win") {
		if (this->status == GAME_PLAY_SINGLE_STATUS) {
			this->status = WIN_STATUS;
		}
		return;
	}

	if (this->status_next == "lose") {
		if (this->status == GAME_PLAY_SINGLE_STATUS) {
			this->status = LOSE_STATUS;
		}
		return;
	}

	if (this->status_next == "pause") {
		if (this->status == GAME_PLAY_SINGLE_STATUS || this->status == GAME_PLAY_MULTI_STATUS) {
			this->status = PAUSE_STATUS;
		}
		return;
	}

	if (this->status_next == "continue") {
		if (this->status == PAUSE_STATUS) {
			if (mode == SINGLE)
			{
				this->status = GAME_PLAY_SINGLE_STATUS;
			}
			else
			{
				this->status = GAME_PLAY_MULTI_STATUS;
			}
		}
		return;
	}

	if (this->status_next == "again") {
		if (this->status == WIN_STATUS || this->status == LOSE_STATUS) {
			setupSingleGame();
			this->status = GAME_PLAY_SINGLE_STATUS;
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
		case STARTUP_STATUS:
		{
			this->status_next = startup();
			break;
		}
		case GAME_PLAY_SINGLE_STATUS:
		{
			this->status_next = game_play_single();
			break;
		}
		case GAME_PLAY_MULTI_STATUS:
		{
			this->status_next = game_play_multi();
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
	//Mix_HaltMusic();
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}
			if (Mix_PlayingMusic() == 0 && settings.music) {
				Mix_PlayMusic(gMusicMenu, -1);
			}
			if (Mix_PlayingMusic() == 1 && !settings.music) {
				Mix_HaltMusic();
			}
			SDL_RenderClear(renderer);

			SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);

			gButton[START].handleEvent(&e);
			gButton[EXIT].handleEvent(&e);
			if (settings.sfx) {
				gButton[SFX_ON].handleEvent(&e);
			}
			else {
				gButton[SFX_OFF].handleEvent(&e);
			}

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
		if (settings.sfx) {
			gButton[SFX_ON].render(renderer);
		}
		else {
			gButton[SFX_OFF].render(renderer);
		}

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
		renderTexture.render(300, 50, renderer);

		//Ấn vào start để bắt đầu 
		if (gButton[START].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[START].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			//Mix_HaltMusic();
			return "startup";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		//
		if (gButton[SFX_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.sfx) {
			settings.sfx = false;

			gButton[SFX_ON].freeStatus();
		}

		if (gButton[SFX_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.sfx) {

			settings.sfx = true;

			Mix_PlayChannel(-1, gSFX, 0);

			gButton[SFX_OFF].freeStatus();
		}
		//
		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;

			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}

			gButton[MUSIC_ON].freeStatus();
		}

		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {

			settings.music = true;

			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}

			gButton[MUSIC_OFF].freeStatus();
		}
		//
		if (!isDataEmpty) {
			if (gButton[CONTINUE_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				if (settings.sfx) {
					Mix_PlayChannel(-1, gSFX, 0);
				}
				getEqualArray(data_save, data);
				getEqualArray(data_save, data);
				score = loadFile(CurrentScore);
				Mix_HaltMusic();
				return "continue_saveGame";
			}
		}

		//Update screen
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}

std::string startup()
{
	SDL_Event e;
	while (1) {

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				return "quit";
			}
			if (e.key.repeat == 0 && e.type == SDL_KEYDOWN) {

				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
				{
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);
					SDL_Delay(100);

					if (settings.sfx) {
						Mix_PlayChannel(-1, gSFX, 0);
					}
					return "menu";
				}

				}
			}
			if (Mix_PlayingMusic() == 0 && settings.music) {
				Mix_PlayMusic(gMusicMenu, -1);
			}

			if (Mix_PlayingMusic() == 1 && !settings.music) {
				Mix_HaltMusic();
			}

			SDL_RenderClear(renderer);

			gButton[SINGLE_PLAYER].handleEvent(&e);
			gButton[MULTIPLAYER].handleEvent(&e);
		}

		SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);

		gButton[SINGLE_PLAYER].render(renderer);
		gButton[MULTIPLAYER].render(renderer);

		renderTexture.loadFromRenderedText("Choose game mode.", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào continue để chơi tiếp
		if (gButton[SINGLE_PLAYER].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[SINGLE_PLAYER].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			Mix_HaltMusic();
			return "single";
		}

		//Ấn vào Save and exit để lưu và thoát.
		if (gButton[MULTIPLAYER].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[MULTIPLAYER].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			Mix_HaltMusic();
			return "multi";
		}

		SDL_RenderPresent(renderer);

		SDL_Delay(1000 / FPS);
	}
}

void setupSingleGame()
{
	score = 0;
	deleteData(data);
	deleteData(data_check);
	data = createData();
	data_check = createData();
	randomUpgrade(data);
}

void setupMultiGame()
{
	score_player1 = 0;
	score_player2 = 0;
	deleteData(data_player1);
	deleteData(data_player2);
	deleteData(data_check_player1);
	deleteData(data_check_player2);
	data_player1 = createData();
	randomUpgrade(data_player1);
	data_player2 = createData();
	randomUpgrade(data_player2);
	data_check_player1 = createData();
	data_check_player2 = createData();
}

std::string game_play_single()
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
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_a: {
						updateData(data, 'a', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_s: {
						updateData(data, 's', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_d: {
						updateData(data, 'd', score);
						if (isPossibleMove(data, data_check)) {

							randomUpgrade(data);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_ESCAPE: {
						if (settings.sfx) {
							Mix_PlayChannel(-1, gSFX, 0);
						}
						return "pause";
					}
				}

				if (score > highscore) {
					highscore = score;
				}
			}

			if (Mix_PlayingMusic() == 0 && settings.music) {
				Mix_PlayMusic(gMusicGamePlay, -1);
			}

			if (Mix_PlayingMusic() == 1 && !settings.music) {
				Mix_HaltMusic();
			}
		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);
		//Văn bản chuẩn bị xuất hiện trên nền 
		std::string currentscore = "Your score: " + std::to_string(score);
		std::string _highscore = "High score: " + std::to_string(highscore);

		//Hiển thị khung hình hiện tại 

		SDL_RenderCopy(renderer, gTexture[0], NULL, &RectPicture[0]);// Kết xuất hình ảnh nền

		//Kết xuất từng ô một 
		Render_Copy(renderer, gTexture, RectPicture, data, 1, 1);


		renderTexture.loadFromRenderedText(currentscore, BLUE_COLOR, renderer, gFont);//Nội dung cần vẽ + Màu vẽ. (vẽ chữ)
		renderTexture.render(255, 5, renderer);//Tọa độ cần vẽ (chữ): x,y;

		renderTexture.loadFromRenderedText(_highscore, BLUE_COLOR, renderer, gFont);
		renderTexture.render(255, 55, renderer);
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

std::string game_play_multi()
{
	bool player1_complete = false;
	bool player2_complete = false;
	SDL_Event e;
	while (1) {
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&e) != 0) {

			if (e.type == SDL_QUIT) {
				return "quit";
			}
			if (player1_complete && player2_complete) {
				gButton[MAIN_MENU_END_MULTI].handleEvent(&e);
			}
			//e.key.repeat == 0 && 
			if (e.type == SDL_KEYDOWN) {
				getEqualArray(data_player1, data_check_player1);
				getEqualArray(data_player2, data_check_player2);
				switch (e.key.keysym.sym){
					case SDLK_w: {
						updateData(data_player1, 'w', score_player1);
						if (isPossibleMove(data_player1, data_check_player1)) {

							randomUpgrade(data_player1);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_a: {
						updateData(data_player1, 'a', score_player1);
						if (isPossibleMove(data_player1, data_check_player1)) {

							randomUpgrade(data_player1);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_s: {
						updateData(data_player1, 's', score_player1);
						if (isPossibleMove(data_player1, data_check_player1)) {

							randomUpgrade(data_player1);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_d: {
						updateData(data_player1, 'd', score_player1);
						if (isPossibleMove(data_player1, data_check_player1)) {

							randomUpgrade(data_player1);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_UP:
					{
						updateData(data_player2, 'w', score_player2);
						if (isPossibleMove(data_player2, data_check_player2)) {

							randomUpgrade(data_player2);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_LEFT:
					{
						updateData(data_player2, 'a', score_player2);
						if (isPossibleMove(data_player2, data_check_player2)) {

							randomUpgrade(data_player2);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_DOWN:
					{
						updateData(data_player2, 's', score_player2);
						if (isPossibleMove(data_player2, data_check_player2)) {

							randomUpgrade(data_player2);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_RIGHT:
					{
						updateData(data_player2, 'd', score_player2);
						if (isPossibleMove(data_player2, data_check_player2)) {

							randomUpgrade(data_player2);
							if (settings.sfx) {
								Mix_PlayChannel(-1, gSFX, 0);
							}
						}
						break;
					}
					case SDLK_ESCAPE: {
						if (settings.sfx) {
							Mix_PlayChannel(-1, gSFX, 0);
						}
						return "pause";
					}
				}

				if (score_player1 > highscore) {
					highscore = score_player1;
				}
				if (score_player2 > highscore) {
					highscore = score_player2;
				}
			}

			if (Mix_PlayingMusic() == 0 && settings.music) {
				Mix_PlayMusic(gMusicGamePlay, -1);
			}

			if (Mix_PlayingMusic() == 1 && !settings.music) {
				Mix_HaltMusic();
			}
		}


		SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);
		//Văn bản chuẩn bị xuất hiện trên nền 
		std::string currentscore1 = "Player1's score: " + std::to_string(score_player1);
		std::string currentscore2 = "Player2's score: " + std::to_string(score_player2);

		//Hiển thị khung hình hiện tại 
		if (!check_lose(data_player1)&&!check_win(data_player1)) {
			SDL_RenderCopy(renderer, gTexture[0], NULL, &RectPicture[18]);// Kết xuất hình ảnh nền

			Render_Copy(renderer, gTexture, RectPicture, data_player1, 2, 1);

			renderTexture.loadFromRenderedText(currentscore1, BLUE_COLOR, renderer, gFont);//Nội dung cần vẽ + Màu vẽ. (vẽ chữ)

			renderTexture.render(5, 5, renderer);//Tọa độ cần vẽ (chữ): x,y;
		}

		if (!check_lose(data_player2) && !check_win(data_player2)) {
			SDL_RenderCopy(renderer, gTexture[0], NULL, &RectPicture[35]);

			Render_Copy(renderer, gTexture, RectPicture, data_player2, 2, 2);

			renderTexture.loadFromRenderedText(currentscore2, CYAN_COLOR, renderer, gFont);

			renderTexture.render(505, 5, renderer);
		}

		if (check_lose(data_player1)||check_win(data_player1)) {
			player1_complete = true;
			std::string lose1 = "You've done!";
			renderTexture.loadFromRenderedText(lose1, BLUE_COLOR, renderer, gFont);
			renderTexture.render(50, 175, renderer);

			renderTexture.loadFromRenderedText(currentscore1, BLUE_COLOR, renderer, gFont);
			renderTexture.render(50, 250, renderer);
		}

		if (check_lose(data_player2) || check_win(data_player2)) {
			player2_complete = true;
			std::string lose2 = "You've done!";
			renderTexture.loadFromRenderedText(lose2, CYAN_COLOR, renderer, gFont);
			renderTexture.render(500, 175, renderer);

			renderTexture.loadFromRenderedText(currentscore2, CYAN_COLOR, renderer, gFont);
			renderTexture.render(500, 250, renderer);
		}
		//Cập nhật màn hình 

		if (player1_complete && player2_complete) {
			SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);
			if (score_player1 > score_player2) {
				renderTexture.loadFromRenderedText("Player 1 win with score: " + std::to_string(score_player1), BLUE_COLOR, renderer, gFont);
				renderTexture.render(175, 100, renderer);
			}
			else if (score_player1 < score_player2) {
				renderTexture.loadFromRenderedText("Player 2 win with score: " + std::to_string(score_player2), CYAN_COLOR, renderer, gFont);
				renderTexture.render(175, 100, renderer);
			}
			else {
				renderTexture.loadFromRenderedText("2 Players draw with score: " + std::to_string(score_player1), CYAN_COLOR, renderer, gFont);
				renderTexture.render(175, 100, renderer);
			}
			gButton[MAIN_MENU_END_MULTI].render(renderer);
			if (gButton[MAIN_MENU_END_MULTI].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
				gButton[MAIN_MENU_END_MULTI].freeStatus();
				if (settings.sfx) {
					Mix_PlayChannel(-1, gSFX, 0);
				}
				Mix_HaltMusic();
				return "menu";
			}
		}
		SDL_RenderPresent(renderer);

		//Dừng SDL 
		SDL_Delay(1000 / FPS);
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
			if (e.key.repeat == 0 && e.type == SDL_KEYDOWN) {

				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
					{
						SDL_RenderClear(renderer);
						SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);
						SDL_Delay(100);

						if (settings.sfx) {
							Mix_PlayChannel(-1, gSFX, 0);
						}
						Mix_HaltMusic();
						return "menu";
					}

				}
			}
			if (Mix_PlayingMusic() == 0 && settings.music) {
				Mix_PlayMusic(gMusicGamePlay, -1);
			}

			if (Mix_PlayingMusic() == 1 && !settings.music) {
				Mix_HaltMusic();
			}

			SDL_RenderClear(renderer);

			gButton[CONTINUE_GAMEPLAY].handleEvent(&e);
		
			if (mode == SINGLE)
			{
				gButton[SAVE_AND_EXIT].handleEvent(&e);
			}

			if (settings.sfx) {
				gButton[SFX_ON].handleEvent(&e);
			}
			else {
				gButton[SFX_OFF].handleEvent(&e);
			}

			if (settings.music) {
				gButton[MUSIC_ON].handleEvent(&e);
			}
			else {
				gButton[MUSIC_OFF].handleEvent(&e);
			}
		}

		SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);

		gButton[CONTINUE_GAMEPLAY].render(renderer);
		gButton[SAVE_AND_EXIT].render(renderer);

		if (settings.sfx) {
			gButton[SFX_ON].render(renderer);
		}
		else {
			gButton[SFX_OFF].render(renderer);
		}

		if (settings.music) {
			gButton[MUSIC_ON].render(renderer);
		}
		else {
			gButton[MUSIC_OFF].render(renderer);
		}

		renderTexture.loadFromRenderedText("Game Paused!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//
		if (gButton[SFX_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.sfx) {
			settings.sfx = false;
			gButton[SFX_ON].freeStatus();
		}
		if (gButton[SFX_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.sfx) {
			settings.sfx = true;

			Mix_PlayChannel(-1, gSFX, 0);

			gButton[SFX_OFF].freeStatus();
		}
		//
		
		if (gButton[MUSIC_ON].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && settings.music) {
			settings.music = false;

			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}

			gButton[MUSIC_ON].freeStatus();
		}

		if (gButton[MUSIC_OFF].getStatus() == BUTTON_SPRITE_MOUSE_DOWN && !settings.music) {

			settings.music = true;

			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}

			gButton[MUSIC_OFF].freeStatus();
		}
		//Ấn vào continue để chơi tiếp
		if (gButton[CONTINUE_GAMEPLAY].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[CONTINUE_GAMEPLAY].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			return "continue";
		}

		//Ấn vào Save and exit để lưu và thoát.
		if (gButton[SAVE_AND_EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			isSaveData = true;
			gButton[SAVE_AND_EXIT].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
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

			SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);

			gButton[EXIT].handleEvent(&e);

			gButton[MAIN_MENU].handleEvent(&e);
		}


		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);
		gButton[MAIN_MENU].render(renderer);

		renderTexture.loadFromRenderedText("You Win!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);

		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[PLAY_AGAIN].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			return "again";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		if (gButton[MAIN_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[MAIN_MENU].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			SDL_Delay(100);
			return "menu";
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

			SDL_RenderCopy(renderer, gTexture[12], NULL, &RectPicture[17]);

			gButton[PLAY_AGAIN].handleEvent(&e);

			gButton[EXIT].handleEvent(&e);

			gButton[MAIN_MENU].handleEvent(&e);
		}


		gButton[PLAY_AGAIN].render(renderer);
		gButton[EXIT].render(renderer);
		gButton[MAIN_MENU].render(renderer);

		renderTexture.loadFromRenderedText("You Lose!", BLUE_COLOR, renderer, gFont);
		renderTexture.render(25, 50, renderer);
		
		//Ấn vào "Play Again" để chơi lại 
		if (gButton[PLAY_AGAIN].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[PLAY_AGAIN].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			return "again";
		}

		//Ấn vào exit để thoát 
		if (gButton[EXIT].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[EXIT].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			SDL_Delay(500);
			return "quit";
		}

		if (gButton[MAIN_MENU].getStatus() == BUTTON_SPRITE_MOUSE_DOWN) {
			gButton[MAIN_MENU].freeStatus();
			if (settings.sfx) {
				Mix_PlayChannel(-1, gSFX, 0);
			}
			SDL_Delay(100);
			return "menu";
		}

		SDL_RenderPresent(renderer);
		//Dừng SDL 
		SDL_Delay(1000 / FPS);
	}
}
