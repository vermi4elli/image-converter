#pragma once
#include "ConsoleParser.h"
#include "ImageReaderImplementations/PpmImageReader.h"
#include "ImageWriterImplementations/PpmImageWriter.h"
#include "ImageReaderImplementations/BmpImageReader.h"
#include "ImageWriterImplementations/BmpImageWriter.h"
#include "ImageReaderImplementations/GifImageReader.h"
//#include "ImageWriterImplementations/GifImageWriter.h"
//#include "ImageReaderImplementations/PngImageReader.h"
//#include "ImageWriterImplementations/PngImageWriter.h"

class ImageConverter
{
	ConsoleParser* consoleParser;
	IImageReader* imageReader;
	IImageWriter* imageWriter;
public:
	ImageConverter(int argc, char* argv[]);
	void convertImage();
};

