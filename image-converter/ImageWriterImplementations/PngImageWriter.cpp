#include "PngImageWriter.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "rgbaquad.h"
#include "Deflate.h"
#include <sstream>
#include "BmpImageWriter.h";
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include "PngFilter.h"

void PngImageWriter::set16bit(uint16_t data, char buffer[]) {
	buffer[1] = static_cast<char>(data);
	buffer[0] = static_cast<char>(data >> 8);
}

void PngImageWriter::set32bit(uint32_t data, char buffer[]) {
	buffer[0] = static_cast<char>(data);
	buffer[1] = static_cast<char>(data >> 8);
	buffer[2] = static_cast<char>(data >> 16);
	buffer[3] = static_cast<char>(data >> 24);
}

void PngImageWriter::set32bitrev(uint32_t data, char buffer[]) {
	buffer[3] = static_cast<char>(data);
	buffer[2] = static_cast<char>(data >> 8);
	buffer[1] = static_cast<char>(data >> 16);
	buffer[0] = static_cast<char>(data >> 24);
}

uint32_t PngImageWriter::saveRGBAquad(const RGBAquad& pixel)
{
	return
		(static_cast<uint32_t>(pixel.r) << 16) |
		(static_cast<uint32_t>(pixel.g) << 8) |
		(static_cast<uint32_t>(pixel.b) << 0) |
		(static_cast<uint32_t>(pixel.a) << 24);
}
int* crcTable;
uint32_t PngImageWriter::Crc32(char* stream, int offset, int length, uint32_t crc) {
	int c;

	if (crcTable == nullptr) {
		crcTable = new int[256];
		for (int n = 0; n <= 255; n++) {
			c = n;
			for (int k = 0; k <= 7; k++) {
				if ((c & 1) == 1)
					c = 0xEDB88320 ^ ((c >> 1) & 0x7FFFFFFF);
				else
					c = ((c >> 1) & 0x7FFFFFFF);
			}
			crcTable[n] = c;
		}
	}
	c = crc ^ 0xffffffff;
	auto endOffset = offset + length;
	for (auto i = offset; i < endOffset; i++) {
		c = crcTable[(c ^ stream[i]) & 255] ^ ((c >> 8) & 0xFFFFFF);
	}
	return c ^ 0xffffffff;
}
void PngImageWriter::setIHDR(std::ofstream& fout,std::vector< std::vector <RGBAquad> > data) {
	char buffer[4];
	uint32_t crc = 0;

	set32bitrev(13, buffer);
	crc = Crc32(buffer, 0, 4, crc);
	fout.write(buffer, 4);

	buffer[0] = 'I';
	buffer[1] = 'H';
	buffer[2] = 'D';
	buffer[3] = 'R';
	crc = Crc32(buffer, 0, 4, crc);
	fout.write(buffer, 4);

	
	//set width
	set32bitrev(data[0].size(), buffer);
	fout.write(buffer, 4);
	crc = Crc32(buffer, 0, 4, crc);

	//set height
	set32bitrev(data.size(), buffer);
	fout.write(buffer, 4);
	crc = Crc32(buffer, 0, 4, crc);
	
	//set bitdepth
	buffer[0] = 8;
	fout.write(buffer, 1);
	crc = Crc32(buffer, 0, 1, crc);
	//set color type
	buffer[0] = 2;
	fout.write(buffer, 1);
	crc = Crc32(buffer, 0, 1, crc);
	//set compression method
	buffer[0] = 0;
	fout.write(buffer, 1);
	crc = Crc32(buffer, 0, 1, crc);
	//set filter method
	buffer[0] = 0;
	fout.write(buffer, 1);
	crc = Crc32(buffer, 0, 1, crc);
	//set interlace method
	buffer[0] = 0;
	fout.write(buffer, 1);
	crc = Crc32(buffer, 0, 1, crc);

	set32bitrev(crc, buffer);
	fout.write(buffer, 4);
}
void PngImageWriter::setIDAT(std::ofstream& fout, std::vector <char> segment,int len) {
	char buffer[4];
	uint32_t crc = 0;
	set32bitrev(len, buffer);
	fout.write(buffer, 4);


	buffer[0] = 'I';
	buffer[1] = 'D';
	buffer[2] = 'A';
	buffer[3] = 'T';
	fout.write(buffer, 4);
	crc = Crc32(buffer, 0, 4, crc);

	for (auto ch : segment) {
		buffer[0] = ch;
		fout.write(buffer, 1);
		crc = Crc32(buffer, 0, 1, crc);
	}
	set32bitrev(crc, buffer);
	fout.write(buffer, 4);
}

void PngImageWriter::separateIDATs(std::ofstream& fout, std::vector< std::vector <RGBAquad> > data) {
	std::stringbuf uncompressed;
	for (auto row : data) {
		uncompressed.sputc('0');
		for (auto pixel : row) {
			uncompressed.sputc(pixel.r);
			uncompressed.sputc(pixel.g);
			uncompressed.sputc(pixel.b);
		}
	}

	Deflate compressor;
	boost::iostreams::filtering_streambuf<boost::iostreams::input> compressed;
	compressor.compress(uncompressed, compressed);

	std::vector <char> segment;
	char buffer[1];
	int len = 0;

	while (compressed.sgetc() != EOF) {
		compressed.sgetn(buffer, 1);
		segment.push_back(buffer[0]);
		len++;
		if (len == 32768) {
			setIDAT(fout,segment, len);
			len = 0;
			segment.resize(0);
		}
	}

	if (len != 0) {
		setIDAT(fout, segment, len);
	}
}

void PngImageWriter::setIEND(std::ofstream& fout, std::vector< std::vector <RGBAquad> > data) {
	char buffer[4];
	uint32_t crc = 0;

	set32bitrev(0, buffer);

	fout.write(buffer, 4);

	buffer[0] = 'I';
	buffer[1] = 'E';
	buffer[2] = 'N';
	buffer[3] = 'D';
	crc = Crc32(buffer, 0, 4, crc);
	fout.write(buffer, 4);

	set32bitrev(crc, buffer);
	fout.write(buffer, 4);
}

void PngImageWriter::write(const char* name, std::vector< std::vector <RGBAquad> > data) {

	std::ofstream fout(name, std::ios::binary);
	char buffer[4];


	buffer[0] = (char)0x89;
	fout.write(buffer, 1);

	buffer[0] = 'P'; buffer[1] = 'N'; buffer[2] = 'G';

	fout.write(buffer, 3);


	buffer[0] = (char)0x0D; buffer[1] = (char)0x0A;

	fout.write(buffer, 2);

	buffer[0] = (char)0x1A; buffer[1] = (char)0x0A;
	fout.write(buffer, 2);

	setIHDR(fout, data);

	separateIDATs(fout, data);

	setIEND(fout, data);
}