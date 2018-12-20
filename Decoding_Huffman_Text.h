#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

class HuffmanTree {

public:
    char character;
    HuffmanTree *leftNode, *rightNode, *root;

    HuffmanTree(char character);

    HuffmanTree();

    void insertNode(char character, string code);

    string decodeString(string code);
};


class Decoding_Huffman_Text {

public:
    Decoding_Huffman_Text();

    string decodeText(map<char, string> huffmanCodesTable, string encodedString);

    string decodeTextInFile(string fileLocation);

    ~Decoding_Huffman_Text();
};
