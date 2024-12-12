#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "loopsystem.h"
#include "filemanager.h"
#include <QDebug>

class Simulator
{
public:

    explicit Simulator();    // Konstruktor
    ~Simulator();            // Destruktor

    void run();
private:
    void init();

    FileManager fileManager; // Instancja FileManager
    loopsystem loopSystem;  // Instancja LoopSystem

};

#endif // SIMULATOR_H
