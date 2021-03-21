#pragma once
#include <vector>
#include <string>
#include "../DataTypes/rgbaquad.h"
#include "../DataTypes/ImageType.h"

class IImageWriter
{
protected:
	std::string name;
public:
	IImageWriter(std::string name);
	virtual void write(std::vector< std::vector <RGBAquad> > data) = 0;
	static IImageWriter* createImageWriter(imageType goalType, std::string name);
};
