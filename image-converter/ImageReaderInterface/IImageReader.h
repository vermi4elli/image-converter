#pragma once
#include <vector>
#include "../DataTypes/rgbaquad.h"
#include "../DataTypes/ImageType.h"
#include "../ImageReaderImplementations/PpmImageReader.h"
#include "../ImageReaderImplementations/BmpImageReader.h"
#include "../ImageReaderImplementations/GifImageReader.h"

class IImageReader
{
protected:
	const char* name;
public:
	IImageReader(const char* name);
	virtual std::vector< std::vector <RGBAquad> > read() = 0;
	static IImageReader* createImageReader(imageType sourceType, const char* name);
};

