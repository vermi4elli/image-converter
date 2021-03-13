#pragma once
#include <iostream>;
struct BmpHeader
{
    // BM letters
    uint32_t filesize;
    // Empty 4 bytes
    uint32_t headersize = 54;
    uint32_t biheadersize = 40;
    int32_t width;
    int32_t depth;
    uint16_t biPlanes = 0;
    uint16_t bits = 32;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = 0 ;
    uint32_t biXPelsPerMeter = 0 ;
    uint32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biImClrUsed = 0;
};