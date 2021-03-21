#include "IImageReader.h"

IImageReader::IImageReader(const char* name)
{
	this->name = name;
}

IImageReader* IImageReader::createImageReader(imageType sourceType, const char* name)
{
	switch (sourceType)
	{
	case imageType::PPM:
		return new PpmImageReader(name);
		break;
	case imageType::BMP:
		return new BmpImageReader(name);
		break;
	case imageType::UNKNOWN:
		throw std::exception("Unknown or unsupported source image type!");
		break;
	default:
		throw std::exception("Unknown or unsupported source image type!");
		break;
	}
}
