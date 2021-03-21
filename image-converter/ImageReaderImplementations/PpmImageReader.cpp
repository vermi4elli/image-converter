#include "PpmImageReader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>

void PpmImageReader::makeRGBAquad(RGBAquad& res, uint32_t data)
{
    res.r = (data & 0xff0000) >> 16;
    res.g = (data & 0xff00) >> 8;
    res.b = (data & 0xff) >> 0;
    res.a = (data & 0xff000000) >> 24;
}

void PpmImageReader::printMatrix(const std::vector<std::vector<RGBAquad>>& res)
{
    int W = res.front().size(), H = res.size();
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            std::cout << " (" << static_cast<int>(res[i][j].r) << " " << static_cast<int>(res[i][j].g) << " " << static_cast<int>(res[i][j].b) << ")";
        }
        std::cout << std::endl;
    }
}

constexpr uint16_t PpmImageReader::get16bit(char buffer[])
{
    return
        static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
        static_cast<uint16_t>(static_cast<uint8_t>(buffer[1])) << 8;
}

std::vector<std::vector<RGBAquad>> PpmImageReader::read(const char* name)
{
    std::ifstream fin(name);
    if (!fin.is_open()) throw std::exception("Failed to open the given file!");

    // basic vars
    std::string header;
    int W, H, maxValue;
    RGBAquad rgba_temp;

    // reading file type header (P3 or P6)
    fin >> header;
    
    // getting rid of comments
    fin.get();
    while (fin.peek() == '#')
    {
        char ch;
        while (fin.get(ch))
        {
            if (ch == '\n')
            {
                break;
            }
        }
    }

    // reading the width, height, max color value
    fin >> W >> H >> maxValue;
     std::cout << header << " ; " << W << " ; " << H << " ; " << maxValue << std::endl;

    std::vector<std::vector<RGBAquad>> result(H, std::vector<RGBAquad>(W));
    if (header == "P3") {
        int t_r, t_g, t_b;

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                fin >> t_r >> t_g >> t_b;

                result[i][j].r = t_r;
                result[i][j].g = t_g;
                result[i][j].b = t_b;
                result[i][j].a = 255;
            }
        }
    }
    else if (header == "P6") {
        if (maxValue > 255) throw std::exception("PPM's binary version cannot have a maximum color-component value higher than 255!");
        uint8_t t_r, t_g, t_b;
        char* buffer = new char(2);

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                fin.read(buffer, 1);
                fin.read(buffer, 2);
                std::cout << get16bit(buffer) << std::endl;
                fin.read(buffer, 1);
                std::cout << get16bit(buffer) << std::endl;
                fin.read(buffer, 2);
                std::cout << get16bit(buffer) << std::endl;
                fin.read(buffer, 2);
                fin.read(buffer, 2);
                std::cout << get16bit(buffer) << std::endl;
                fin.read(buffer, 2);
                std::cout << get16bit(buffer) << std::endl;
                fin.read(buffer, 2);
                std::cout << get16bit(buffer) << std::endl;
                

                int a = 0;
                /*result[i][j].r = t_r;
                result[i][j].g = t_g;
                result[i][j].b = t_b;
                result[i][j].a = 255;*/

                //std::cout << i << " : " << j << " ->" << " (" << t_r << " " << t_g << " " << t_b << ")" << std::endl;
                //std::cout << i << " : " << j << " ->" << " (" << static_cast<int>(result[i][j].r) << " " << static_cast<int>(result[i][j].g) << " " << static_cast<int>(result[i][j].b) << ")" << std::endl;
            }
        }
    }

    std::cout << "Done parsing" << std::endl;
    printMatrix(result);
    return result;
}