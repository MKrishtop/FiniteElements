#-------------------------------------------------
#
# Project created by QtCreator 2011-04-10T20:03:33
#
#-------------------------------------------------
QT       += core gui opengl

TARGET = FiniteElements
TEMPLATE = app

LIBS += -lqwt

INCLUDEPATH += "/usr/include/qwt/"

SOURCES += main.cpp\
        mainwindow.cpp \
    FiniteElements.cpp \
    graph_plot.cpp

HEADERS  += mainwindow.h \
    FiniteElements.h \
    graph_plot.h

#DEPENDPATH += include


#LIBS    +=  -LC:\Qt\2010.05\qt\FiniteElements
#INCLUDEPATH += include
