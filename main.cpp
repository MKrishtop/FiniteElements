#include <QtGui/QApplication>
#include <qwt_plot.h>
#include "mainwindow.h"
#include "FiniteElements.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
