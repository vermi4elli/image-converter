#include "PpmImageWriter.h"

void PpmImageWriter::write(std::vector<std::vector<RGBAquad>> data)
{
	std::ofstream fout(name);
    int W = data.front().size(), H = data.size(), max = data.front().front().a;
    
    fout << "P3\n" << W << " " << H << "\n" << max << "\n";

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            fout << (int)data[i][j].r << " ";
            fout << (int)data[i][j].g << " ";
            fout << (int)data[i][j].b << " ";
        }
    }

    fout.close();
}
