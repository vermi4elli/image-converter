#pragma once
#include <vector>
#include "../DataTypes/rgbaquad.h"
class IImageReader
{
	virtual void makeRGBAquad(RGBAquad& res, uint32_t data) = 0;
public:
	virtual std::vector< std::vector <RGBAquad> > read(const char* name) = 0;
};

