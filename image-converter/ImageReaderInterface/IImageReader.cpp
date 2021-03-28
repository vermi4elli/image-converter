#include "IImageReader.h"
#include "../ImageReaderImplementations/PpmImageReader.h"
#include "../ImageReaderImplementations/BmpImageReader.h"
#include "../ImageReaderImplementations/png/PngImageReader.h"
#include "../ImageReaderImplementations/png/GifImageReader.h"

IImageReader::IImageReader(std::string name)
{
	this->name = name;
}

IImageReader* IImageReader::createImageReader(imageType sourceType, std::string name)
{
	switch (sourceType)
	{
	case imageType::PPM:
		return new PpmImageReader(name);
		break;
	case imageType::BMP:
		return new BmpImageReader(name);
		break;
	case imageType::PNG:
		return new PngImageReader(name);
		break;
	case imageType::GIF:
		return new PngImageReader(name);
		break;
	default:
		throw std::exception("[Error]: Unknown or unsupported source image type!");
		break;
	}
}
