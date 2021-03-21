#pragma once
#include "../ImageWriterInterface/IImageWriter.h"
#include "../DataTypes/BmpHeader.h";

class BmpImageWriter :
	public IImageWriter {
	void set16bit(uint16_t data, char buffer[]);
	void set32bit(uint32_t data, char buffer[]);
	uint32_t saveRGBAquad(const RGBAquad& pixel);
	bool print(const char* error);
public:
	void write(const char* name, std::vector< std::vector <RGBAquad> > data);
};