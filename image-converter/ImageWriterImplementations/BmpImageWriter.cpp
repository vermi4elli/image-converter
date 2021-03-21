#include "BmpImageWriter.h";
#include <fstream>;
#include <iostream>;
#include <iomanip>;
#include <algorithm>;
#include <vector>;
#include "../DataTypes/BmpHeader.h";

bool BmpImageWriter::print(const char* error) {
    std::cout << error << std::endl;
    exit(1);
}

void BmpImageWriter::set16bit(uint16_t data, char buffer[]){
        buffer[0] = static_cast<char>(data);
        buffer[1] = static_cast<char>(data >> 8);
}

void BmpImageWriter::set32bit(uint32_t data, char buffer[]){
        buffer[0] = static_cast<char>(data);
        buffer[1] = static_cast<char>(data >> 8);
        buffer[2] = static_cast<char>(data >> 16);
        buffer[3] = static_cast<char>(data >> 24);
}

uint32_t BmpImageWriter::saveRGBAquad(const RGBAquad& pixel)
{
    return
        (static_cast<uint32_t>(pixel.r) << 16) |
        (static_cast<uint32_t>(pixel.g) << 8) |
        (static_cast<uint32_t>(pixel.b) << 0) |
        (static_cast<uint32_t>(pixel.a) << 24);
}

void BmpImageWriter::write(std::vector< std::vector <RGBAquad> > data) {

    BmpHeader head;
    head.width = data[0].size();
    head.depth = data.size();

    head.filesize = data[0].size() * data.size() * 4 + 54;


    char buffer[4];

    std::ofstream fout(name, std::ios::binary);

    // ***** HEADER
    buffer[0] = 'B'; buffer[1] = 'M';
    fout.write(buffer, 2) || print("Can't write");

    set32bit(head.filesize, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(0, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.headersize, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biheadersize, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.width, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.depth, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set16bit(head.biPlanes, buffer);
    fout.write(buffer, 2) || print("Can't write");

    set16bit(head.bits, buffer);
    fout.write(buffer, 2) || print("Can't write");

    set32bit(head.biCompression, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biSizeImage, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biXPelsPerMeter, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biYPelsPerMeter, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biClrUsed, buffer);
    fout.write(buffer, 4) || print("Can't write");

    set32bit(head.biImClrUsed, buffer);
    fout.write(buffer, 4) || print("Can't write");

    auto currentWriteOffset = head.headersize;
    for (auto& row : data)
    {
        {
            auto nextOffset = (currentWriteOffset * 4 + 3) / 4;
            while (nextOffset > currentWriteOffset && currentWriteOffset < head.filesize)
            {
                fout.write(0, 1) || print("Can't write");
                ++currentWriteOffset;
            }
        }
        for (auto& pixel : row)
        {
            auto bytesToWrite = (head.bits + 7) / 8;
            uint32_t bytes = saveRGBAquad(pixel);
            set32bit(bytes, buffer);
            fout.write(buffer, bytesToWrite) || print("Can't write");
            currentWriteOffset += bytesToWrite;
        }
    }

    fout.close();

}
