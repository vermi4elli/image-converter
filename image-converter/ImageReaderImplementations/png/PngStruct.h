#pragma once
#include <iostream>
#include <vector>
struct PngStruct
{
    uint32_t width;
    uint32_t height;
    uint8_t bit_depth;
    uint8_t color_type;
    uint8_t compression_method;
    uint8_t filter_method;
    uint8_t interlace_method;

    bool alpha = false;

    std::vector<char*> chunks_name;
    std::vector<int> chunks_length;

    uint32_t gAMA;
    std::string color_space;

    uint32_t White_Point_x;
    uint32_t White_Point_y;
    uint32_t Red_x;
    uint32_t Red_y;
    uint32_t Green_x;
    uint32_t Green_y;
    uint32_t Blue_x;
    uint32_t Blue_y;
};