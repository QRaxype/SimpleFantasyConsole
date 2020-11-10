#pragma once
#include "lua.hpp"
#include "CApi.h"

void loadLuaStdLibs(lua_State *L);

void luaApiInit();
void luaApiUpdate();
void luaApiDeinit();
void luaApiExit(byte reason);