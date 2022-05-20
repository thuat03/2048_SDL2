#pragma once

//Thông số của các nút 
const int BUTTON_WIDTH = 175;
const int BUTTON_HEIGHT = 50;

//
const int TOTAL_RECT = 52;
const int TOTAL_PICTURE = 13;
enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_TOTAL = 3
};

enum LButtonStatusRender {
	DEFAULT_STATUS = 0,
	TRIGGERED_STATUS = 1,
	TOTAL_STATUS_RENDER = 2
};

enum TheGameStatus {
	MAIN_MENU_STATUS = 0,
	GAME_PLAY_SINGLE_STATUS = 1,
	GAME_PLAY_MULTI_STATUS = 2,
	WIN_STATUS = 3,
	LOSE_STATUS = 4,
	PAUSE_STATUS = 5,
	EXIT_STATUS = 6,
	STARTUP_STATUS = 7,
	TOTAL_STATUS = 8
};

enum TheButton {
	START = 0,
	EXIT = 1,
	PLAY_AGAIN = 2,
	CONTINUE_MENU = 3,
	CONTINUE_GAMEPLAY = 4,
	SAVE_AND_EXIT = 5,
	SFX_ON = 6,
	SFX_OFF = 7,
	MUSIC_ON = 8,
	MUSIC_OFF = 9,
	MAIN_MENU = 10,
	SINGLE_PLAYER = 11,
	MULTIPLAYER = 12,
	MAIN_MENU_END_MULTI = 13,
	TOTAL_BUTTON = 14
};

enum Mode {
	SINGLE = 1,
	MULTI = 2
};

enum Players {
	PLAYER_1 = 1,
	PLAYER_2 = 2
};