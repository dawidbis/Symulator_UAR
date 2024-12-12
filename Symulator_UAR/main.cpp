//#include "mainwindow.h" <-- wylaczenie GUI

#include <QApplication>
#include <QDebug>
#include "simulator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Simulator simulation;

    simulation.run();

    // Uruchamiamy główną pętlę aplikacji
    return a.exec();
}
