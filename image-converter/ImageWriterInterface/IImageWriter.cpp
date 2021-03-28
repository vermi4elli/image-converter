#include "IImageWriter.h"
#include "../ImageWriterImplementations/BmpImageWriter.h"
#include "../ImageWriterImplementations/PpmImageWriter.h"
#include "../ImageWriterImplementations/PngImageWriter.h"

IImageWriter::IImageWriter(const std::string& name)
{
	this->name = name;
}

IImageWriter* IImageWriter::createImageWriter(imageType goalType, const std::string& name)
{
	switch (goalType)
	{
	case imageType::PPM:
		return new PpmImageWriter(name);
		break;
	case imageType::BMP:
		return new BmpImageWriter(name);
		break;
	case imageType::PNG:
		return new PngImageWriter(name);
		break;
	default:
		throw std::exception("[Error]: Unknown or unsupported goal image type!");
		break;
	}
}
