#include "ConsoleParser.h"
#include "ImageReaderImplementations/PpmImageReader.h"

int main(int argc, char* argv[]) {
	try
	{
		/*ConsoleParser* consoleParser = ConsoleParser::GetInstance(argc, argv);
		std::cout << "Source path: " << consoleParser->pathSource() <<
			";\nGoal Image Type: " << printImageType(consoleParser->goalImageType()) <<
			";\nOutput path: " << consoleParser->pathOutput() << std::endl;*/

		PpmImageReader reader;
		reader.read("C:\\Users\\nikit\\OneDrive\\Рабочий стол\\star_field.ascii.ppm");
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}