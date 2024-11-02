#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "loopsystem.h"
#include "filemanager.h"
#include "gui.h"

class Simulator
{
public:
    Simulator(int argc, char *argv[]);

    void run();

    GUI& getGUI();
private:
    LoopSystem m_loop;
    FileManager m_fileManager;
    GUI m_gui;
};

#endif // SIMULATOR_H
