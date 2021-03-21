#include "ImageConverter.h"

int main(int argc, char* argv[]) {
	try
	{
		ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();

		/*
		// Some LZW tests

		std::vector<int> compressed;
		LZV::compress("TOBEORNOTTOBEORTOBEORNOT", std::back_inserter(compressed));
		std::cout << std::endl;
		for (const auto&l: compressed)
		{
			std::cout << l << ", ";
		}
		std::cout << std::endl;
		std::string decompressed = LZV::decompress(compressed.begin(), compressed.end());
		std::cout << decompressed << std::endl;*/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}