#pragma once
#include <string>
#include <map>
#include <iterator>

class LZV
{
public:
template <typename Iterator>
    static Iterator compress(const std::string& uncompressed, Iterator result);
template <typename Iterator>
    static std::string decompress(Iterator begin, Iterator end);
};

template<typename Iterator>
inline Iterator LZV::compress(const std::string& uncompressed, Iterator result)
{
    // Build the dictionary.
    int dictSize = 256;
    std::map<std::string, int> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary[std::string(1, i)] = i;

    std::string w;
    for (std::string::const_iterator it = uncompressed.begin();
        it != uncompressed.end(); ++it) {
        char c = *it;
        std::string wc = w + c;
        if (dictionary.count(wc))
            w = wc;
        else {
            *result++ = dictionary[w];
            // Add wc to the dictionary.
            dictionary[wc] = dictSize++;
            w = std::string(1, c);
        }
    }

    // Output the code for w.
    if (!w.empty())
        *result++ = dictionary[w];
    return result;
}

template<typename Iterator>
inline std::string LZV::decompress(Iterator begin, Iterator end)
{
    // Build the dictionary.
    int dictSize = 256;
    std::map<int, std::string> dictionary;
    for (int i = 0; i < 256; i++)
        dictionary[i] = std::string(1, i);

    std::string w(1, *begin++);
    std::string result = w;
    std::string entry;
    for (; begin != end; begin++) {
        int k = *begin;
        if (dictionary.count(k))
            entry = dictionary[k];
        else if (k == dictSize)
            entry = w + w[0];
        else
            throw "Bad compressed k";

        result += entry;

        // Add w+entry[0] to the dictionary.
        dictionary[dictSize++] = w + entry[0];

        w = entry;
    }
    return result;
}
