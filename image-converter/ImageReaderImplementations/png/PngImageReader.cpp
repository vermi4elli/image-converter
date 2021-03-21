#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "PngImageReader.h"
#include "rgbaquad.h"
#include "Deflate.h"
#include <sstream>
#include "BmpImageWriter.h";
#include <boost/iostreams/filtering_streambuf.hpp>
#include "PngFilter.h"

constexpr uint32_t PngImageReader::get32bit(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[3])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[2])) << 8 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) << 16 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) << 24;
}


constexpr uint32_t PngImageReader::get32bitrev(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) << 8 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[2])) << 16 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[3])) << 24;
}

int* crcTable;
uint32_t PngImageReader::Crc32(char* stream, int offset, int length, uint32_t crc) {
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

void PngImageReader::gAMA_chunk(std::ifstream& fin,PngStruct png,char* buffer) {

	fin.read(buffer, 4 );
	png.gAMA = get32bit(buffer);
}
void PngImageReader::bKGD_chunk(std::ifstream& fin) {

	char buffer[6];

	fin.read(buffer, 6);

}
void PngImageReader::IDAT_chunk(std::ifstream& fin, int len, std::vector<std::vector<char> >& data) {

	char buffer[1];
	std::vector<char> temp;
	for (int i = 0; i < len; i++) {
		fin.read(buffer, 1);
		temp.push_back(buffer[0]);
	}
	data.push_back(temp);

}


void PngImageReader::filterdata(boost::iostreams::filtering_streambuf<boost::iostreams::input>& decompressed,
				std::vector<std::vector<uint8_t> >& bytes_matrix, 
				PngStruct png) {
	bytes_matrix.resize(png.height);
	int bytes_matrix_width = png.alpha ? png.width * 4 : png.width * 3;
	PngFilter filter;
	for (int i = 0; i < png.height; i++) {
		bytes_matrix[i].resize(bytes_matrix_width);

		char buffer[1];

		decompressed.sgetn(buffer, 1);

		uint8_t filter_type = static_cast<uint8_t>(buffer[0]);

		filter.setfilter(filter_type);
		for (int j = 0; j < bytes_matrix_width; j++) {
			decompressed.sgetn(buffer, 1);
			uint8_t x = static_cast<uint8_t>(buffer[0]);
			uint8_t a = (j > 0) ? bytes_matrix[i][j - 1] : 0;
			uint8_t b = (i > 0) ? bytes_matrix[i - 1][j] : 0;
			uint8_t c = (i > 0 && j > 0) ? bytes_matrix[i - 1][j - 1] : 0;

			bytes_matrix[i][j] = static_cast<uint8_t>((filter.revfilter(x, a, b, c) + 256) % 256);
		}
	}

}
std::vector<std::vector<RGBAquad> >  PngImageReader::buildpixelmatrix(std::vector<std::vector<uint8_t> >& bytes_matrix, PngStruct png){
	std::vector<std::vector<RGBAquad> > pixel_matrix;
	pixel_matrix.resize(png.height);

	for (int i = 0; i < png.height; i++) {
		pixel_matrix[i].resize(png.width);
		int index = 0;

		for (auto& pixel : pixel_matrix[i]) {

			pixel.r = bytes_matrix[i][index];
			index++;
			pixel.g = bytes_matrix[i][index];
			index++;
			pixel.b = bytes_matrix[i][index];
			index++;
			if (png.alpha) {
				pixel.a = bytes_matrix[i][index];
				index++;
			}
		}

	}
	return pixel_matrix;

}

std::vector<std::vector<RGBAquad> > PngImageReader::dataproccess
			(std::ifstream& fin, PngStruct png, std::vector<std::vector<char> > data) {

	std::stringbuf compressed;

	for (auto idat_data : data) {
		for (auto ch : idat_data) {
			compressed.sputc(ch);
		}
	}
	Deflate decompressor;

	boost::iostreams::filtering_streambuf<boost::iostreams::input> decompressed;

	decompressor.decompress(compressed, decompressed);

	std::vector<std::vector<uint8_t> > bytes_matrix;

	filterdata(decompressed, bytes_matrix,png);

	return buildpixelmatrix(bytes_matrix, png);
}

void PngImageReader::cHRM_chunk(std::ifstream& fin, PngStruct png, char* buffer) {
	int t = png.chunks_length[png.chunks_length.size() - 1];

	fin.read(buffer, 4);
	png.White_Point_x = get32bit(buffer);

	fin.read(buffer, 4);
	png.White_Point_y = get32bit(buffer);

	fin.read(buffer, 4);
	png.Red_x = get32bit(buffer);

	fin.read(buffer, 4);
	png.Red_y = get32bit(buffer);

	fin.read(buffer, 4);
	png.Green_x = get32bit(buffer);

	fin.read(buffer, 4);
	png.Green_y = get32bit(buffer);

	fin.read(buffer, 4);
	png.Blue_x = get32bit(buffer);

	fin.read(buffer, 4);
	png.Blue_y = get32bit(buffer);
}


std::vector<std::vector<RGBAquad> > PngImageReader::read() {
	std::ifstream fin("shisui.png", std::ios::binary);

	PngStruct png;

	char buffer[4];

	fin.read(buffer, 1);

	if (buffer[0] != (char)0x89) exit(1);

	fin.read(buffer, 3);
	
	if (buffer[0] != 'P' || buffer[1] != 'N' || buffer[2] != 'G') exit(1);

	fin.read(buffer, 2);

	if (buffer[0] != (char)0x0D && buffer[1] != (char)0x0A) exit(1);

	fin.read(buffer, 2);

	if (buffer[0] != (char)0x1A && buffer[1] != (char)0x0A) exit(1);

	fin.read(buffer, 4);

	auto lenght_IHDR = get32bit(buffer);

	fin.read(buffer, 4);
	std::string s;
	s.push_back(buffer[0]);
	s.push_back(buffer[1]); 
	s.push_back(buffer[2]); 
	s.push_back(buffer[3]); 

	if(s != "IHDR") exit(1);

	fin.read(buffer, 4);
	png.width = get32bit(buffer);

	fin.read(buffer, 4);
	png.height = get32bit(buffer);

	fin.read(buffer, 1);
	png.bit_depth = static_cast<uint8_t>(buffer[0]);
	if (png.bit_depth != 8) {
		std::cout << "support only 8 bitdepth";
		exit(1);
	}

	fin.read(buffer, 1);
	png.color_type = static_cast<uint8_t>(buffer[0]);
	if (png.color_type >= 4) png.alpha = true;

	fin.read(buffer, 1);
	png.compression_method = static_cast<uint8_t>(buffer[0]);

	fin.read(buffer, 1);
	png.filter_method = static_cast<uint8_t>(buffer[0]);

	fin.read(buffer, 1);
	png.interlace_method = static_cast<uint8_t>(buffer[0]);

	fin.read(buffer, 4);
	auto crc = get32bit(buffer);
	std::vector<std::vector<char> > idat_compressed_data;

	while (!fin.eof()) {
		fin.read(buffer, 4);

		int len = get32bit(buffer);
		png.chunks_length.push_back(len);

		fin.read(buffer, 4);

		png.chunks_name.push_back(buffer);
		std::string s1;
		s1.push_back(buffer[0]);
		s1.push_back(buffer[1]);
		s1.push_back(buffer[2]);
		s1.push_back(buffer[3]);
		//if (s1 == "sRGB") sRGB_chunk(fin, png, buffer);
		if (s1 == "gAMA") { 
			gAMA_chunk(fin, png, buffer); 
		} else if (s1 == "cHRM") {
			cHRM_chunk(fin, png, buffer);
		} else if (s1 == "bKGD") {
			bKGD_chunk(fin);
		} else if (s1 == "IDAT") {
			IDAT_chunk(fin, len, idat_compressed_data); 
		}else {
			for (int i = 0; i < len; i++) {
				fin.read(buffer, 1);
			}
		}
		fin.read(buffer, 4);

	}

	return 	dataproccess(fin, png, idat_compressed_data);

}