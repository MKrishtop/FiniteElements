#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QDir>
#include <QtGui/QtGui>
#include <QApplication>
#include <QString>
#include "FiniteElements.h"
#include "graph_plot.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QTableWidget;
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public Q_SLOTS:
    void browse();

private:
    QPushButton *createButton(const QString &text, const char *member);
    QPushButton *browseButton;
    FiniteElements *A;
    QwtBeginner *B;

};

#endif
