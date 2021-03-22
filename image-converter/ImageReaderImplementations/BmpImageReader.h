#pragma once
<<<<<<< HEAD
#include "../DataTypes/rgbaquad.h"
#include "../DataTypes/BmpHeader.h"
#include "../ImageReaderInterface/IImageReader.h"

class BmpImageReader :
	public IImageReader {
=======
#include "rgbaquad.h";
#include "IImageReader.h";
class BmpImageReader :
	public IImageReader {
    
>>>>>>> bmpconverter
	constexpr uint32_t get32bit(char buffer[]);
	constexpr uint16_t get16bit(char buffer[]);
	bool print(const char* error);
	void makeRGBAquad(RGBAquad& res, uint32_t data);
<<<<<<< HEAD
public:
	BmpImageReader(std::string name) : IImageReader(name) {};
	std::vector< std::vector <RGBAquad> > read();
=======

public:
	std::vector< std::vector <RGBAquad> > read(const char* name);

>>>>>>> bmpconverter
};