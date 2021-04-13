#include "ImageConverter.h"

ImageConverter::ImageConverter(int argc, char* argv[])
{
	consoleParser.reset(std::move(ConsoleParser::GetInstance(argc, argv)));
	consoleParser->PrintInfo();

	imageReader.reset(IImageReader::createImageReader(this->consoleParser->sourceImageType(), this->consoleParser->pathSource()));
	imageWriter.reset(IImageWriter::createImageWriter(this->consoleParser->goalImageType(), this->consoleParser->pathOutput()));
}

void ImageConverter::convertImage()
{	
	auto result = imageReader->read();
	imageWriter->write(result);
}
