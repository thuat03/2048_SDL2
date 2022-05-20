#pragma once

void setup() {

	init(window, renderer);

	loadFont(gFont);
	
	loadPicture(gTexture, renderer);

	loadSound(gSFX);

	loadMusic(gMusicMenu, "2048_Data/intro.wav");
	loadMusic(gMusicGamePlay, "2048_Data/gameplay.wav");

	setupButton(gButton[START], "Start", 50, 150, renderer, gFont);
	setupButton(gButton[EXIT], "Exit", 50, 210, renderer, gFont);
	setupButton(gButton[PLAY_AGAIN], "Play Again", 50, 150, renderer, gFont);
	setupButton(gButton[CONTINUE_MENU], "Continue", 50, 390, renderer, gFont);
	setupButton(gButton[CONTINUE_GAMEPLAY], "Continue", 50, 150, renderer, gFont);
	setupButton(gButton[SAVE_AND_EXIT], "Save and exit", 50, 210, renderer, gFont);
	setupButton(gButton[SFX_ON], "SFX: On", 50, 270, renderer, gFont);
	setupButton(gButton[SFX_OFF], "SFX: Off", 50, 270, renderer, gFont);
	setupButton(gButton[MUSIC_ON], "Music: On", 50, 330, renderer, gFont);
	setupButton(gButton[MUSIC_OFF], "Music: Off", 50, 330, renderer, gFont);
	setupButton(gButton[MAIN_MENU], "Main Menu", 50, 270, renderer, gFont);
	setupButton(gButton[SINGLE_PLAYER], "Single Player", 50, 150, renderer, gFont);
	setupButton(gButton[MULTIPLAYER], "Multiplayer", 50, 250, renderer, gFont);
	setupButton(gButton[MAIN_MENU_END_MULTI], "Main Menu", 350, 225, renderer, gFont);

	setPositionOfPicture(RectPicture);

	highscore = loadFile(HighScore);

	loadMatrix(Matrix, data_save, isDataEmpty);
}

void quitSDL() {
	deleteData(data);
	deleteData(data_check);
	deleteData(data_save);
	deleteData(data_player1);
	deleteData(data_player2);
	deleteData(data_check_player1);
	deleteData(data_check_player2);
	//Lưu dữ liệu 
	saveScore(highscore, "2048_Data/highscore.txt");

	if (!isSaveData) {
		saveScore(0, "2048_Data/current score.txt");

		saveMatrix(createData());
	}

	//Đóng file
	HighScore.close();

	Matrix.close();

	CurrentScore.close();
	//Giải phóng các nút 

	for (int i = 0; i < TOTAL_BUTTON; i++) {
		freeButtons(gButton[i]);
	}

	//Giaỉ phóng dữ liệu và kết thúc chương trình 
	freeTexture(renderTexture);

	freeSoundEffects(gSFX);

	freeMusic(gMusicMenu);
	freeMusic(gMusicGamePlay);

	freeFont(gFont);

	freeWindowAndRenderer(window, renderer);

	quit();
}