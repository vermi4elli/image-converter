#include "ConsoleParser.h"

ConsoleParser::ConsoleParser(std::string& pathSource, std::string& sourceType, std::string& goalType, std::string& pathOutput, std::string& side)
{
	pathSource_ = pathSource;
	
	if (pathOutput.empty()) {
		int lastDotIndex = pathSource.find_last_of('.');
		if (lastDotIndex != std::string::npos) pathOutput_ = pathSource.substr(0, lastDotIndex) + '.' + goalType;
		else throw std::exception("[Error]: Enter a valid source image name!");
	}
	else pathOutput_ = pathOutput;

	if (goalType.empty())
	{
		int lastDotIndex = pathOutput.find_last_of('.');
		if (lastDotIndex != std::string::npos && lastDotIndex != pathOutput.length() - 1) goalType = pathOutput.substr(lastDotIndex + 1);
		else throw std::exception("[Error]: Enter a valid goal image type!");
	}

	if (side == "front") modelSide_ = modelSide::FRONT;
	else if (side == "left") modelSide_ = modelSide::LEFT;
	else if (side == "right") modelSide_ = modelSide::RIGHT;
	else if (side == "back") modelSide_ = modelSide::BACK;
	else
	{
		modelSide_ = modelSide::FRONT;
		std::cout << "[Debug]: No model side parameter found. Setting default value: FRONT!" << std::endl;
	}
	
	if (goalType == "ppm") goalImageType_ = imageType::PPM;
	else if (goalType == "bmp") goalImageType_ = imageType::BMP;
	else if (goalType == "png") goalImageType_ = imageType::PNG;
	else throw std::exception(std::string("[Error]: Enter a supported goal image type instead of " + goalType + "!").c_str());
	
	if (sourceType == "ppm") sourceImageType_ = imageType::PPM;
	else if (sourceType == "bmp") sourceImageType_ = imageType::BMP;
	else if (sourceType == "png") sourceImageType_ = imageType::PNG;
	else if (sourceType == "gif") sourceImageType_ = imageType::GIF;
	else if (sourceType == "obj") sourceImageType_ = imageType::OBJ;
	else throw std::exception(std::string("[Error]: Enter a supported source image type instead of " + sourceType + "!").c_str());
}

ConsoleParser* ConsoleParser::GetInstance(const int argc, char* argv[])
{
	if (argc > 1)
	{
		std::string pathSource, pathOutput, goalType, side;
		for (int i = 1; i < argc; i++)
		{
			std::string temp = argv[i];
			if (temp.find("--source") == 0) pathSource = ".\\" + temp.substr(9);
			if (temp.find("--goal-format") == 0) goalType = temp.substr(14);
			if (temp.find("--output") == 0) pathOutput = ".\\" + temp.substr(9);
			if (temp.find("--side") == 0) side = temp.substr(7);
		}

		if (pathSource.empty()) {
			throw std::exception("[Error]: Enter a valid source value!");
		}
		else {
			std::string sourceType = pathSource.substr(pathSource.find_last_of('.') + 1);

			if (consoleParser_ == nullptr) {
				consoleParser_ = new ConsoleParser(pathSource, sourceType, goalType, pathOutput, side);
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
