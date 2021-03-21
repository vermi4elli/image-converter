#pragma once
#include "../DataTypes/rgbaquad.h";
#include "../ImageReaderInterface/IImageReader.h";
class BmpImageReader :
	public IImageReader {
    
	constexpr uint32_t get32bit(char buffer[]);
	constexpr uint16_t get16bit(char buffer[]);
	bool print(const char* error);
	void makeRGBAquad(RGBAquad& res, uint32_t data);

public:
	std::vector< std::vector <RGBAquad> > read(const char* name);

};