#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QGraphicsPixmapItem>
#include <QTextStream>
#include <QFileInfo>

#include "TextEncoder.h"
#include "TextDecoder.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
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
    string inputFilePath;

    QMessageBox::information(this, tr("Compress File"), "Choose a file to compress");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Compress File"), QDir::homePath(), "All Files (*);;Text Files (*.txt);;Images(*.bmp)");
    if (filePath.size() == 0)
    {
        QMessageBox::information(this, tr("Failed"), "Failed to open file.");
        return;
    }

    QMessageBox::information(this, tr("Successful"), "File opened successfully, please choose where to compress it.");
    inputFilePath = filePath.toStdString();

    Encoder encoder;
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Save Compressed File"), QDir::homePath(), "Compressed Files (*.qmp);;All Files (*)");
    if (saveFilePath.size() == 0)
    {
        QMessageBox::information(this, tr("Failed"), "Failed to save file.");
        return;
    }

    QString extension;
    for (int i = saveFilePath.size() - 1; i > saveFilePath.size() - 5; i--)
        extension += saveFilePath[i];

    if (!(extension == "pmq.")) saveFilePath += ".qmp";

    QMessageBox::information(this, tr("File saved successfully"),"File saved to " + saveFilePath);
    encoder.encodeStringFromFile(inputFilePath, saveFilePath.toStdString());

    QFileInfo input(QString::fromUtf8(inputFilePath.c_str()));
    QFileInfo output(saveFilePath);

    QMessageBox::information(this, tr("Comparison"), "Old File Size:   " + QString::number(input.size()) + " Bytes\nNew File Size:  " + QString::number(output.size()) + " Bytes");
}


void MainWindow::on_actionExtract_File_triggered()
{
    QMessageBox::information(this, tr("Decompress File"), "Choose a compressed file to decompress");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), "Compressed Files (*.qmp);;All Files (*)");
    if (filePath.size() == 0)
    {
        QMessageBox::information(this, tr("Failed"), "Failed to open file.");
        return;
    }

    string inputFilePath;
    QMessageBox::information(this, tr("Successful"), "File opened successfully, please choose where to decompress it.");
    inputFilePath = filePath.toStdString();

    Decoder decoder;
    QString saveFilePath = QFileDialog::getSaveFileName(this, tr("Save Decompressed File"), QDir::homePath(), "All Files (*);;Text Files (*.txt);;Images(*.bmp)");
    if (saveFilePath.size() == 0)
    {
        QMessageBox::information(this, tr("Failed"), "Failed to save file.");
        return;
    }

    QMessageBox::information(this, tr("File saved successfully"),"File saved to " + saveFilePath);
    decoder.decodeTextInFile(inputFilePath, saveFilePath.toStdString());
}

void MainWindow::on_actionView_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("View File"), QDir::homePath(), "All Files (*);;Text Files (*.txt);;Images(*.bmp)");
    MainWindow::loadFileIntoLabel(filePath);
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
  QDesktopServices::openUrl(QUrl("https://github.com/andrewawni/Qompressor"));
}

void MainWindow::on_actionQuit_triggered()
{
  QApplication::quit();
}

void MainWindow::on_actionHelp_2_triggered()
{
    QMessageBox::information(this, tr("How to Use"), "Use the file menu to choose the desired action.");
}

void MainWindow::on_actionClose_Viewed_File_triggered()
{
    ui->textEdit->setText("");
}

void MainWindow::on_actionForce_Dark_Theme_triggered()
{
      QFile f(":qdarkstyle/style.qss");

      if (!f.exists())  printf("Unable to set stylesheet, file not found\n");

      else
      {
          f.open(QFile::ReadOnly | QFile::Text);
          QTextStream ts(&f);
          qApp->setStyleSheet(ts.readAll());
      }
}
