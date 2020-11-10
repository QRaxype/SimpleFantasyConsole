#include "lua_api.h"
#define LUAAPI_ERROR(x) luaApiExit(x); return;

static Global *G = Global::G;

static const luaL_Reg loadedlibs[] = {
  {LUA_GNAME, luaopen_base},
  //{LUA_LOADLIBNAME, luaopen_package},
  //{LUA_COLIBNAME, luaopen_coroutine},
  {LUA_TABLIBNAME, luaopen_table},
  //{LUA_IOLIBNAME, luaopen_io},
  //{LUA_OSLIBNAME, luaopen_os},
  {LUA_STRLIBNAME, luaopen_string},
  {LUA_MATHLIBNAME, luaopen_math},
  //{LUA_UTF8LIBNAME, luaopen_utf8},
  //{LUA_DBLIBNAME, luaopen_debug},
  {NULL, NULL}
};

void loadLuaStdLibs(lua_State *L){
	const luaL_Reg *lib;
	/* "require" functions from 'loadedlibs' and set results to global table */
	for(lib = loadedlibs; lib->func; lib++){
		luaL_requiref(L, lib->name, lib->func, 1);
		lua_pop(L, 1);  /* remove lib */
	}
}

int luaapi_exit(lua_State *lua){
	capi_exit(0);
	return 0;
}
int luaapi_print(lua_State *lua){
	if(lua_gettop(lua) >= 1){
		if(lua_isstring(lua, 1)){
			char str[1024];
			strcpy(str, lua_tostring(lua, 1));
			capi_print(0, str);
		}
	}
	return 0;
}
int luaapi_pix(lua_State *lua){
	if(lua_gettop(lua) >= 2){
		int x = lua_tointeger(lua, 1), y = lua_tointeger(lua, 2);
		if(lua_gettop(lua) >= 3){
			ui8 c = lua_tointeger(lua, 3);
			capi_pix(0, x, y, c);
			return 0;
		}
		else{
			ui8 ret = capi_pix(1, x, y, 0);
			lua_pushinteger(lua, ret);
			return 1;
		}
	}
	return 0;
}
int luaapi_cls(lua_State *lua){
	ui8 c = 0;
	if(lua_gettop(lua) >= 1){
		c = lua_tointeger(lua, 1);
	}
	capi_cls(0, c);
	return 0;
}
int luaapi_key(lua_State *lua){
	if(lua_gettop(lua) >= 1){
		short key = lua_tointeger(lua, 1);
		bool ret = capi_key(0, key);
		lua_pushboolean(lua, ret);
		return 1;
	}
	return 0;
}

void luaApiInit(){
	Global *G = Global::G;
	G->lua = luaL_newstate();
	loadLuaStdLibs(G->lua);
#define LUA_API_MACRO(name, ret, argc, ...) {#name, luaapi_##name},
	const struct{ const char *name; lua_CFunction func; } api[API_COUNT] = {API_LIST(LUA_API_MACRO)};
#undef LUA_API_MACRO
	for(size_t i = 0; i < API_COUNT; i++){
		lua_register(G->lua, api[i].name, api[i].func);
	}
	if(luaL_dostring(G->lua, G->code.c_str())){
		G->err_msg = lua_tostring(G->lua, -1);
		LUAAPI_ERROR(2);
		return;
	}
	if(lua_getglobal(G->lua, "Tick") == LUA_TFUNCTION && lua_getglobal(G->lua, "Init") == LUA_TFUNCTION){
		lua_pop(G->lua, 2);
	}
	else{
		lua_pop(G->lua, 2);
		LUAAPI_ERROR(2);
		return;
	}
	lua_getglobal(G->lua, "Init");
	int res = lua_pcall(G->lua, 0, 0, 0);
	if(res != LUA_OK){
		G->err_msg = lua_tolstring(G->lua, -1, nullptr);
		lua_pop(G->lua, 1);
		LUAAPI_ERROR(3);
	}
}

void luaApiUpdate(){
	Global *G = Global::G;
	lua_getglobal(G->lua, "Tick");
	lua_pushnumber(G->lua, G->delta_time.asSeconds());
	int res = lua_pcall(G->lua, 1, 0, 0);
	if(res != LUA_OK){
		G->err_msg = lua_tolstring(G->lua, -1, nullptr);
		lua_pop(G->lua, 1);
		LUAAPI_ERROR(3);
	}
}

void luaApiDeinit(){
	Global *G = Global::G;
	lua_close(G->lua);
}

void luaApiExit(byte reason){
	Global *G = Global::G;
	CApiExit(reason);
}

#undef LUAAPI_ERROR