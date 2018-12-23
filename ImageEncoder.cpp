#include "../include/ImageEncoder.h"

Encoder::Encoder(string imagePath, string outputPath)
{
	cv::Mat file;

	file = cv::imread(imagePath, CV_LOAD_IMAGE_COLOR);

	if (!file.data)
	{
		std::cerr << "Could not open or find the image" << std::endl;
		exit(-1);
	}
	
	fileTXT.open(outputPath);

	fileTXT.clear();

	image = readImage(file);

	root = buildTree(image);

	binaryRepForCode("", root, false);

	fileTXT << file.rows << " " << file.cols << " " << color2bin.size() << std::endl;
}


void Encoder::printImageBin()
{
	for (int h = 0; h < int(image.size()); h++)
	{
		for (int w = 0; w < int(image[h].size()); w++)
		{
			fileTXT << color2bin[image[h][w].r];
			fileTXT << color2bin[image[h][w].g];
			fileTXT << color2bin[image[h][w].b];
			fileTXT << (w == int(image[h].size()) - 1 ? "\n" : "");
		}
	}
}

void Encoder::printImageAscii(){
	for (int h = 0; h < int(image.size()); h++)
	{
		string PxlRow = "";
		for (int w = 0; w < int(image[h].size()); w++)
		{
			PxlRow += color2bin[image[h][w].r];
			PxlRow += color2bin[image[h][w].g];
			PxlRow += color2bin[image[h][w].b];
			//PxlRow += (w == int(image[h].size()) - 1 ? "\n" : "");
		}
		string compressed = stringCompressor.binaryStreamtoASCII(PxlRow);
		fileTXT << compressed.size() << " " << compressed << '\n';
		// std::cout << compressed << std::endl;
		// return; 
	}
}

void Encoder::printImagePxl()
{
	for (int h = 0; h < int(image.size()); h++)
	{
		for (int w = 0; w < int(image[h].size()); w++)
		{
			fileTXT << image[h][w].r << "\t" << image[h][w].g << "\t" << image[h][w].b << "\t|\t";
			fileTXT << (w == int(image[h].size()) - 1 ? "\n" : "");
		}
	}
}

vector<vector<Pixel>> Encoder::readImage(cv::Mat image)
{

	std::vector<std::vector<Pixel>> ret(image.rows, std::vector<Pixel>(image.cols));
	for (int h = 0; h < image.rows; h++)
	{
		for (int w = 0; w < image.cols; w++)
		{
			ret[h][w].r = (int)image.at<cv::Vec3b>(h, w)[2]; // red
			ret[h][w].g = (int)image.at<cv::Vec3b>(h, w)[1]; // green
			ret[h][w].b = (int)image.at<cv::Vec3b>(h, w)[0]; // blue
		}
	}

	return ret;
}

// node constructor function
Node *Encoder::createNode(int count, int code, Node *left, Node *right)
{
	Node *node = (Node *)malloc(sizeof(struct Node));
	node->count = count;
	node->code = code;
	node->left = left;
	node->right = right;
	return node;
}

Node *Encoder::buildTree(std::vector<std::vector<Pixel>> &image)
{

	// frequency std::map
	std::map<int, int> freq;

	// count code occurrences
	for (int h = 0; h < int(image.size()); h++)
	{
		for (int w = 0; w < int(image[h].size()); w++)
		{
			freq[image[h][w].r]++;
			freq[image[h][w].g]++;
			freq[image[h][w].b]++;
		}
	}

	// smallest value on the top to make the lowest branches assigned to the most frequent colors' codes
	std::priority_queue<Node *, std::vector<Node *>, cmp> tree;

	// construct leafs of the tree
	for (std::map<int, int>::iterator it = freq.begin(); it != freq.end(); it++)
	{
		Node *leaf = createNode(it->second, it->first, NULL, NULL);
		tree.push(leaf);
	}

	// build the tree from bottom to top
	while (tree.size() > 1)
	{
		// pick left and right nodes
		Node *node1 = tree.top();
		tree.pop();
		Node *node2 = tree.top();
		tree.pop();

		// -1 means no such code (dummy value), codes in the leafs only
		Node *new_node = createNode(node1->count + node2->count, -1, node1, node2);

		// new parent
		tree.push(new_node);
	}

	// return root of the tree
	if (tree.size())
	{
		return tree.top();
	}
	else
	{
		exit(-1);
		return tree.top();
	}
}

// checks if node is leaf
bool Encoder::isLeaf(Node *node)
{
	return (node->left == NULL && node->right == NULL);
}

// pre-order traversing
void Encoder::traverse(Node *node)
{
	//std::cout << node->code << ' ' << node->count << std::endl;
	if (isLeaf(node))
		return;
	traverse(node->left);
	traverse(node->right);
}

void Encoder::binaryRepForCode(std::string binStr, Node *node, bool printMap)
{
	if (isLeaf(node))
	{
		if(printMap) fileTXT << node->code << " " << binStr << std::endl;

		// save the result
		color2bin[node->code] = binStr;
		bin2color[binStr] = node->code;
		return;
	}

	// traverse left
	binaryRepForCode(binStr + "0", node->left, printMap);
	// traverse right
	binaryRepForCode(binStr + "1", node->right, printMap);
}

void Encoder::clear(Node * node)
{
	if(isLeaf(node)){
		delete node;
		return;
	}
	clear(node->left);
	clear(node->right);
	delete node;
}


Node * Encoder::getRoot(){
	return root;	
}

Encoder::~Encoder()
{
	fileTXT.close();
	clear(root);
}