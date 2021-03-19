#include "ConsoleParser.h"

int main(int argc, char* argv[]) {
	try
	{
		ConsoleParser::GetInstance(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}