#pragma once
#include "../ImageWriterInterface/IImageWriter.h"
#include <vector>;
#include "../DataTypes/rgbaquad.h";
#include <fstream>

class PpmImageWriter :
    public IImageWriter
{
public:
	void write(const char* name, std::vector< std::vector <RGBAquad> > data);
};

