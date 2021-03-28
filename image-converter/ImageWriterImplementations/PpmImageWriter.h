#pragma once
#include "../ImageWriterInterface/IImageWriter.h"
#include <fstream>

class PpmImageWriter :
    public IImageWriter
{
public:
	PpmImageWriter(const std::string& name) : IImageWriter(name) {};
	void write(const std::vector< std::vector <RGBAquad> >& data);
};

