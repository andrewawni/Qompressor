#include "../include/Decoder.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
Decoder::Decoder()
{
    HuffmanTree = new MinHeap();
}

void Decoder::GenerateMap(string fileName)
{
    cout << fileName << std::endl;
    std::ifstream file(fileName.c_str());
    int key;
    string code;
    if (file.is_open())
    {
        cout << "open\n";
        while (!file.eof())
        {
            file >> key;
            file >> code;
            std::cout << key << " " << code << '\n';
            keyCodeMap[key] = code;
        }
    }
    cout << "close\n";
    file.close();
}
void Decoder::Decode(string fileName)

{
        HuffmanTree->GenerateMinHeap(keyCodeMap);
        std::ifstream file(fileName.c_str());
        string code;
        MinHeapNode* root = HuffmanTree->GetRoot();
        if(file.is_open())
        {
            std::cout << "open2\n";
            while(!file.eof())
            {

            char temp;
            file >> temp;
            code.push_back(temp);
            if(temp == '0')
                root = root->left;
            else
                root = root->right;

            if(root->isLeaf)
                {
                    // cout << root->m_data << std::endl;
                    binaryStream.push_back(root->m_data);
                    code.clear();
                    root = HuffmanTree->GetRoot();
                }
            }
            
        }
        cout << "close2\n";
        file.close();
}

Decoder::~Decoder()
{
}



//int main(int argc, char **argv)
//{
//	freopen("encoded_image.txt", "w", stdout);

	

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
//	return 0;
//}

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
