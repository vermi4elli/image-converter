#pragma once
#include "../DataTypes/rgbaquad.h";
#include "../ImageReaderInterface/IImageReader.h";
#include <fstream>
class PpmImageReader :
    public IImageReader
{
    void printMatrix(const std::vector<std::vector<RGBAquad>>& res);
public:
    PpmImageReader(const char* name) : IImageReader(name) {};
    std::vector< std::vector <RGBAquad> > read();
};
