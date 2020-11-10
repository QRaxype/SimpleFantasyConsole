#include "Global.h"
#include <fstream>
#include "CApi.h"
#include "lua_api.h"

using std::string;

Global *Global::G;
static Global *G = Global::G;


void init(){
	Global *G = Global::G;
	if(G->argc >= 2){
		std::ifstream fs;
		fs.open(G->argv[1], std::ios::in);
		if(!fs.is_open()){
			return;
		}
		string code;
		char tmp[1024 * MAX_CODE_KB] = {0};
		memset(tmp, 0, 1024 * MAX_CODE_KB);
		fs.seekg(0, std::ios::end);
		int size = fs.tellg();
		fs.seekg(0, std::ios::beg);
		fs.read(tmp, 1024 * MAX_CODE_KB > size ? size : 1024 * MAX_CODE_KB);
		fs.close();
		code = tmp;
		G->code = code;
	}
	else{
		return;
	}

	G->work = true;
	G->win.create(sf::VideoMode(DISPLAY_RESOLUTION[0] * PIXELS_IN_PIXEL, DISPLAY_RESOLUTION[1] * PIXELS_IN_PIXEL),
				  "SimpleFantasyConsole", 5);
	G->win.setFramerateLimit(120);
	G->screen.create(DISPLAY_RESOLUTION[0], DISPLAY_RESOLUTION[1]);
	G->win_texture.loadFromImage(G->screen);
	G->win_sprite.setTexture(G->win_texture);
	G->win_sprite.setScale(PIXELS_IN_PIXEL, PIXELS_IN_PIXEL);

	CApiInit();
	if(G->error){
		return;
	}

};
void update(){
	Global *G = Global::G;
	sf::Event e;
	while(G->win.pollEvent(e)){
		if(e.type == sf::Event::Closed){
			G->win.close();
			G->work = false;
		}
		if(e.type == sf::Event::KeyPressed){
			if(e.key.code == sf::Keyboard::Escape){
				G->win.close();
				G->work = false;
			}
		}
	}
	CApiUpdate();
	G->win_texture.loadFromImage(G->screen);
	//G->win_sprite.setTexture(G->win_texture);
	G->win.draw(G->win_sprite);
	G->win.display();
};
void deinit(){
	Global *G = Global::G;
};
