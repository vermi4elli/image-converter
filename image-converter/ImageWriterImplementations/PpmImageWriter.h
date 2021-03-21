#pragma once
#include "../ImageWriterInterface/IImageWriter.h"
#include <fstream>

class PpmImageWriter :
    public IImageWriter
{
public:
	void write(std::vector< std::vector <RGBAquad> > data);
};

