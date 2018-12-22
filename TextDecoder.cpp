#include "TextDecoder.h"
#include "stringCompressor.h"

HuffmanTree::HuffmanTree(char character)
{
	this->character = character;
	leftNode = NULL;
	rightNode = NULL;
}

HuffmanTree::HuffmanTree()
{
	root = NULL;
	leftNode = NULL;
	rightNode = NULL;
}

//insert nodes in a tree by creating new ones or by passing by them
void HuffmanTree::insertNode(char character, string code)
{
	HuffmanTree *ptr;
	if (root == NULL)
	{
		HuffmanTree *node = new HuffmanTree('#');
		root = node;
		ptr = root;
	}

	else	ptr = root;


	for (int i = 0; i < code.size(); i++)
	{
		char nodeChar = ' ';
		//checking if we reached the end of the tree
		if (i == code.size() - 1) nodeChar = character;
		else nodeChar = '#';

		//go left or right depending on the code char
		if (code[i] == '0')
		{
			if (ptr->leftNode == nullptr)
			{
				HuffmanTree *node = new HuffmanTree(nodeChar);
				ptr->leftNode = node;
				ptr = ptr->leftNode;
			}

			else ptr = ptr->leftNode;
		}

		else
		{
			if (ptr->rightNode == nullptr)
			{
				HuffmanTree *node = new HuffmanTree(nodeChar);
				ptr->rightNode = node;
				ptr = ptr->rightNode;

			}

			else ptr = ptr->rightNode;
		}
	}
}

//traverse the tree decoding the message to it's origin
string HuffmanTree::decodeString(string code)
{
	HuffmanTree *ptr = root;
	string result = "";
	ptr = root;
	for (int i = 0; i < code.size(); i++)
	{
		if (code[i] == '0') ptr = ptr->leftNode;
		else ptr = ptr->rightNode;

		if (ptr->rightNode == nullptr && ptr->leftNode == nullptr)
		{
			result += ptr->character;
			ptr = root;
		}
	}

	return result;
}

//return a decoded string using huffmanCodes and the encodedString
string Decoder::decodeText(map<char, string> huffmanCodesTable, string encodedString)
{
	HuffmanTree Tree;
	map<char, string>::iterator it;

	for (it = huffmanCodesTable.begin(); it != huffmanCodesTable.end(); it++)
		Tree.insertNode(it->first, it->second);

	return Tree.decodeString(encodedString);
}

//return a decoded string of the encoded text file location
string Decoder::decodeTextInFile(string fileLocation, string outputFileLocation)
{
	StringCompressor compressor;
	map<char, string> huffmanMapCodes;
	pair<char, string> huffmanMapPair;
	int counter = 0;
	bool firstLine = true;
    string encodedText, readLine, charCode;
	ifstream readHuffmanFile;
	readHuffmanFile.open(fileLocation);
	if (readHuffmanFile.is_open())
	{
        char c;
        while (readHuffmanFile.get(c))
        {
            encodedText.push_back(c);
            int txtSz = encodedText.size();
            if (encodedText[txtSz - 1] == 'D' && encodedText[txtSz - 2] == 'N' && encodedText[txtSz - 3] == 'E') break;
        }

        for (int i = 0; i < 3; i++)
        {
            encodedText.pop_back();
        }

        while (getline(readHuffmanFile, readLine))
        {
            int p = 0;
            string keyString, valueString;
            keyString += readLine[0];
            for (p = 1; p < readLine.size(); p++)
            {
                if (readLine[p] == '\t') break;
                keyString += readLine[p];
            }

            if (keyString == "\\n") keyString = "\n";

            for (int i = p + 1; i < readLine.size(); i++)
                valueString.push_back(readLine[i]);

            huffmanMapPair.first = keyString[0];
            huffmanMapPair.second = valueString;
            huffmanMapCodes.insert(huffmanMapPair);

        }
    }

    else cout << "Couldn't open the file" << endl;

    readHuffmanFile.close();
//    cout << encodedText << endl;

    encodedText = compressor.asciitoBinaryStream(encodedText);
//	cout << encodedText << endl;

	map<char, string>::iterator it;

//	for (it = huffmanMapCodes.begin(); it != huffmanMapCodes.end(); it++)
//	  cout << it->first << " => " << it->second << endl;

	ofstream decodedFile(outputFileLocation);
	decodedFile << decodeText(huffmanMapCodes, encodedText);
	return decodeText(huffmanMapCodes, encodedText);
}
