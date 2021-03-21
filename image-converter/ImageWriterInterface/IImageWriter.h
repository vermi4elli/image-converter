#pragma once
#include <vector>
#include "../DataTypes/rgbaquad.h"

class IImageWriter
{
public:
	virtual void write(const char* name, std::vector< std::vector <RGBAquad> > data) = 0;
};

