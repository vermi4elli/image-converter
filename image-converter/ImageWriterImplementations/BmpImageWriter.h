#pragma once
#include <vector>;
#include "rgbaquad.h";
#include "BmpHeader.h";
#include "IImageWriter.h";

class BmpImageWriter : public IImageWriter{
	void set16bit(uint16_t data, char buffer[]);
	void set32bit(uint32_t data, char buffer[]);
	uint32_t saveRGBAquad(const RGBAquad& pixel);
	void write(const char* name, std::vector< std::vector <RGBAquad> > data, BmpHeader head);
	bool print(const char* error);
public:
	void todo(const char* name, std::vector< std::vector <RGBAquad> > data);
};