#include <fstream>
#include <iostream>

#include <string>
#include <map>

using std::string;
using std::map;
using std::pair;

using std::ifstream;
using std::ofstream;

using std::cout;
using std::endl;


class HuffmanTree
{
public:
	 char character;
	 HuffmanTree *leftNode, *rightNode, *root;
	 void insertNode(char character, string code);
	 string decodeString(string code);
	 HuffmanTree(char character);
	 HuffmanTree();
};

class Decoder
{
public:
	 string decodeText(map<char, string> huffmanCodesTable, string encodedString);
	 string decodeTextInFile(string fileLocation, string outputFileLocation);
};
