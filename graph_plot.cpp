#include "graph_plot.h"

QwtBeginner::QwtBeginner(QWidget *parent)
    : QWidget(parent)
{
    funPlot = new QwtPlot;

    funPlot->setTitle("Function");
    QPen myPen = QPen(Qt::blue);
    myPen.setWidth(2);
    myPen.setCapStyle(Qt::RoundCap);
    QPen dotPen = QPen(Qt::red);
    dotPen.setWidth(5);
    dotPen.setCapStyle(Qt::RoundCap);

    myCurve = new QwtPlotCurve;
    myCurve->setPen(myPen);
    myCurve->attach(funPlot);

    dot = new QwtPlotCurve;
    dot->setPen(dotPen);
    dot->attach(funPlot);
    dot->setStyle(QwtPlotCurve::Dots);

    QHBoxLayout *plotsLayout = new QHBoxLayout;
    plotsLayout->setSpacing(10);
    plotsLayout->addWidget(funPlot);

    QVBoxLayout *widgetLayout = new QVBoxLayout;
    widgetLayout->addLayout(plotsLayout);

    setLayout(widgetLayout);
}

void QwtBeginner::eval(double * X, double * Y, int n, int ** tr,
                       const char* title,double* T,double x,double y,double res_temp)
{
    size=n;
    xval=X;
    yval=Y;
    tnum=size-2;
    triang=tr;
    funPlot->setTitle(title);
    temp=T;
    res=res_temp;

    plot_xy=new double* [2];
    for (int i=0;i<2;i++)
    plot_xy[i]=new double [tnum*4];
    xd=new double [tnum*4+1];
    yd=new double [tnum*4+1];
    xd[0]=x;
    yd[0]=y;

    for (int i=0,k=0;i<tnum;i++)
    {
        plot_xy[0][k]=xval[triang[i][0]];
        plot_xy[1][k++]=yval[triang[i][0]];
        plot_xy[0][k]=xval[triang[i][1]];
        plot_xy[1][k++]=yval[triang[i][1]];
        plot_xy[0][k]=xval[triang[i][2]];
        plot_xy[1][k++]=yval[triang[i][2]];
        plot_xy[0][k]=xval[triang[i][0]];
        plot_xy[1][k++]=yval[triang[i][0]];
    }

    for (int i=1;i<tnum*4+1;i++)
    {
        xd[i]=plot_xy[0][i];
        yd[i]=plot_xy[1][i];
    }

    myCurve->setSamples(plot_xy[0],  plot_xy[1], tnum*4);

    dot->setSamples(xd,yd,tnum*4+1);

    markers = new QwtPlotMarker[size+1];

    QString qstr;
    QwtText texts;
    std::string s1;

    for (int i=0;i<size;i++)
    {
        std::ostringstream oss;
        oss << temp[i];
        s1=oss.str();
        qstr=s1.data();
        texts.setText(qstr);
        markers[i].setXValue(xval[i]);
        markers[i].setYValue(yval[i]);
        markers[i].setLabel(texts);
        markers[i].attach(funPlot);
        if (xval[i]<0.3)
        {
            markers[i].setLabelAlignment(Qt::AlignRight);
        }
        else markers[i].setLabelAlignment(Qt::AlignLeft);
    }

    std::ostringstream oss;
    oss << res;
    s1=oss.str();
    qstr=s1.data();
    texts.setText(qstr);
    markers[size].setXValue(xd[0]);
    markers[size].setYValue(yd[0]);
    markers[size].setLabel(texts);
    markers[size].attach(funPlot);
    if (xd[0]<0.3)
    {
        markers[size].setLabelAlignment(Qt::AlignRight);
    }
    else markers[size].setLabelAlignment(Qt::AlignLeft);

    funPlot->replot();
}
