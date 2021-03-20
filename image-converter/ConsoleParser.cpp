#include "ConsoleParser.h"

ConsoleParser::ConsoleParser(std::string pathSource, std::string goalType, std::string pathOutput)
{
	pathSource_ = pathSource;
	
	if (pathOutput.empty()) {
		int lastDotIndex = pathSource.find_last_of('.');
		if (lastDotIndex != std::string::npos) pathOutput_ = pathSource.substr(0, lastDotIndex) + goalType;
		else throw std::exception("Enter a valid source image name!");
	}
	else pathOutput_ = pathOutput;

	if (goalType == "ppm") goalImageType_ = imageType::PPM;
	else if (goalType == "bpm") goalImageType_ = imageType::BPM;
	else if (goalType == "gif") goalImageType_ = imageType::GIF;
	else if (goalType == "png") goalImageType_ = imageType::PNG;
	else if (goalType == "jpeg") goalImageType_ = imageType::JPEG;
	else goalImageType_ = imageType::UNKNOWN;

	if (goalImageType_ == imageType::UNKNOWN) throw std::exception("Enter a valid goal image type!");
}

ConsoleParser* ConsoleParser::GetInstance(const int argc, char* argv[])
{
	if (argc > 1)
	{
		std::string pathSource, pathOutput, goalType;
		for (int i = 1; i < argc; i++)
		{
			std::string temp = argv[i];
			if (temp.find("--source") == 0) pathSource = temp.substr(9);
			if (temp.find("--goal") == 0) goalType = temp.substr(7);
			if (temp.find("--output") == 0) pathOutput = temp.substr(9);
		}

		if (pathSource.empty()) {
			throw std::exception("Enter a source image value!");
		}
		if (goalType.empty()) {
			throw std::exception("Enter a goal image type value!");
		}
		else {
			if (consoleParser_ == nullptr) {
				consoleParser_ = new ConsoleParser(pathSource, goalType, pathOutput);
			}
			return consoleParser_;
		}
	}
	throw std::exception("Enter a valid amount of arguments!");
}

ConsoleParser* ConsoleParser::consoleParser_ = nullptr;

std::string printImageType(imageType value) {
	std::string temp;
	switch (value)
	{
	case imageType::PPM:
		temp = "ppm";
		break;
	case imageType::BPM:
		temp = "bpm";
		break;
	case imageType::GIF:
		temp = "gif";
		break;
	case imageType::PNG:
		temp = "png";
		break;
	case imageType::JPEG:
		temp = "jpeg";
		break;
	case imageType::UNKNOWN:
		temp = "unknown type";
		break;
	default:
		break;
	};

	return temp;
}