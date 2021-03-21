#pragma once
#include "ConsoleParser.h"
#include "ImageReaderImplementations/PpmImageReader.h"
#include "ImageWriterImplementations/PpmImageWriter.h"
#include "ImageReaderImplementations/BmpImageReader.h"
#include "ImageWriterImplementations/BmpImageWriter.h"
#include "ImageReaderImplementations/png/PngImageReader.h"

class ImageConverter
{
	ConsoleParser* consoleParser;
	IImageReader* imageReader;
	IImageWriter* imageWriter;
public:
	ImageConverter(int argc, char* argv[]);
	void convertImage();
};

