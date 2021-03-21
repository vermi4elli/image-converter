#include "ConsoleParser.h"
#include "ImageReaderImplementations/PpmImageReader.h"
#include "ImageWriterImplementations/PpmImageWriter.h"

int main(int argc, char* argv[]) {
	try
	{
		/*ConsoleParser* consoleParser = ConsoleParser::GetInstance(argc, argv);
		std::cout << "Source path: " << consoleParser->pathSource() <<
			";\nGoal Image Type: " << printImageType(consoleParser->goalImageType()) <<
			";\nOutput path: " << consoleParser->pathOutput() << std::endl;*/

		PpmImageReader reader;
		//auto res = reader.read("..\\images\\ppm\\pbmlib.ppm");
		//auto res = reader.read("..\\images\\ppm\\pbmlib.ascii.ppm");
		//auto res = reader.read("..\\images\\ppm\\bell_206.ppm");
		//auto res = reader.read("..\\images\\ppm\\star_field.ascii.ppm");
		auto res = reader.read("..\\images\\ppm\\newton.ppm");

		PpmImageWriter writer;
		writer.write("..\\images\\ppm\\result.ppm", res);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}
	return 0;
}