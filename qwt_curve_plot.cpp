#include "qwt_curve_plot.h"

void qwt_curve_plot::eval(double* X,double* Y,int n,int** tr)
{
    size=n;
    xval=X;
    yval=Y;
    tnum=size-2;
    triang=tr;

    plot_xy=new double* [2];
    for (int i=0;i<2;i++)
        plot_xy[i]=new double [tnum*4];

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

    xMap.setScaleInterval(-1, 6);
    yMap.setScaleInterval(-1, 6);

    setFrameStyle(QFrame::Box|QFrame::Raised);
    setLineWidth(2);
    setMidLineWidth(3);
    //enableAxis(QwtPlot::yRight);
    //d_curves.legendItem()->
    d_plot=new QwtPlot(this);
    //setCentralWidget(d_plot);
    mY = new QwtPlotMarker();
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(0.0);
    mY->attach(d_plot);

    d_curves.setPen(QColor(Qt::darkBlue));
    d_curves.setStyle(QwtPlotCurve::Lines);
    d_curves.setRawSamples(plot_xy[0], plot_xy[1], tnum*4);
    d_curves.attach(d_plot);

    d_grid.enableX(true);
    d_grid.enableY(true);

    d_plot->setAxisTitle(QwtPlot::xBottom, "X");
    d_plot->setAxisScale(QwtPlot::xBottom, -1, 10);

    d_plot->setAxisTitle(QwtPlot::yLeft, "Y");
    d_plot->setAxisScale(QwtPlot::yLeft, -1, 10);


       // finally, refresh the plot
    d_plot->replot();
}

void qwt_curve_plot::shiftDown(QRect &rect, int offset) const
{
    rect.translate(0, offset);
}

void qwt_curve_plot::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setClipRect(contentsRect());
    drawContents(&painter);
}

void qwt_curve_plot::drawContents(QPainter *painter)
{
    int deltay;
    QRect r = contentsRect();
    deltay = r.height();
    r.setHeight(deltay);

    xMap.setPaintInterval(r.left(), r.right());
    yMap.setPaintInterval(r.top(), r.bottom());

    painter->setRenderHint(QPainter::Antialiasing,
         d_curves.testRenderHint(QwtPlotItem::RenderAntialiased) );
    d_curves.draw(painter, xMap, yMap, r);

    shiftDown(r, deltay);

    painter->setRenderHint(QPainter::Antialiasing,d_grid.testRenderHint(QwtPlotItem::RenderAntialiased));
    d_grid.draw(painter, xMap, yMap, r);
    shiftDown(r, deltay);
}
