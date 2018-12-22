#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}


//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//using namespace cv;



//  Mat image;
//      image = imread("Filpath");   // Read the file

//      if(! image.data )                              // Check for invalid input
//      {
//          return -1;
//      }

//      namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//      imshow( "Display window", image );                   // Show our image inside it.
