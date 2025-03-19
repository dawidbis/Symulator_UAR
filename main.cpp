#include "simulation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Simulation simulation;

    simulation.run();

    return a.exec();
}
