#include "Decoding_Huffman_Text.h"


/*
 * class usage example
 *
 * #include "Decoding_Huffman_Text.h"

    int main() {
    Decoding_Huffman_Text decoder;
    string fileLocation = "/home/ahmed/Desktop/huffmanTest.txt";
    browse for the encoded file then the function will return a string of the decoded string
    cout<<decoder.decodeTextInFile(fileLocation)<<endl;
    return 0;
}
 */
//Huffman Tree
HuffmanTree::HuffmanTree(char character) {
    this->character = character;
    leftNode = NULL;
    rightNode = NULL;
}

HuffmanTree::HuffmanTree() {
    root = NULL;
    leftNode = NULL;
    rightNode = NULL;
}

//insert nodes in a tree by creating new ones or by passing by them
void HuffmanTree::insertNode(char character, string code) {
    HuffmanTree *ptr;
    if (root == NULL) {
        HuffmanTree *node = new HuffmanTree('#');
        root = node;
        ptr = root;
    } else {
        ptr = root;
    }
    for (int i = 0; i < code.size(); i++) {
        char nodeChar = ' ';
        //checking if we reached the end of the tree
        if (i == code.size() - 1)
            nodeChar = character;
        else
            nodeChar = '#';
        //go left or right depending on the code char
        if (code[i] == '0') {
            if (ptr->leftNode == nullptr) {
                HuffmanTree *node = new HuffmanTree(nodeChar);
                ptr->leftNode = node;
                ptr = ptr->leftNode;
            } else
                ptr = ptr->leftNode;
        } else {
            if (ptr->rightNode == nullptr) {
                HuffmanTree *node = new HuffmanTree(nodeChar);
                ptr->rightNode = node;
                ptr = ptr->rightNode;

            } else
                ptr = ptr->rightNode;
        }
    }
}

//traverse the tree decoding the message to it's origin
string HuffmanTree::decodeString(string code) {
    HuffmanTree *ptr = root;
    string result = "";
    ptr = root;
    for (int i = 0; i < code.size(); i++) {
        if (code[i] == '0')
            ptr = ptr->leftNode;
        else
            ptr = ptr->rightNode;

        if (ptr->rightNode == nullptr && ptr->leftNode == nullptr) {
            result += ptr->character;
            ptr = root;
        }
    }
    return result;
}

//Decoding the huffman Tree
Decoding_Huffman_Text::Decoding_Huffman_Text() {
}

Decoding_Huffman_Text::~Decoding_Huffman_Text() {
}

//return a decoded string using huffmanCodes and the encodedString
string Decoding_Huffman_Text::decodeText(map<char, string> huffmanCodesTable, string encodedString) {
    HuffmanTree Tree;
    map<char, string>::iterator it;

    for (it = huffmanCodesTable.begin(); it != huffmanCodesTable.end(); it++) {
        Tree.insertNode(it->first, it->second);
    }
    return Tree.decodeString(encodedString);
}

//return a decoded string of the encoded text file location
string Decoding_Huffman_Text::decodeTextInFile(string fileLocation) {
    map<char, string> huffmanMapCodes;
    pair<char, string> huffmanMapPair;
    int counter = 0;
    bool firstLine = true;
    string encodedText, readLine, charCode;
    ifstream readHuffmanFile;
    readHuffmanFile.open(fileLocation);
    if (readHuffmanFile.is_open()) {
        while (getline(readHuffmanFile, readLine)) {
            if (firstLine) {
                encodedText = readLine;
                firstLine = false;
            } else {
                counter++;
                if (counter == 1)
                    huffmanMapPair.first = readLine[0];
                else if (counter == 2) {
                    huffmanMapPair.second = readLine;
                    huffmanMapCodes.insert(huffmanMapPair);
                    counter = 0;
                }
            }

        }
    } else {
        cout << "we couldn't open the file" << endl;
    }
    readHuffmanFile.close();

// if you want to see the map and encoded string to check uncomment the next commented lines

    cout << encodedText << endl;

    map<char, string>::iterator it;

    for (it = huffmanMapCodes.begin(); it != huffmanMapCodes.end(); it++) {
        cout << it->first << " => " << it->second << endl;
    }
    return decodeText(huffmanMapCodes, encodedText);
}
