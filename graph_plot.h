#ifndef GRAPH_PLOT_H
#define GRAPH_PLOT_H

#include <QtGui/QtGui>
#include <QApplication>
#include <QString>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_text.h>
#include <iostream>
#include <sstream>
#include <string>

QT_BEGIN_NAMESPACE
class QComboBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QTableWidgetItem;
QT_END_NAMESPACE

class QwtBeginner : public QWidget
{
    Q_OBJECT

public:
    QwtBeginner(QWidget *parent = 0);
    void eval(double*,double*,int,int**,const char*,double* ,double,double,double);

private:
    QwtPlot *funPlot;
    QwtPlotCurve *myCurve;
    QwtPlotCurve *dot;
    QwtPlotMarker *markers;
    int size,**triang,tnum;
    double *xval,*yval,**plot_xy,*temp,*xd,*yd,res;
};

#endif // GRAPH_PLOT_H
