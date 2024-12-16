#include <QApplication>
#include "simulator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Simulator simulation;

    simulation.run();

    return app.exec();
}
