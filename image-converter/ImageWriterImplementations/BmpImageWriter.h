#pragma once
#include <vector>;
#include "../DataTypes/BmpHeader.h";
#include "../DataTypes/rgbaquad.h";
#include "../IImageWriter.h";

class BmpImageWriter {
	void set16bit(uint16_t data, char buffer[]);
	void set32bit(uint32_t data, char buffer[]);
	uint32_t saveRGBAquad(const RGBAquad& pixel);
	void write(const char* name, std::vector< std::vector <RGBAquad> > data, BmpHeader head);
	bool print(const char* error);
public:
	void todo(const char* name, std::vector< std::vector <RGBAquad> > data);
};