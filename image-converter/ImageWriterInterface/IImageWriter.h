#pragma once
#include <vector>
#include "../DataTypes/rgbaquad.h"

class IImageWriter
{
protected:
	const char* name;
public:
	IImageWriter(const char* name);
	virtual void write(std::vector< std::vector <RGBAquad> > data) = 0;
};

