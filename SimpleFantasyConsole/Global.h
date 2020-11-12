#pragma once
#include "Include.h"

using std::string;

struct Global{
	static Global *G;
	bool work = false;
	unsigned int argc;
	const char **argv;
	sf::Time delta_time;
	byte error;
	string err_msg;

	sf::RenderWindow win;
	sf::Color palette[16] = {
		{0,0,0},{255,255,255},sf::Color::Red,sf::Color::Yellow,
		sf::Color::Green,sf::Color::Cyan,sf::Color::Blue,sf::Color::Magenta,
		{0,0,0},{0,0,0},{0,0,0},{0,0,0},
		{0,0,0},{0,0,0},{0,0,0},{0,0,0}
	};
	sf::Texture win_texture; sf::Sprite win_sprite;
	sf::Image screen;
	sf::SoundBuffer sound_buffer;

	lua_State *lua;

	string code;
	ui32 clockoffset;

	Global(){};
	//Global(const Global &){};
};

void init();
void update();
void deinit();