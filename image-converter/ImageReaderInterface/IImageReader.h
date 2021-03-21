#pragma once
#include <vector>
#include "../DataTypes/rgbaquad.h"
class IImageReader
{
public:
	virtual std::vector< std::vector <RGBAquad> > read(const char* name) = 0;
};

