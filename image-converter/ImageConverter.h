#pragma once
#include <memory>
#include "ConsoleParser.h"
#include "ImageReaderImplementations/PpmImageReader.h"
#include "ImageWriterImplementations/PpmImageWriter.h"
#include "ImageReaderImplementations/BmpImageReader.h"
#include "ImageWriterImplementations/BmpImageWriter.h"
#include "ImageReaderImplementations/png/PngImageReader.h"

class ImageConverter
{
	std::unique_ptr<ConsoleParser> consoleParser;
	std::unique_ptr<IImageReader> imageReader;
	std::unique_ptr<IImageWriter> imageWriter;
public:
	ImageConverter(int argc, char* argv[]);
	void convertImage();
};

