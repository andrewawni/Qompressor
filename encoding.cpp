#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

//Previous vs Current SIZE
int prv, cur;

// RGB colors' codes
struct Pixel
{
	int r, g, b;
};

// Node in the binary tree with 2 values and 2 children
struct Node
{
	int count;
	int code;
	struct Node *left;
	struct Node *right;
};

// compare function to sort in the priority queue
struct cmp
{
	bool operator()(Node *const &p1, Node *const &p2)
	{
		return p1->count > p2->count;
	}
};

// stores final results
std::map<int, std::string> color2bin;
std::map<std::string, int> bin2color;

std::vector<std::vector<Pixel>> readImage(cv::Mat image)
{

	std::vector<std::vector<Pixel>> ret(image.rows, std::vector<Pixel>(image.cols));
	for (int h = 0; h < image.rows; h++)
	{
		for (int w = 0; w < image.cols; w++)
		{
			ret[h][w].r = (int)image.at<cv::Vec3b>(h, w)[2];
			ret[h][w].g = (int)image.at<cv::Vec3b>(h, w)[1];
			ret[h][w].b = (int)image.at<cv::Vec3b>(h, w)[0];
		}
	}

	return ret;
}

// node constructor function
Node *createNode(int count, int code, Node *left, Node *right)
{
	Node *node = (Node *)malloc(sizeof(struct Node));
	node->count = count;
	node->code = code;
	node->left = left;
	node->right = right;
	return node;
}

Node *buildTree(std::vector<std::vector<Pixel>> &image)
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
bool isLeaf(Node *node)
{
	return (node->left == NULL && node->right == NULL);
}

// pre-order traversing
void traverse(Node *node)
{
	//std::cout << node->code << ' ' << node->count << std::endl;
	if (isLeaf(node))
		return;
	traverse(node->left);
	traverse(node->right);
}

void binaryRepForCode(std::string binStr, Node *node)
{
	if (isLeaf(node))
	{
		//std::cout << node->code << " -> " << binStr << "    (" << node->count << ")" << std::endl;

		std::cout << node->code << " " << binStr << std::endl;

		cur += int(binStr.size()) * node->count;

		// save the result
		color2bin[node->code] = binStr;
		bin2color[binStr] = node->code;
		return;
	}

	// traverse left
	binaryRepForCode(binStr + "0", node->left);
	// traverse right
	binaryRepForCode(binStr + "1", node->right);
}

int main(int argc, char **argv)
{
	freopen("encoded_image.txt", "w", stdout);

	cv::Mat file;
	std::string fileName = "/home/aboamra/Downloads/WhatsApp Image 2018-12-09 at 12.52.03 AM.jpeg";

	file = cv::imread(fileName, CV_LOAD_IMAGE_COLOR);

	if (!file.data)
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	std::vector<std::vector<Pixel>> image = readImage(file);

	Node *root = buildTree(image);
	binaryRepForCode("", root);

	for (int h = 0; h < int(image.size()); h++)
	{
		for (int w = 0; w < int(image[h].size()); w++)
		{
			//std::cout << image[h][w].r << "\t" << image[h][w].g << "\t" << image[h][w].b << "\t|\t";
			std::cout << color2bin[image[h][w].r];
			std::cout << color2bin[image[h][w].g];
			std::cout << color2bin[image[h][w].b];
			std::cout << (w == int(image[h].size()) - 1 ? "\n" : "");
		}
	}

	//ANDREW'S PART
	// cv::Mat grHistogram(file.rows, file.cols, CV_8UC3, cv::Scalar(0, 0, 0));

	// for (int i = 0; i < file.rows; i++)
	// {
	// 	for (int j = 0; j < file.cols; j++)
	// 	{
	// 		grHistogram.at<cv::Vec3b>(i, j)[0] = file.at<cv::Vec3b>(i, j)[0];
	// 		grHistogram.at<cv::Vec3b>(i, j)[1] = file.at<cv::Vec3b>(i, j)[1];
	// 		grHistogram.at<cv::Vec3b>(i, j)[2] = file.at<cv::Vec3b>(i, j)[2];
	// 	}
	// }

	// cv::imwrite("Test.jpg", grHistogram);

	// cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	// cv::imshow("Display window", grHistogram);
	// cv::waitKey(0);
	return 0;
}

/*
follow this:
http://www.codebind.com/linux-tutorials/install-opencv-3-2-ubuntu-18-04-lts-linux/

except cmake line
https://linuxize.com/post/how-to-install-opencv-on-ubuntu-18-04/


runned:
sudo apt-get install libopencv-dev

--------------------------------------------------------------------------------
g++ test.cpp -o output `pkg-config --cflags --libs opencv`

./output

*/
