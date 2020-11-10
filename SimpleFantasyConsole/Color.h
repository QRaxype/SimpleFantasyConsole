#pragma once
struct Color{
	unsigned __int8 r = 0, g = 0, b = 0;
	Color(){};
	Color(__int8 _r, __int8 _g, __int8 _b) : r(_r), g(_g), b(_b) {};
};