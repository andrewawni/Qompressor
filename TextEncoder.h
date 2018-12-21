#include<iostream>
#include <fstream>
#include<queue>
#include<vector>
#include<string>
#include<map>
#include "stringCompressor.h"

using namespace std;

class node
{
public :
	 int freq;
	 string m_char;
	 node *left;
	 node *right;

	 node(string p_char, int p_freq);
};

class Encoder
{
private:
	 map<char, string> codeMap;

// Traversing the tree
	 void ConstructMap(node *n, string s);

public:
	 string encodeStringFromFile(string inputPath, string outputPath);
};
