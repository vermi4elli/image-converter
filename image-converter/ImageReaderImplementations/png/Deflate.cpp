#include "Deflate.h"
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
using namespace boost::iostreams;

void Deflate::compress(std::stringbuf& buf, filtering_streambuf<boost::iostreams::input>& in) {

	in.push(zlib_compressor());
	in.push(buf);
};

void  Deflate::decompress(std::stringbuf& buf, filtering_streambuf<boost::iostreams::input>& in) {
	in.push(zlib_decompressor());
	in.push(buf);

};