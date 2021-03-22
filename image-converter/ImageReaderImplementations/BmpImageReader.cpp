
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
<<<<<<< HEAD
#include "BmpImageReader.h"

=======
#include "BmpImageReader.h";
#include "BmpHeader.h";
#include "BmpImageWriter.h";
>>>>>>> bmpconverter
void BmpImageReader::makeRGBAquad(RGBAquad& res, uint32_t data)
{
    res.r = (data & 0xff0000) >> 16;
    res.g = (data & 0xff00) >> 8;
    res.b = (data & 0xff) >> 0;
    res.a = (data & 0xff000000) >> 24;
}
constexpr uint16_t BmpImageReader::get16bit(char buffer[])
{
    return
        static_cast<uint16_t>(static_cast<uint8_t>(buffer[0])) |
        static_cast<uint16_t>(static_cast<uint8_t>(buffer[1])) << 8;
}
constexpr uint32_t BmpImageReader::get32bit(char buffer[])
{
    return
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[0])) |
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[1])) << 8 |
<<<<<<< HEAD
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[2])) << 16 |
=======
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[2])) << 16| 
>>>>>>> bmpconverter
        static_cast<uint32_t>(static_cast<uint8_t>(buffer[3])) << 24;
}

bool BmpImageReader::print(const char* error) {
<<<<<<< HEAD
    std::cout << "[Error]: " << error << std::endl;
    exit(1);
}

std::vector< std::vector <RGBAquad> > BmpImageReader::read () {
=======
    std::cout << error << std::endl;
    exit(1);
}

std::vector< std::vector <RGBAquad> > BmpImageReader::read (const char* name) {
>>>>>>> bmpconverter
    BmpHeader header;

    std::ifstream fin(name, std::ios::binary);

    char buffer[4];

    // BITMAP HEADER

    // offset 0, size 2 - BM
    fin.read(buffer, 2) || print("Can't read file");
    (buffer[0] == 'B' && buffer[1] == 'M') || print("Not BMP");

    fin.read(buffer, 4) || print("Can't read file");
    header.filesize = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");

    fin.read(buffer, 4) || print("Can't read file");
    header.headersize = get32bit(buffer);
    
    // ***** DIB HEADER

    fin.read(buffer, 4) || print("Can't read file");
    header.biheadersize  = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");
    header.width = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");
    header.depth = get32bit(buffer);

    fin.read(buffer, 2) || print("Can't read file");
    header.biPlanes = get16bit(buffer);

    fin.read(buffer, 2) || print("Can't read file");
    header.bits = get16bit(buffer);
<<<<<<< HEAD
    if (header.bits != 32) print("Bits not 32");
=======
    if(header.bits!=32 && header.bits!=24) print("File not 24 or 32 bits.");

>>>>>>> bmpconverter

    fin.read(buffer, 4) || print("Can't read file");
    header.biCompression = get32bit(buffer);
    if (header.biCompression != 0) print("Compress is not 0");

    fin.read(buffer, 4) || print("Can't read file");
    header.biSizeImage = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");
    header.biXPelsPerMeter = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");
    header.biYPelsPerMeter = get32bit(buffer);
    
    fin.read(buffer, 4) || print("Can't read file");
    header.biClrUsed = get32bit(buffer);

    fin.read(buffer, 4) || print("Can't read file");
    header.biImClrUsed = get32bit(buffer);
    
    std::vector< std::vector <RGBAquad> > data(header.depth);

    auto currentOffset = 0;

    fin.seekg(0);

    while (currentOffset != header.headersize) {
        fin.read(buffer, 1) || print("Can't read file");
        currentOffset++;
    }

<<<<<<< HEAD

=======
    currentOffset = 0;
>>>>>>> bmpconverter

    for (auto& row : data) {
        row.resize(header.width);
        {
<<<<<<< HEAD
            auto nextOffset = (currentOffset * 4 + 3) / 4;
            while (nextOffset > currentOffset && currentOffset < header.filesize)
            {
                fin.read(buffer, 1) || print("Can't read file");
                ++currentOffset;
=======
            auto nextOffset = currentOffset  % 4;
            while (nextOffset > 0 && currentOffset < (header.filesize - header.headersize))
            {
                fin.read(buffer, 1) || print("Can't read file");
                ++currentOffset;
                nextOffset--;
>>>>>>> bmpconverter
            }
        }
        for (auto& pixel : row)
        {
            auto bytesToRead = (header.bits + 7) / 8;
            fin.read(buffer, bytesToRead) || print("Can't read file");
            makeRGBAquad(pixel, get32bit(buffer));
            currentOffset += bytesToRead;
        }

    }

    std::reverse(data.begin(), data.end());

<<<<<<< HEAD
    fin.close();

    std::cout << "[Debug]: Done reading" << std::endl;

=======
>>>>>>> bmpconverter
    return data;

}