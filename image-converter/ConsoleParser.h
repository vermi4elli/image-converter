#pragma once
#include <string>
#include <algorithm>
#include <iostream>

enum class imageType
{
	PPM,
	BPM,
	GIF,
	PNG,
	JPEG,
	UNKNOWN
};

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
	return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

std::string printImageType(imageType value);

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

};
