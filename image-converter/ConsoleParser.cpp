#include "ConsoleParser.h"

ConsoleParser::ConsoleParser(std::string pathSource, std::string pathOutput, std::string goalType)
{
	pathSource_ = pathSource;
	pathOutput_ = pathOutput;

	if (goalType == "ppm") goalImageType_ = imageType::PPM;
	else if (goalType == "bpm") goalImageType_ = imageType::BPM;
	else if (goalType == "gif") goalImageType_ = imageType::GIF;
	else if (goalType == "png") goalImageType_ = imageType::PNG;
	else if (goalType == "jpeg") goalImageType_ = imageType::JPEG;
	else goalImageType_ = imageType::UNKNOWN;
}

ConsoleParser* ConsoleParser::GetInstance(const std::string& value)
{
	
}
