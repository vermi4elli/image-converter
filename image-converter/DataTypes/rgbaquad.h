#pragma once
#include <iostream>

struct RGBAquad
{
	uint8_t r, g, b, a;
	RGBAquad() : r(0), g(0), b(0), a(0) {};
	RGBAquad(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0) : r(r), g(g), b(b), a(a) {};
};