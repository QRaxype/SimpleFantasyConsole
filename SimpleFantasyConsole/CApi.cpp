#include "CApi.h"
#include "lua_api.h"

static Global *G = Global::G;

void CApiInit(){
	Global *G = Global::G;
	G->clockoffset = clock();
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
ui32 capi_pal(byte _override, ui8 idx, ui32 color){
	Global *G = Global::G;
	if(_override == 1){
		return G->palette[idx%PALETTE_SIZE].toInteger();
	}
	if(idx < PALETTE_SIZE){
		G->palette[idx] = sf::Color(color);
	}
	return 0;
}
void capi_sfx(byte _override, ui8 s){
	Global *G = Global::G;
	//G->sound_buffer.loadFromSamples()
}
ui32 capi_clock(byte _override){
	Global *G = Global::G;
	return clock() - G->clockoffset;
}
void capi__spr(byte _override){

}
void capi__test(byte _override){

}

