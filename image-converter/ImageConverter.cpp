#include "ImageConverter.h"

ImageConverter::ImageConverter(int argc, char* argv[])
{
	this->consoleParser = ConsoleParser::GetInstance(argc, argv);
	consoleParser->PrintInfo();

	this->imageReader = IImageReader::createImageReader(this->consoleParser->sourceImageType(), this->consoleParser->pathSource().c_str());
	this->imageWriter = IImageReader::createImageReader(this->consoleParser->sourceImageType(), this->consoleParser->pathSource().c_str());
}

void ImageConverter::convertImage()
{	
	auto result = imageReader->read();

}
