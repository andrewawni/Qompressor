#include <fstream>
#include <iostream>

#include <queue>
#include <vector>
#include <string>
#include <map>

#include "stringCompressor.h"

using std::ifstream;
using std::ofstream;

using std::cout;
using std::endl;

using std::map;
using std::string;
using std::priority_queue;
using std::vector;


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
