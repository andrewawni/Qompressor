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




