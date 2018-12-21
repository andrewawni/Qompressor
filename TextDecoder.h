#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

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
