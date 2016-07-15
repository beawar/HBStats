#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  a.setWindowIcon(QIcon(":/images/images/HBStats_Icon_Sfondo.png"));
  QObject::connect(qApp,SIGNAL(lastWindowClosed()),qApp,SLOT(quit()));
  w.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.size(), qApp->desktop()->availableGeometry()));
  w.showMaximized();

  return a.exec();
}
