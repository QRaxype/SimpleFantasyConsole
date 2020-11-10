#include "Include.h"

#include "Global.h"

void print_version();
//Main Loop
int main(int argc, const char **argv){
	print_version();
	Global::G = new Global();
	Global *G = Global::G;
	G->argc = argc; G->argv = argv;
	init();
	sf::Clock C;
	while(G->work){
		update();
		G->delta_time = C.restart();
	}
	deinit();
	delete Global::G;
	return 0;
}

void test(){
	"";
}

void print_version(){
	char state[16] = {0};
	switch(_version.state){
		case 0:
			strcpy(state, "Dev");
			break;
		case 1:
			strcpy(state, "Alpha");
			break;
		case 2:
			strcpy(state, "Beta");
			break;
		case 3:
			strcpy(state, "Release");
			break;
		default:
			strcpy(state, "None");
			break;
	}
	/*printf("Version: (%u.%u.%u) [%u] {%s}\n\n", _version.ver.major, _version.ver.minor, _version.ver.macro,
		   _version.alt, state);*/
	printf("Version: %u.%u.%u-%u-%s\n\n", _version.ver.major, _version.ver.minor, _version.ver.macro,
		   _version.alt, state);
}
