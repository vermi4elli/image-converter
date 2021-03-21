#include "IImageWriter.h"
#include "../ImageWriterImplementations/BmpImageWriter.h"
#include "../ImageWriterImplementations/PpmImageWriter.h"

IImageWriter::IImageWriter(std::string name)
{
	this->name = name;
}

IImageWriter* IImageWriter::createImageWriter(imageType goalType, std::string name)
{
	switch (goalType)
	{
	case imageType::PPM:
		return new PpmImageWriter(name);
		break;
	case imageType::BMP:
		return new BmpImageWriter(name);
		break;
	default:
		throw std::exception("Unknown or unsupported goal image type!");
		break;
	}
}
