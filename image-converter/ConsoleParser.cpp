#include "ConsoleParser.h"

ConsoleParser::ConsoleParser(std::string pathSource, std::string sourceType, std::string goalType, std::string pathOutput)
{
	pathSource_ = pathSource;
	
	if (pathOutput.empty()) {
		int lastDotIndex = pathSource.find_last_of('.');
		if (lastDotIndex != std::string::npos) pathOutput_ = pathSource.substr(0, lastDotIndex) + '.' + goalType;
		else throw std::exception("[Error]: Enter a valid source image name!");
	}
	else pathOutput_ = pathOutput;

	if (goalType == "ppm") goalImageType_ = imageType::PPM;
	else if (goalType == "bmp") goalImageType_ = imageType::BMP;
	else goalImageType_ = imageType::UNKNOWN;
	if (goalImageType_ == imageType::UNKNOWN) throw std::exception("[Error]: Enter a supported goal image type!");
	
	if (sourceType == "ppm") sourceImageType_ = imageType::PPM;
	else if (sourceType == "bmp") sourceImageType_ = imageType::BMP;
	else if (sourceType == "png") sourceImageType_ = imageType::PNG;
	else sourceImageType_ = imageType::UNKNOWN;
	if (sourceImageType_ == imageType::UNKNOWN) throw std::exception("[Error]: Enter a supported source image type!");
}

ConsoleParser* ConsoleParser::GetInstance(const int argc, char* argv[])
{
	if (argc > 1)
	{
		std::string pathSource, pathOutput, goalType;
		for (int i = 1; i < argc; i++)
		{
			std::string temp = argv[i];
			if (temp.find("--source") == 0) pathSource = ".\\" + temp.substr(9);
			if (temp.find("--goal-format") == 0) goalType = temp.substr(14);
			if (temp.find("--output") == 0) pathOutput = ".\\" + temp.substr(9);
		}

		if (pathSource.empty()) {
			throw std::exception("[Error]: Enter a source image value!");
		}
		else {
			std::string sourceType = pathSource.substr(pathSource.find_last_of('.') + 1);

			if (consoleParser_ == nullptr) {
				consoleParser_ = new ConsoleParser(pathSource, sourceType, goalType, pathOutput);
			}
			return consoleParser_;
		}
	}
	throw std::exception("[Error]: Enter a valid amount of arguments!");
}

void ConsoleParser::PrintInfo() const
{
	std::cout << "Source path: " << pathSource() <<
		//";\nGoal Image Type: " << printImageType(goalImageType()) <<
		";\nOutput path: " << pathOutput() << std::endl;
}

ConsoleParser* ConsoleParser::consoleParser_ = nullptr;
