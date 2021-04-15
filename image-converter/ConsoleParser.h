#pragma once
#include <string>
#include <iostream>
#include "DataTypes/ImageType.h"

class ConsoleParser
{
private:
	std::string pathSource_, pathOutput_;
	imageType goalImageType_, sourceImageType_;

	ConsoleParser(std::string& pathSource, std::string& sourceType, std::string& goalType, std::string& pathOutput);

	static ConsoleParser* consoleParser_;

public:
    ConsoleParser(ConsoleParser& other) = delete;
    void operator=(const ConsoleParser&) = delete;
    
    static ConsoleParser* GetInstance(const int argc, char* argv[]);
    
	std::string pathSource() const {
        return pathSource_;
    }

	std::string pathOutput() const {
		return pathOutput_;
	}

	imageType goalImageType() const {
		return goalImageType_;
	}
	
	imageType sourceImageType() const {
		return sourceImageType_;
	}

	void PrintInfo() const;

};
