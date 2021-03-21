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
		reader.read("C:\\Users\\nikit\\OneDrive\\Рабочий стол\\pbmlib.ppm");

		/*std::ofstream f("C:\\Users\\nikit\\OneDrive\\Рабочий стол\\text.txt");
		if (f.fail()) return -1;

		f << "P6\n" << 1 << " " << 1 << "\n" << "255\n";
		f << uint8_t(255) << " " << uint8_t(0) << " " << uint8_t(0);

		std::cout << ((int)'я') << std::endl;

		f.close();*/
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}