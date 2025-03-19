#ifndef SIMULATION_H
#define SIMULATION_H

#include "gui.h"
#include "loopsystem.h"
#include "filemanager.h"
#include <QObject>
#include <QPushButton>

class Simulation
{
public:
    Simulation();

    void run();
private:
    GUI gui;
    LoopSystem loop;
    FileManager fileManager;

    void init();

    void connectBackendFrontend();
};

#endif // SIMULATION_H
