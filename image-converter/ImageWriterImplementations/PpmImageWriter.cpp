#include "PpmImageWriter.h"

void PpmImageWriter::write(std::vector<std::vector<RGBAquad>>& data)
{
	std::ofstream fout(name);
    int W = data.front().size(), H = data.size(), max = data.front().front().a;
    constexpr char SPACE = ' ';

    fout << "P3\n" << W << SPACE << H << "\n" << max << "\n";
    
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            fout.write(std::to_string((int)data[i][j].r).c_str(), std::to_string((int)data[i][j].r).length());
            fout.put(SPACE);
            fout.write(std::to_string((int)data[i][j].g).c_str(), std::to_string((int)data[i][j].g).length());
            fout.put(SPACE);
            fout.write(std::to_string((int)data[i][j].b).c_str(), std::to_string((int)data[i][j].b).length());
            fout.put(SPACE);
        }
    }

    std::cout << "[Debug]: Done writing" << std::endl;

    fout.close();
}
