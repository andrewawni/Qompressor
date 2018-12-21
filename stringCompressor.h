#include <string>
#include <math.h>

using std::string;

class StringCompressor
{
public:
    string decimalToBinaryString(int x, int nBits);
    int binaryStringtoDecimal(string s);
    string binaryStreamtoASCII(string encodedString);
    string asciitoBinaryStream(string asciiString);
};
