#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  // Load an application style
  QFile styleFile( ":/qstyle.qss" );
  styleFile.open( QFile::ReadOnly );
  // Apply the loaded stylesheet
  QString style( styleFile.readAll() );
  a.setStyleSheet( style );

  a.setWindowIcon(QIcon(":/images/images/HBStats_Icon_Sfondo.ico"));
  QObject::connect(qApp,SIGNAL(lastWindowClosed()),qApp,SLOT(quit()));
  w.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.size(), qApp->desktop()->availableGeometry()));
  w.showMaximized();


  return a.exec();
}
