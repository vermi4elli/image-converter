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
    for (int j = 0; j < H; j++)
    {
        for (int i = 0; i < W; i++)
        {
            std::cout << " (" << res[i][j].r << " " << res[i][j].g << " " << res[i][j].b << ")";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<RGBAquad>> PpmImageReader::read(const char* name)
{
    std::ifstream fin(name);
    if (!fin.is_open()) throw std::exception("Failed to open the given file!");

    std::string header;
    int W, H, maxValue;
    RGBAquad rgba_temp;
    char buffer[70];

    fin >> header >> W >> H >> maxValue;
    std::cout << header << " ; " << W << " ; " << H << " ; " << maxValue << std::endl;

    std::vector<std::vector<RGBAquad>> result(W, std::vector<RGBAquad>(H));
    if (header == "P3") {
        int t_r, t_g, t_b;

        for (int j = 0; j < H; j++)
        {
            for (int i = 0; i < W; i++)
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

        for (int j = 0; j < H; j++)
        {
            for (int i = 0; i < W; i++)
            {
                fin >> t_r >> t_g >> t_b;

                result[i][j].r = t_r;
                result[i][j].g = t_g;
                result[i][j].b = t_b;
                result[i][j].a = 255;
            }
        }
    }

    printMatrix(result);
    return result;
}