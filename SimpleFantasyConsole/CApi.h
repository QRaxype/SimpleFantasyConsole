#pragma once
#include "Include.h"
#include "Global.h"

//API list generator
//macro(name, ret arg, argc, byte func overide, args...)
static const int ___API_LIST_LINE_START = __LINE__ + 2;
#define API_LIST(macro) \
macro(exit, void, 0) \
macro(print, void, 1, const char *text) \
macro(pix, ui8, 3, int x, int y, ui8) \
macro(cls, void, 1, ui8) \
macro(key, bool, 1, short int key) \
macro(pal, ui32, 2, ui8 idx, ui32 c)

static const int ___API_LIST_LINE_END = __LINE__ - 2;
const unsigned int API_COUNT = ___API_LIST_LINE_END - ___API_LIST_LINE_START + 1;


#define MAKE_CAPI(name, ret, argc, ...) \
ret capi_##name(byte _override, __VA_ARGS__);
API_LIST(MAKE_CAPI)
#undef MAKE_CAPI

void CApiInit();
void CApiUpdate();
void CApiDeinit();
void CApiExit(byte reason);