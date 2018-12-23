#pragma once
#include <stdio.h>

class BitmapImageGenerator
{
    const int bytesPerPixel = 3;  /// red -> green -> blue
    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;

  public:
    BitmapImageGenerator();
    void generateBitmapImage(unsigned char *image, int height, int width, char *imageFileName);
    unsigned char *createBitmapFileHeader(int height, int width);
    unsigned char *createBitmapInfoHeader(int height, int width);

    ~BitmapImageGenerator();
};



//TODO
// add constructor(height, width, filename)
// add function that filles image array from file




//MAIN ex:

    // BitmapImageGenerator gen;
    // int height = 1024;
    // int width = 920;
    // unsigned char image[height][width][3];
    // char *imageFileName = "test22.bmp";

    // int i, j;
    // int x = 0;
    // for (i = 0; i < height; i++)
    // {
    //     for (j = 0; j < width; j++)
    //     {

    //         image[i][j][2] = (unsigned char)( (x^0)*100) ;             ///red
    //         image[i][j][1] = (unsigned char)( (x^1)*100);              ///green
    //         image[i][j][0] = (unsigned char)( (x^2)*100);              ///blue   
    //     }
    //     x = (x+1)%3;
    // }
    // gen.generateBitmapImage((unsigned char *)image, height, width, imageFileName);