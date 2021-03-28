#include <fstream>
#include <iostream>
#include <iomanip>

constexpr uint32_t GifImageReader::get16bit(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) << 8;
}

constexpr uint32_t GifImageReader::get16bitrev(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) << 8;
}

constexpr uint32_t GifImageReader::get32bit(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[3])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[2])) << 8 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) << 16 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) << 24;
}


constexpr uint32_t GifImageReader::get32bitrev(char bits[]) {

	return
		static_cast<uint32_t>(static_cast<uint8_t>(bits[0])) |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[1])) << 8 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[2])) << 16 |
		static_cast<uint32_t>(static_cast<uint8_t>(bits[3])) << 24;
}

std::vector<RGBAquad> GifImageReader::buildcolortable(std::ifstream& fin, GifStruct gif) {

	char buffer[4];
	std::vector<RGBAquad> colors;
	for (int i = 0; i < gif.colortablesize; i++) {
		RGBAquad temp;
		fin.read(buffer, 1);
		temp.r = static_cast<uint8_t>(buffer[0]);
		fin.read(buffer, 1);
		temp.g = static_cast<uint8_t>(buffer[0]);
		fin.read(buffer, 1);
		temp.b = static_cast<uint8_t>(buffer[0]);
		colors.push_back(temp);
	}

	return colors;
}

int GifImageReader::getcode(std::vector<char > flow,int offset, int len) {
	int index = offset / 8;
	uint32_t code = static_cast<uint32_t>(static_cast<uint8_t>(flow[index])) |
		static_cast<uint32_t>(static_cast<uint8_t>(flow[index+1])) << 8 |
		static_cast<uint32_t>(static_cast<uint8_t>(flow[index+2])) << 16;
	int mask = pow(2, len) - 1;
	return (code >> (offset%8)) & mask;
}

std::vector<std::vector<int> > GifImageReader::initdict(GifStruct& gif, std::vector<RGBAquad> table) {
	std::vector<std::vector<int> > dictionary;
	for (int i = 0; i < table.size(); i++) {
		std::vector<int> temp;
		temp.push_back(i);
		dictionary.push_back(temp);
	}
	std::vector<int> empty;
	gif.clear = dictionary.size();
	dictionary.push_back(empty);
	gif.end = dictionary.size();
	dictionary.push_back(empty);

	return dictionary;
}

void GifImageReader::addpixels(std::vector<RGBAquad> &pixels, std::vector<int> list, std::vector<RGBAquad> table) {
	for (int i = 0; i < list.size(); i++) {
		pixels.push_back(table[list[i]]);
	}
}


