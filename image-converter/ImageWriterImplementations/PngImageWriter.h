#pragma once
#include "RGBAquad.h"
#include <boost/iostreams/filtering_streambuf.hpp>
#include <vector>

class PngImageWriter {
	void set16bit(uint16_t data, char buffer[]);
	void set32bit(uint32_t data, char buffer[]);
	void set32bitrev(uint32_t data, char buffer[]);
	uint32_t saveRGBAquad(const RGBAquad& pixel);
	uint32_t Crc32(char* stream, int offset, int length, uint32_t crc);
	void setIHDR(std::ofstream& fout, std::vector< std::vector <RGBAquad> > data);
	void setIDAT(std::ofstream& fout, std::vector <char> segment, int len);
	void separateIDATs(std::ofstream& fout, std::vector< std::vector <RGBAquad> > data);
	void setIEND(std::ofstream& fout, std::vector< std::vector <RGBAquad> > data);
public:
	void write(const char* name, std::vector< std::vector <RGBAquad> > data);
};