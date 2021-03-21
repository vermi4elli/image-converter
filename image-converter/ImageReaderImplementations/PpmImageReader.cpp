#include "PpmImageReader.h"
#include <fstream>
#include <sstream>
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

constexpr uint32_t PpmImageReader::get32bit(char buffer[])
{
    return
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[0])) |
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[1])) << 8 |
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[2])) << 16 |
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[3])) << 24;
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
    if (header == "P3")
    {
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
    else if (header == "P6")
    {
        if (maxValue > 255) throw std::exception("PPM's binary version cannot have a maximum color-component value higher than 255!");
        uint8_t t_r, t_g, t_b;
        char ch;
        char* buffer = new char(4);
        RGBAquad pixel;
        //fin.get();
        
        if (fin.peek() == '\n') {
            fin.get(ch);
        }

        //std::vector<uint8_t> data((std::istreambuf_iterator<char>(fin.rdbuf())), std::istreambuf_iterator<char>());

        std::ostringstream os;
        os << fin.rdbuf();
        const std::string& str = os.str();

        std::vector<uint8_t> data;

        data.insert(data.end(), str.begin(), str.end());


        int index = -1;
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                ++index;
                result[i][j].r = data[index];
                ++index;
                result[i][j].g = data[index];
                ++index;
                result[i][j].b = data[index];
            }
        }
    }
    result[0][0].a = maxValue;

    std::cout << "Done parsing" << std::endl;

    //printMatrix(result);
    return result;
}


/*fin.read(buffer, 2);
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
                std::cout << get16bit(buffer) << std::endl;*/

                /*result[i][j].r = t_r;
                result[i][j].g = t_g;
                result[i][j].b = t_b;
                result[i][j].a = 255;*/

                //std::cout << i << " : " << j << " ->" << " (" << t_r << " " << t_g << " " << t_b << ")" << std::endl;
                //std::cout << i << " : " << j << " ->" << " (" << static_cast<int>(result[i][j].r) << " " << static_cast<int>(result[i][j].g) << " " << static_cast<int>(result[i][j].b) << ")" << std::endl;



/*if (fin.peek() == '\n') {
                    fin.get(ch);
                }
                fin.read(buffer, 4);

                makeRGBAquad(pixel, get32bit(buffer));
                result[i][j] = pixel;*/

