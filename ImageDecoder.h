#pragma once
#include <map>
#include <vector>
#include <MinHeap.h>
#include "BitmapImageGenerator.h"

using std::map;
using std::string;

class ImageDecoder {

public:
    map<int, string> keyCodeMap;  
    std::vector<int> colorStream;
    unsigned char* image;
    MinHeap* HuffmanTree;

    ImageDecoder();
    void Decode(string, string);
    ~ImageDecoder();
};
