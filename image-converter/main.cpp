#include "ImageConverter.h"

int main(int argc, char* argv[]) {
	try
	{
		ImageConverter* imageConverter = new ImageConverter(argc, argv);
		imageConverter->convertImage();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}