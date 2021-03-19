#include "ConsoleParser.h"

ConsoleParser::ConsoleParser(std::string pathSource, std::string goalType, std::string pathOutput)
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
			throw exception("Enter a source image value!");
		}
		if (goalType.empty()) {
			throw exception("Enter a goal image type value!");
		}
		else {
			if (consoleParser_ == nullptr) {
				consoleParser_ = new ConsoleParser(pathSource, goalType, pathOutput);
			}
			return consoleParser_;
		}
	}
	throw exception("Enter a valid amount of arguments!");
}

ConsoleParser* ConsoleParser::consoleParser_ = nullptr;