std::vector<RGBAquad> GifImageReader::decodeimage(std::ifstream& fin, GifStruct& gif, std::vector<RGBAquad> table) {

	char buffer[4];
	//Image Descriptor [2C]
	while (!fin.eof()) {
		fin.read(buffer, 1);
		std::cout << static_cast<uint8_t>(buffer[0]);
		if (static_cast<uint8_t>(buffer[0]) == 0x2c) break;
	}


	fin.read(buffer, 2);

	gif.x_coord = get16bitrev(buffer);

	fin.read(buffer, 2);

	gif.y_coord = get16bitrev(buffer);

	fin.read(buffer, 2);
	int width = get16bitrev(buffer);

	fin.read(buffer, 2);
	int heigth = get16bitrev(buffer);

	fin.read(buffer, 1);

	bool localtable = (buffer[0] >> 7) & 1;

	bool interlains = (buffer[0] & 0b1000000) >> 6;

	bool sorted = (buffer[0] & 0b100000) >> 5;

	int extention = (buffer[0] & 0b111);

	fin.read(buffer, 1);

	int minsize = static_cast<int>(buffer[0]) + 1;

	fin.read(buffer, 1);

	int sectionlength = static_cast<uint8_t>(buffer[0]);

	std::vector<std::vector<int> > dictionary = initdict(gif, table);

	uint32_t code = 0;
	uint32_t prevcode = 0;
	uint32_t offset = 0;
	int codesize = minsize;
	const int MAXCODESIZE = 12;
	std::vector<RGBAquad> pixels;
	std::vector<char > dataflow;
	
	while (!fin.eof())
	{
		if (sectionlength == 0) {
			fin.read(buffer, 1);
			sectionlength = static_cast<uint8_t>(buffer[0]);
			if (sectionlength == 0) break;
		}
		else {
			fin.read(buffer, 1);
			dataflow.push_back(buffer[0]);
			sectionlength--;
		}
	}
	bool prevclear = false;
	while (true)
	{
		code = getcode(dataflow, offset, codesize);

		if (code == gif.clear) {
			dictionary = initdict(gif, table);
			offset += codesize;
			codesize = minsize;
			prevclear = true;
		}
		else if (code == gif.end) {
			break;
		}
		else {

			if (prevclear) {
				pixels.push_back(table[code]);
				prevclear = false;
			}
			else if (dictionary.size() == code) {
				std::vector<int> temp = dictionary[prevcode];
				temp.push_back(dictionary[prevcode][0]);
				dictionary.push_back(temp);

				addpixels(pixels, dictionary[code], table);
			}
			else {
				std::vector<int> temp = dictionary[code];
				int firstcode = temp[0];
				addpixels(pixels, dictionary[code], table);

				std::vector<int> temp1 = dictionary[prevcode];
				temp1.push_back(firstcode);
				dictionary.push_back(temp1);


			}
			prevcode = code;
			offset += codesize;
		}


		if (dictionary.size() == pow(2, codesize) && codesize < MAXCODESIZE) {
			codesize++;
		}
	}

	fin.read(buffer, 1);
	if (static_cast<uint8_t>(buffer[0]) == 0x3b) {
		return pixels;
	}
	else {
		exit(1);
	}

}
std::vector<std::vector<RGBAquad> > GifImageReader::arraytomatrix(GifStruct gif, std::vector<RGBAquad> pixels) {

	std::vector<std::vector<RGBAquad> > temp;
	temp.resize(gif.heigth);
	int index = 0;
	for (int i = 0; i < gif.heigth; i++) {
		temp[i].resize(gif.width);
		for (int j = 0; j < gif.width; j++) {
			if (index == pixels.size()) {
				temp[i][j] = RGBAquad();
			} else{
			temp[i][j] = pixels[index];
			index++;
			}

		}
	}
	return temp;
}
std::vector<std::vector<RGBAquad> > GifImageReader::read() {

	GifStruct gif;

	std::ifstream fin(name, std::ios::binary);

	char buffer[4];

	fin.read(buffer, 3);

	if (buffer[0] != 'G' || buffer[1] != 'I' || buffer[2] != 'F') {
		std::cout << "not gif";
		exit(1);
	}

	fin.read(buffer, 3);

	if (buffer[0] != '8' || buffer[1] != '9' || buffer[2] != 'a') {
		std::cout << "not gif89a";
		exit(1);
	}



	fin.read(buffer, 2);
	gif.width = get16bitrev(buffer);

	fin.read(buffer, 2);
	gif.heigth = get16bitrev(buffer);

	fin.read(buffer, 1);

	gif.globaltable = (buffer[0] >> 7) & 1;

	gif.colorextention = pow(2,((buffer[0] & 0b1110000) >> 4) + 1);


	gif.colorssorted = (buffer[0] & 0b1000) >> 3;

	gif.colortablesize = pow(2, (buffer[0] & 0b111) + 1 );

	fin.read(buffer, 1);
	gif.transparency = get16bitrev(buffer);

	fin.read(buffer, 1);
	gif.correlation = get16bitrev(buffer);

	std::vector<RGBAquad> colortable = buildcolortable(fin, gif);


	return 	arraytomatrix(gif,decodeimage(fin, gif, colortable));
}