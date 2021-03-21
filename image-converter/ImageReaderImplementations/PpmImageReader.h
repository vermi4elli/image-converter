#pragma once
#include "../DataTypes/rgbaquad.h";
#include "../ImageReaderInterface/IImageReader.h";
class PpmImageReader :
    public IImageReader
{
    void makeRGBAquad(RGBAquad& res, uint32_t data);
    void printMatrix(const std::vector<std::vector<RGBAquad>>& res);
public:
    std::vector< std::vector <RGBAquad> > read(const char* name);
};