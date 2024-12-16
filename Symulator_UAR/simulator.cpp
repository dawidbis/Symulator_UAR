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
    gui.show(); // Wyświetlamy główne okno

}
