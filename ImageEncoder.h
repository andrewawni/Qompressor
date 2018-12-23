#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/opencv.hpp"
#include "stringCompressor.h"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <fstream>

using std::map;
using std::string;
using std::vector;
using std::ofstream;

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

class ImageEncoder {
private:
	
    StringCompressor stringCompressor;

    ofstream fileTXT;

    // image pixels RGB in 2D array
    vector<vector<Pixel>> image;

    //Huffman Root Node;
    Node * root;

    // stores final results
    map<int, std::string> color2bin;
    map<std::string, int> bin2color;

    // read image in 2D array
    vector<std::vector<Pixel>> readImage(cv::Mat image);

    // creates new node in the binary huffman tree
    Node * createNode(int count, int code, Node * left, Node * right);
    
    // build huffman tree
    Node * buildTree(vector<vector<Pixel>> &image);

    // checks if node is leaf
    bool isLeaf(Node * node);

    // pre-order traversing
    void traverse(Node * node); 
    
    void clear(Node * node);
public:

    ImageEncoder(string imagePath, string outputPath);

    // 2D image in binary
    void printImageBin();    

    // print 2D image pixels
    void printImagePxl();

    // print 2D image pixels in ascii (compressed)
    void printImageAscii();

    Node * getRoot();

    // dfs on tree to get code's binary representation
    void binaryRepForCode(std::string binStr, Node * node, bool printMap);

    ~ImageEncoder();

};



// TODO: connect between all classes
