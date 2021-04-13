#pragma once
#include <vector>
#include <string>
#include "../DataTypes/rgbaquad.h"
#include "../DataTypes/ImageType.h"

class IImageReader
{
protected:
	std::string name;
public:
	IImageReader(IImageReader& other) = delete;
	void operator=(const IImageReader&) = delete;

	IImageReader(const std::string& name);
	virtual std::vector< std::vector <RGBAquad> > read() = 0;
	static IImageReader* createImageReader(imageType sourceType, std::string name);
};

