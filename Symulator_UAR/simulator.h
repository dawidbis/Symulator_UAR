#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "loopsystem.h"
#include "filemanager.h"

class Simulator
{
public:
    loopsystem loopSystem;  // Instancja LoopSystem
    explicit Simulator();    // Konstruktor
    ~Simulator();            // Destruktor

    void run();
private:
    void init();

    FileManager fileManager; // Instancja FileManager

};

#endif // SIMULATOR_H
