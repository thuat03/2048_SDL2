#pragma once
class Settings {
public:
	bool music;
	bool sfx;
	Settings(bool _music = true, bool _sfx = true) {
		this->music = _music;
		this->sfx = _sfx;
	}
};