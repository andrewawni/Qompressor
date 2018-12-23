#include <stdio.h>
#include <iostream>
#include <fstream>
#include "ImageDecoder.h"
#include "stringCompressor.cpp"

ImageDecoder::ImageDecoder()
{
    HuffmanTree = new MinHeap();
}

void ImageDecoder::Decode(string inputFileName, string outputFileName)
{
    std::ifstream InputFile(inputFileName);

    int height, width, mapSize;
    if (InputFile.is_open())
    {
        
        InputFile >> height >> width >> mapSize;
        std::cout << "Height: " << height << " " << "Width: " << width << " " << "Number of values: "<< mapSize << '\n';

        while (mapSize--)
        {
            int key;
            string code;

            InputFile >> key >> code;
            // std::cout << key << " " << code << std::endl;
            keyCodeMap[key] = code;
        }
        std::cout << "Map generated\n";

        /*******************************************/

        this->HuffmanTree->GenerateMinHeap(this->keyCodeMap);

        MinHeapNode *root = HuffmanTree->GetRoot();

        
        char c;
        int temp = height;
        int k = 0;
        while (InputFile >> c)
        {
            
            string row = "";
            int numChars;
            string s = "";
            while (c != ' ')
            {
                s.push_back(c);
                InputFile.get(c);
            }

            
            numChars = std::stoi(s);
            
            for (int j = 0; j < numChars; j++)
            {
                InputFile.get(c);
                row.push_back(c);
            }
           
            StringCompressor con;

            row = con.asciitoBinaryStream(row);

            int t = row.size(), i = 0;

            while (t--)
            {
                if (row[i++] == '0')
                    root = root->left;
                else
                    root = root->right;

                if (root->isLeaf)
                {
                    colorStream.push_back(root->m_data);
                    root = HuffmanTree->GetRoot();
                }
            }
        }
        InputFile.close();
    }

    /**************************************************/

    unsigned char image[height][width][3];

    char *imageFileName =  new char[outputFileName.size()+5];
    
    for (int i = 0; i < outputFileName.length(); i++)
    {
        imageFileName[i] = outputFileName[i];
    }
    
    int x = 0;
    for (int i = height - 1; i >= 0; i--)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j][2] = (unsigned char)this->colorStream[x++]; ///red
            image[i][j][1] = (unsigned char)this->colorStream[x++]; ///green
            image[i][j][0] = (unsigned char)this->colorStream[x++]; ///blue
        }
    }

    BitmapImageGenerator gen;
    gen.generateBitmapImage((unsigned char *)image, height, width, imageFileName);
    
    std::cout << "Image decoded!\n";

}


ImageDecoder::~ImageDecoder()
{
}
