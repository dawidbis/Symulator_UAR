#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "loopsystem.h"
#include "filemanager.h"

class Simulator
{
public:
    explicit Simulator();    // Konstruktor
    ~Simulator();            // Destruktor

    void run();
private:
    void init();

    LoopSystem loopSystem;  // Instancja LoopSystem
    FileManager fileManager; // Instancja FileManager
};

#endif // SIMULATOR_H
