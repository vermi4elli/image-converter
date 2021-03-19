#pragma once
#include <string>

enum class imageType
{
	PPM,
	BPM,
	GIF,
	PNG,
	JPEG,
	UNKNOWN
};

class ConsoleParser
{
protected:
	std::string pathSource_, pathOutput_;
	imageType goalImageType_;

	ConsoleParser(std::string pathSource, std::string pathOutput, std::string goalType);

	static ConsoleParser* consoleParser_;

public:
    ConsoleParser(ConsoleParser& other) = delete;
    void operator=(const ConsoleParser&) = delete;
    
    static ConsoleParser* GetInstance(const std::string& value);
    
	std::string pathSource() const {
        return pathSource_;
    }


	std::string pathOutput() const {
		return pathOutput_;
	}

	imageType goalImageType() const {
		return goalImageType_;
	}

};
