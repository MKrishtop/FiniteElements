#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    showMaximized();
    A = new FiniteElements;
    B = new QwtBeginner;
    browseButton = createButton(tr("&Open"), SLOT(browse()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(B, 0, 0);
    mainLayout->addWidget(browseButton, 0, 1);

    setLayout(mainLayout);

    setWindowTitle(tr("L4V14_oapsois by Mikhail Krishtop"));
}

void MainWindow::browse()
{
    QString filepath = QFileDialog::getOpenFileName(this,tr("Select input datafile"),QDir::currentPath());

    if (!filepath.isEmpty()) {
        std::string str = std::string(filepath.toAscii().data());
        const char * stuff = str.c_str();
        A->SetFN(stuff);
        A->evaluate();
        B->eval(A->GetXArray(),A->GetYArray(),A->GetN(),A->GetTriangles(),stuff,
                A->GetTArray(),A->GetX(),A->GetY(),A->GetResultTemp());
    }
}

QPushButton *MainWindow::createButton(const QString &text, const char *member)
{
    QPushButton *button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}


