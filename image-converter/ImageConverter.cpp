#include "ImageConverter.h"

ImageConverter::ImageConverter(int argc, char* argv[])
{
	this->consoleParser = ConsoleParser::GetInstance(argc, argv);
	consoleParser->PrintInfo();

	this->imageReader = IImageReader::createImageReader(this->consoleParser->sourceImageType(), this->consoleParser->pathSource());
	this->imageWriter = IImageWriter::createImageWriter(this->consoleParser->goalImageType(), this->consoleParser->pathOutput());
}

void ImageConverter::convertImage()
{	
	auto result = imageReader->read();
	imageWriter->write(result);
}
