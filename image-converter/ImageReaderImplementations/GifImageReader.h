#pragma once
#include "../DataTypes/rgbaquad.h"
#include "../DataTypes/GifStruct.h"
#include "../ImageReaderInterface/IImageReader.h"
#include <vector>

class GifImageReader :
	public IImageReader {
	constexpr uint32_t get16bit(char bits[]);
	constexpr uint32_t get16bitrev(char bits[]);
	constexpr uint32_t get32bit(char bits[]);
	constexpr uint32_t get32bitrev(char bits[]);
	std::vector<RGBAquad> buildcolortable(std::ifstream& fin, GifStruct gif);
	int getcode(std::vector<char > flow, int offset, int len);
	std::vector<std::vector<int> > initdict(GifStruct& gif, std::vector<RGBAquad> table);
	void addpixels(std::vector<RGBAquad>& pixels, std::vector<int> list, std::vector<RGBAquad> table);
	std::vector<RGBAquad> decodeimage(std::ifstream& fin, GifStruct& gif, std::vector<RGBAquad> table);
	std::vector<std::vector<RGBAquad> > arraytomatrix(GifStruct gif, std::vector<RGBAquad> pixels);
public:
	GifImageReader(const std::string& name) : IImageReader(name) {};
	std::vector<std::vector<RGBAquad> > read();
};
