#include <string>
#include <math.h>

using std::string;

class StringCompressor
{
private:
	string decimalToBinaryString(int x, int nBits);
	int binaryStringtoDecimal(string s);
public:
	string binaryStreamtoASCII(string encodedString); 
	string asciitoBinaryStream(string asciiString);
};

