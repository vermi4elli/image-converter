#pragma once
#include "../DataTypes/rgbaquad.h"
#include "../ImageWriterInterface/IImageWriter.h"
#include "../ImageReaderImplementations/png/Deflate.h"

class PngImageWriter :
	public IImageWriter {
	void set16bit(uint16_t data, char buffer[]);
	void set32bit(uint32_t data, char buffer[]);
	void set32bitrev(uint32_t data, char buffer[]);
	uint32_t saveRGBAquad(const RGBAquad& pixel);
	uint32_t Crc32(char* stream, int offset, int length, uint32_t crc);
	void setIHDR(std::ofstream& fout, const std::vector< std::vector <RGBAquad> >& data);
	void setIDAT(std::ofstream& fout, const std::vector <char>& segment, int len);
	void separateIDATs(std::ofstream& fout, const std::vector< std::vector <RGBAquad> >& data);
	void setIEND(std::ofstream& fout, const std::vector< std::vector <RGBAquad> >& data);
public:
	PngImageWriter(const std::string& name) : IImageWriter(name) {};
	void write(const std::vector< std::vector <RGBAquad> >& data);
};