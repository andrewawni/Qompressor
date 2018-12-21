#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_actionOpen_File_triggered();

  void on_actionAbout_triggered();

  void on_actionCredits_triggered();

  void on_actionContribute_triggered();

  void on_actionForce_Dark_Theme_triggered();

  void on_actionExtract_File_triggered();

  void on_actionView_File_triggered();

private:
  Ui::MainWindow *ui;
  void loadFileIntoLabel(QString filepath);
};

#endif // MAINWINDOW_H
