#include "loopsystem.h"

LoopSystem::LoopSystem(QObject *parent)
    : QObject(parent),
    regulator(new RegulatorPID(1.0, 0.1, 0.01, this)),  // Przykładowe wartości Kp, Ki, Kd
    model(new ModelARX(this)),
    isLoopRunning(false)
{
    // Tworzymy timer i łączymy go z metodą executeLoop
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LoopSystem::executeLoop);
}

LoopSystem::~LoopSystem()
{
    // Zwalniamy pamięć
    delete regulator;
    delete model;
}

void LoopSystem::startLoop()
{
    if (!isLoopRunning) {
        isLoopRunning = true;
        timer->start(100);  // Ustawienie interwału na 100ms (0.1 sekunda)
    }
}

void LoopSystem::stopLoop()
{
    if (isLoopRunning) {
        isLoopRunning = false;
        timer->stop();  // Zatrzymanie timera
    }
}

void LoopSystem::executeLoop()
{
    // Symulacja pętli ujemnego sprzężenia zwrotnego
    static double aktualnaWartosc = 0.0;  // Przykładowa zmienna, którą będziemy przekazywać

    // Symulujemy regulację PID
    double wyjsciePID = regulator->symuluj(aktualnaWartosc);

    // Symulujemy model ARX
    double noweWyjscie = model->symuluj(wyjsciePID);

    // Możesz dodać dalszą logikę, np. zapisywanie wyników
    // Aktualizowanie wartości wyjściowej, lub emitowanie sygnałów

    aktualnaWartosc = noweWyjscie;  // Aktualizowanie wartości na podstawie wyjścia modelu
}
