#ifndef QWT_CURVE_PLOT_H
#define QWT_CURVE_PLOT_H
#include <qwt_scale_map.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_marker.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qcolor.h>
#include <qpainter.h>
#include <qapplication.h>
#include <qframe.h>

class qwt_curve_plot : public QFrame
{
public:
    void eval(double*,double*,int,int**);
    int size,**triang,tnum;
    double *xval,*yval,**plot_xy;
    QwtScaleMap xMap;
    QwtScaleMap yMap;

protected:
    virtual void paintEvent(QPaintEvent *);
    void drawContents(QPainter *p);

private:
    void shiftDown(QRect &rect, int offset) const;

    QwtPlotCurve d_curves;
    QwtPlotGrid d_grid;
    QwtPlot *d_plot;
    QwtPlotMarker *mY;
};

#endif // QWT_CURVE_PLOT_H
