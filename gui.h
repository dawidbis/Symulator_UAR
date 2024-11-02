#ifndef GUI_H
#define GUI_H

#include "mainwindow.h"
#include <QApplication>

class GUI
{
public:
    GUI(int argc, char *argv[]);

    QApplication& getQApplication();
private:
    QApplication a;
    MainWindow w;
};

#endif // GUI_H
