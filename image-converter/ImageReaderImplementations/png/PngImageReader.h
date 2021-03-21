#include "PngStruct.h"
#include "../../DataTypes/rgbaquad.h"
#include <vector>

#pragma once
class PngImageReader {
	constexpr uint32_t get32bit(char bits[]);
	constexpr uint32_t get32bitrev(char bits[]);
	uint32_t Crc32(char* stream, int offset, int length, uint32_t crc);
	void gAMA_chunk(std::ifstream& fin, PngStruct png, char* buffer);
	void bKGD_chunk(std::ifstream& fin);
	void IDAT_chunk(std::ifstream& fin, int len, std::vector<std::vector<char> >& data);
	std::vector<std::vector<RGBAquad> >  buildpixelmatrix(std::vector<std::vector<uint8_t> >& bytes_matrix, PngStruct png);
	void filterdata(boost::iostreams::filtering_streambuf<boost::iostreams::input>& decompressed,
		std::vector<std::vector<uint8_t> >& bytes_matrix,
		PngStruct png);
	std::vector<std::vector<RGBAquad> > dataproccess(std::ifstream& fin, PngStruct png, std::vector<std::vector<char> > data);
	void cHRM_chunk(std::ifstream& fin, PngStruct png, char* buffer);

public:
	std::vector<std::vector<RGBAquad> > read();
};