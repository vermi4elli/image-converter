#pragma once
#include "../DataTypes/rgbaquad.h";
#include "../ImageReaderInterface/IImageReader.h";
#include <fstream>
class PpmImageReader :
    public IImageReader
{
    constexpr uint16_t get16bit(char buffer[]);
    constexpr uint32_t get32bit(char buffer[]);
    void makeRGBAquad(RGBAquad& res, uint32_t data);
    void printMatrix(const std::vector<std::vector<RGBAquad>>& res);
public:
    std::vector< std::vector <RGBAquad> > read(const char* name);
};