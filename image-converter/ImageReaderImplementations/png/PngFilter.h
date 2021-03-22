#pragma once

class PngFilter {
	int filtertype;
	int None(int x, int a, int b, int c);
	int Sub(int x, int a, int b, int c);
	int SubReverse(int x, int a, int b, int c);
	int Up(int x, int a, int b, int c);
	int UpReverse(int x, int a, int b, int c);
	int Average(int x, int a, int b, int c);
	int AverageReverse(int x, int a, int b, int c);
	int Paeth(int x, int a, int b, int c);
	int PaethReverse(int x, int a, int b, int c);
	int GetPaethCoef(int a, int b, int c);


public:
	void setfilter(int f);
	int filter(int x, int a, int b, int c);
	int revfilter(int x, int a, int b, int c);
}; 