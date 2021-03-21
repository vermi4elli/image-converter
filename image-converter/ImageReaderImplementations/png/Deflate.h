#pragma once
#include <iostream>
#include <sstream>
#include <boost/iostreams/filtering_streambuf.hpp>

class Deflate {

public:
	void compress(std::stringbuf& fin, boost::iostreams::filtering_streambuf<boost::iostreams::input>& in);
	void decompress(std::stringbuf& fin, boost::iostreams::filtering_streambuf<boost::iostreams::input>& in);
};