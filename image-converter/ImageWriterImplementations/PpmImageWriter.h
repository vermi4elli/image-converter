#pragma once
#include "../ImageWriterInterface/IImageWriter.h"
#include <fstream>

class PpmImageWriter :
    public IImageWriter
{
public:
	PpmImageWriter(std::string name) : IImageWriter(name) {};
	void write(std::vector< std::vector <RGBAquad> > data);
};

