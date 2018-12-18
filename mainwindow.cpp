#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QGraphicsPixmapItem>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->statusBar()->setSizeGripEnabled(false);
  this->setFixedSize(QSize(500, 420));
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::loadFileIntoLabel(QString filePath)
{
  QFile openedFile(filePath);
  openedFile.open(QIODevice::ReadOnly);
  QTextStream textStream(&openedFile);
  QString openedFileContent = textStream.readAll();
  openedFile.close();

  ui->textEdit->setReadOnly(true);
  ui->textEdit->setText(openedFileContent);
}

void MainWindow::on_actionOpen_File_triggered()
{
  QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), "All Files (*.*);;Text Files (*.txt);;Images(*.png *.bmp *.jpg)");
  QMessageBox::information(this, tr("File Path"), filePath);
  MainWindow::loadFileIntoLabel(filePath);
}

void MainWindow::on_actionSave_Compressed_File_triggered()
{
  QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), "All Files (*.*);;Text Files (*.txt);;Images(*.png *.bmp *.jpg)");
  QMessageBox::information(this, tr("File Path"), saveFilePath);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"), "Qompressor is a free and open source file archiving utility that can compress text files and images.\n\nQompressor uses C++ and the Qt graphics framework.");
}

void MainWindow::on_actionCredits_triggered()
{
   QMessageBox::information(this, tr("Credits"), "Ahmed Elmayyah\nAndrew Awni\nAbdulRahman Yousry\nAhmed Abuamra\nAhmed Mahmoud\n\nDS 2018/2019");
}

void MainWindow::on_actionContribute_triggered()
{
  QDesktopServices::openUrl(QUrl("https://github.com/Satharus"));
}


void MainWindow::on_actionForce_Dark_Theme_triggered()
{
      QFile f(":qdarkstyle/style.qss");
      if (!f.exists())
      {
          printf("Unable to set stylesheet, file not found\n");
      }
      else
      {
          f.open(QFile::ReadOnly | QFile::Text);
          QTextStream ts(&f);
          qApp->setStyleSheet(ts.readAll());
      }
}
