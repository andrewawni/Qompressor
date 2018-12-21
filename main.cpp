#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

//  Mat image;
//      image = imread("/home/satharus/Desktop/48378634_2539509139410740_8241155214313259008_n.jpg");   // Read the file

//      if(! image.data )                              // Check for invalid input
//      {
//          return -1;
//      }

//      namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//      imshow( "Display window", image );                   // Show our image inside it.

  return a.exec();
}
