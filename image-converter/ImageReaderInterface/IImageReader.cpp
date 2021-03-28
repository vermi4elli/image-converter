#include "IImageReader.h"
#include "../ImageReaderImplementations/PpmImageReader.h"
#include "../ImageReaderImplementations/BmpImageReader.h"
#include "../ImageReaderImplementations/png/PngImageReader.h"
#include "../ImageReaderImplementations/GifImageReader.h"

IImageReader::IImageReader(const std::string& name)
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
		return new GifImageReader(name);
		break;
	default:
		throw std::exception("[Error]: Unknown or unsupported source image type!");
		break;
	}
}
