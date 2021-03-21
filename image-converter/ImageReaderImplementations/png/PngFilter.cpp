#include <iostream>;
#include "PngFilter.h"

int PngFilter::None(int x, int a, int b, int c)
{
    return x;
}

int PngFilter::Sub(int x, int a, int b, int c)
{
    return (x - a);
}

int PngFilter::SubReverse(int x, int a, int b, int c)
{
    return (x + a);
}

int PngFilter::Up(int x, int a, int b, int c)
{
    return (x - b);
}

int PngFilter::UpReverse(int x, int a, int b, int c)
{
    return (x + b);
}

int PngFilter::Average(int x, int a, int b, int c)
{
    return (x - floor(a + b) / 2);
}

int PngFilter::AverageReverse(int x, int a, int b, int c)
{
    return (x + floor(a + b) / 2);
}

int PngFilter::Paeth(int x, int a, int b, int c)
{
    int v = GetPaethCoef(a, b, c);
    return (x - v);
}

int PngFilter::PaethReverse(int x, int a, int b, int c)
{
    int v = GetPaethCoef(a, b, c);
    return (x + v);
}

int PngFilter::GetPaethCoef(int a, int b, int c)
{
    int p = a + b - c;
    int pa = abs(p - a);
    int pb = abs(p - b);
    int pc = abs(p - c);
    int pr;
    if (pa < pb && pa < pc) pr = pa;
    else if (pb < pc) pr = pb;
    else pr = pc;

    return pr;
}

int PngFilter::revfilter(int x, int a, int b, int c) {
    if (filtertype == 0) {
        return None(x, a, b, c);
    }
    else if (filtertype == 1) {
        return SubReverse(x, a, b, c);
    }
    else if (filtertype == 2) {
        return UpReverse(x, a, b, c);
    }
    else if (filtertype == 3) {
        return AverageReverse(x, a, b, c);
    }
    else if (filtertype == 4) {
        return PaethReverse(x, a, b, c);
    }
    else return 0;
}

int PngFilter::filter(int x, int a, int b, int c) {
    if (filtertype == 0) {
        return None(x, a, b, c);
    }
    else if (filtertype == 1) {
        return Sub(x, a, b, c);
    }
    else if (filtertype == 2) {
        return Up(x, a, b, c);
    }
    else if (filtertype == 3) {
        return Average(x, a, b, c);
    }
    else if (filtertype == 4) {
        return Paeth(x, a, b, c);
    }
    else return 0;
}

void PngFilter::setfilter(int f) {
    this->filtertype = f;
}