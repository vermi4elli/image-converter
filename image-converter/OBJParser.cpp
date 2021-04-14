#include <iostream>
#include <fstream>
#include <string>
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "OBJParser.h"

OBJParser* OBJParser::objParser_;

OBJParser::OBJParser(const std::string& inputPath)
{
	std::ifstream file(inputPath);
	std::string line;
	float x, y, z;
	std::vector<int> vs, ns;
	std::vector<std::string> splitVertVec;
	std::vector<std::string> splitVertNormVec;
	vertices.push_back(new Vector3D(0, 0, 0));
	normals.push_back(new Vector3D(0, 0, 0));
	
	while (std::getline(file, line))
	{
		if (line[0] == 'v')
		{
			boost::split(splitVertVec, line.substr(line[1] == 'n' ? 3 : 2), boost::is_any_of(" "), boost::token_compress_on);
			x = atof(splitVertVec[0].c_str());
			y = atof(splitVertVec[1].c_str());
			z = atof(splitVertVec[2].c_str());
			
			if (line[1] != 'n')
			{
				vertices.push_back(new Vector3D(x, y, z));
			}
			else
			{
				normals.push_back(new Vector3D(x, y, z));
			}

			splitVertVec.clear();
		}
		else if (line[0] == 'f')
		{
			boost::split(splitVertVec, line.substr(2), boost::is_any_of(" "), boost::token_compress_on);
			for (auto& i : splitVertVec)
			{
				if (i.find('//') != std::string::npos)
				{
					boost::split(splitVertNormVec, i, boost::is_any_of("/"), boost::token_compress_on);

					vs.push_back(atoi(splitVertNormVec[0].c_str()));
					ns.push_back(atoi(splitVertNormVec[1].c_str()));

					splitVertNormVec.clear();
				}
				else
				{
					vs.push_back(atoi(i.c_str()));
				}
			}

			faces.push_back(new Triangle(*vertices[vs[0]], *vertices[vs[1]], *vertices[vs[2]],
				Vector3D(0.32, 1, 0.32), *normals[ns[0]]));

			splitVertVec.clear();
			vs.clear();
			ns.clear();
		}
	}

	std::cout << "[Debug]: Done parsing " << inputPath << std::endl;
}

OBJParser* OBJParser::GetInstance(const std::string& inputPath)
{
	if (objParser_ == nullptr) {
		objParser_ = new OBJParser(inputPath);
	}
	return objParser_;
}

void OBJParser::PrintInfo() const
{
	int counter = 0;
	for (auto& i : faces)
	{
		++counter;
		std::cout << counter << " => A ( x: " << i->a.x << "; y: " << i->a.y << "; z: " << i->a.z << "; )" <<
			", B ( x: " << i->b.x << "; y: " << i->b.y << "; z: " << i->b.z << "; )" <<
			", C ( x: " << i->c.x << "; y: " << i->c.y << "; z: " << i->c.z << "; )" << std::endl;
	}
}

const std::vector<Triangle*>& const OBJParser::GetFaces()
{
	return faces;
}

