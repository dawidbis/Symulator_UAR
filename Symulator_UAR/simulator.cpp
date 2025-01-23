#include "simulator.h"
#include <QDebug>

// Konstruktor
Simulator::Simulator()
{
    init();
}

// Destruktor
Simulator::~Simulator()
{
    // Automatyczne zarządzanie pamięcią przez QObject
}

// Rozpoczyna symulację
void Simulator::run()
{
    loopSystem.startLoop();  // Uruchomienie pętli
}

void Simulator::init()
{
    loopSystem.setGUI(&gui);
    fileManager.setLoop(&loopSystem);
    gui.setLoop(&loopSystem);
    gui.setManager(&fileManager);
    gui.show(); // Wyświetlamy główne okno

}
