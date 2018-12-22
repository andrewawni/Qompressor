#include "TextEncoder.h"


node::node(string p_char, int p_freq)
{
	freq = p_freq;
	m_char = p_char;
	left = right = NULL;
}

void Encoder::ConstructMap(node *n, string s)
{
	if (n->left == NULL && n->right == NULL)
	{
		codeMap[n->m_char[0]] = s;
		s = "";
		return;
	}

	ConstructMap(n->left, s + "0");
	ConstructMap(n->right, s + "1");
}

string Encoder::encodeStringFromFile(string inputPath, string outputPath)
{
	StringCompressor compressor;
	string inpuText;
    ifstream uncompressedFile;
    uncompressedFile.open(inputPath);
    if (uncompressedFile.is_open())
    {
        char c;
        while (uncompressedFile.get(c))
        {
            inpuText.push_back(c);
        }
	}

	else
	{
        cout << "Couldn't open the file" << endl;
		return 0;
    }
	uncompressedFile.close();
    // priority queue custom compare function
//    cout << inpuText;
	struct compare
	{

		 bool operator()(node *l, node *r)
		 {
			 return (l->freq > r->freq);
		 }
	};

	string copyText = inpuText;
	priority_queue<node *, vector<node *>, compare> HuffTree;
	string encodedBits;
	int textLen = inpuText.length();

//	cout << "Text : " << inpuText << endl;
//	cout << "Number of text bits : " << textLen << endl;

	//Getting frequencies of chars
	for (int i = 0; i < inpuText.length(); i++)
	{
		int freq = 1;
		for (int j = i + 1; j < inpuText.length(); j++)
		{
			if (inpuText[i] == inpuText[j])
			{
				freq++;
				inpuText.erase(inpuText.begin() + j);
				j--;
			}
		}

		string tmp;
		tmp.push_back(inpuText[i]);
		HuffTree.push(new node(tmp, freq));
		tmp.clear();
	}

//	cout << "Tree : " << endl;
	//Contructing Huffman Tree
	int n = HuffTree.size();
	for (int i = 0; i < n - 1; i++)
	{
		node *n1 = HuffTree.top();
		HuffTree.pop();
		node *n2 = HuffTree.top();
		HuffTree.pop();
		node *new_node = new node(n1->m_char + n2->m_char, n1->freq + n2->freq);
		new_node->left = n1;
		new_node->right = n2;
//		cout << new_node->freq << " " << new_node->m_char << endl;
//		cout << "Left->" << new_node->left->m_char << new_node->left->freq << "\t" <<
//		     "Right->" << new_node->right->m_char << new_node->right->freq << endl;
		HuffTree.push(new_node);
	}
//	cout << "Map : " << endl;

	// Traversing Huffman Tree
	ConstructMap(HuffTree.top(), "");

	ofstream compressedFile(outputPath);
	// Getting encoded bits
	for (int i = 0; i < textLen; i++)
		encodedBits += codeMap[copyText[i]];

	//Writing encoded bits to a file
	//compressedFile<<encodedBits<<endl;
    compressedFile << compressor.binaryStreamtoASCII(encodedBits);
    compressedFile << "END" << endl;;

	//Writing encoding map to a file
	for (std::map<char, string>::iterator it = codeMap.begin(); it != codeMap.end(); ++it)
	{
        if (it->first != '\n')  compressedFile << it->first << '\t';
        else compressedFile << "\\n" << '\t';
        compressedFile << it->second <<endl;
        //compressedFile << compressor.binaryStreamtoASCII(it->second) << endl;
//        cout << it->first << " => " << it->second << '\n';
	}

	compressedFile.close();
//	cout << "encoded Bits : " << endl << encodedBits << endl;
//	cout << "Number of encoded bits : " << encodedBits.length() << endl;
	return encodedBits;
}
