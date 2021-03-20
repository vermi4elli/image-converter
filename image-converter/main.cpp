#include "ConsoleParser.h"

int main(int argc, char* argv[]) {
	try
	{
		ConsoleParser* consoleParser = ConsoleParser::GetInstance(argc, argv);
		std::cout << "Source path: " << consoleParser->pathSource() <<
			";\nGoal Image Type: " << printImageType(consoleParser->goalImageType()) <<
			";\nOutput path: " << consoleParser->pathOutput() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}