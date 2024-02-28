/*

  requirements:
  gsl, gsl-dev ver. 2.7 (or newer)
  QT ver. 5 (or newer)
  qmake
  make
  nfft3
  nfft3-dev

  istallation:
  qmake
  make


*/

#include "mainwindow.h"
#include <QApplication>

#include "lib/argv_conf2_pw.hpp"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
     //qRegisterMetaType<Worker_data_out>("Worker_data_out");
    MainWindow w;
    w.show();
    return a.exec();
}
