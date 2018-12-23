#pragma once
#include <map>
#include <iostream>

using std::string;
using std::map;
using std::cout;
class MinHeapNode {

public:
    int m_data;   //0-255
    bool isLeaf;
    MinHeapNode* left;
    MinHeapNode* right;
    MinHeapNode()
    {
        m_data = -1;
        left = right = 0;
        isLeaf = true;
    };
    MinHeapNode(int data)
    {
        m_data=data;
        left=right=0;
        isLeaf = true;
    };
    ~MinHeapNode();
};

class MinHeap {

public:
    MinHeapNode* m_root;

    MinHeap();
    void GenerateMinHeap(map<int,string>);
    void Traverse(MinHeapNode*);
    void Get(string);
    MinHeapNode* GetRoot();
    ~MinHeap();
};



// TODO:

// Func: get instructions to fill 2D array
