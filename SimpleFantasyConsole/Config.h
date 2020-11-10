#pragma once

struct{
	struct{
		unsigned int major = 0, minor = 1, macro = 0;
	} ver;
	unsigned int alt = 1;
	enum{
		Dev,
		Alpha,
		Beta,
		Release
	}state = Dev;
	//unsigned int build = __COUNTER__;
} static _version;


//Console

const unsigned short int DISPLAY_RESOLUTION[2] = {240, 136};
//console pixel scale factory by compute pixel
const unsigned short int PIXELS_IN_PIXEL = 2;
const unsigned int MAX_CODE_KB = 8;
/*const unsigned short int PALETTE_SIZE = 16;*/

//Script

const unsigned short int MAX_STRINGLEN_IN_PRINT = 1024;

//Lua

