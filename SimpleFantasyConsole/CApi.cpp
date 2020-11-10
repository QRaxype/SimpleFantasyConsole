#include "CApi.h"
#include "lua_api.h"

static Global *G = Global::G;

void CApiInit(){
	Global *G = Global::G;
	luaApiInit();
	if(G->error){
		return;
	}

}

void CApiUpdate(){
	Global *G = Global::G;
	luaApiUpdate();
}

void CApiDeinit(){
	Global *G = Global::G;
	luaApiDeinit();
}

void CApiExit(byte reason){
	Global *G = Global::G;
	G->work = false;
	printf("Exit reason: %u\n", reason);
	if(!G->err_msg.empty()){
		printf("Add. error message: %s", G->err_msg.c_str());
	}
	//CApiDeinit();
	G->error = reason;
}

void capi_exit(byte _override){
	Global *G = Global::G;
	G->work = false;
	return;
}
void capi_print(byte _override, const char *str){
	printf(str);
	putchar('\n');
	return;
}
ui8 capi_pix(byte _override, int x, int y, ui8 c){
	Global *G = Global::G;
	if(x >= 0 && x <= DISPLAY_RESOLUTION[0]-1 && y >= 0 && y <= DISPLAY_RESOLUTION[1]-1){
		if(_override == 1){
			sf::Color col = G->screen.getPixel(x, y);
			for(size_t i = 0; i < 16; i++){
				if(col == G->palette[i]){
					return i;
				}
			}
			return 0;
		}
		else{
			G->screen.setPixel(x, y, G->palette[c % 16]);
		}
	}
	return (ui8)0;
}
void capi_cls(byte _override, ui8 c){
	Global *G = Global::G;
	for(size_t i = 0; i < DISPLAY_RESOLUTION[0]; i++){
		for(size_t j = 0; j < DISPLAY_RESOLUTION[1]; j++){
			G->screen.setPixel(i, j, G->palette[c%16]);
		}
	}
	return;
}
bool capi_key(byte _override, short key){
	bool b = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
	return b;
}
