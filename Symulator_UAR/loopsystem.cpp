#include "loopsystem.h"

LoopSystem::LoopSystem(QObject *parent)
    : QObject(parent),
    regulator(1.0, 0.1, 0.01, 0.0),  // Przykładowe wartości Kp, Ki, Kd
    model(),
    isLoopRunning(false)
{
    // Tworzymy timer i łączymy go z metodą executeLoop
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LoopSystem::executeLoop);
}

LoopSystem::~LoopSystem()
{
    // Nie musimy już ręcznie zwalniać pamięci, ponieważ obiekty są zarządzane przez kompozycję
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
    wyjsciePID = regulator.symuluj(aktualnaWartosc);

    // Symulujemy model ARX
    noweWyjscie = model.symuluj(wyjsciePID);

    emitSignals(); // emitowanie sygnałów do GUI

    aktualnaWartosc = noweWyjscie;  // Aktualizowanie wartości na podstawie wyjścia modelu
}

void LoopSystem::emitSignals()
{
    double proportional = regulator.getWartoscProporcjonalna();
    double integral = regulator.getWartoscCalkujaca();
    double deriative = regulator.getWartoscRozniczkujaca();

    emit emitPIDProportional(proportional);     //
    emit emitPIDIntegral(integral);             //
    emit emitPIDDeriative(deriative);           //
    emit emitPIDOutput(wyjsciePID);             // Emitujemy sygnał z wyjściem regulatora PID
    emit emitModelOutput(noweWyjscie);          // Emitujemy sygnał z wyjściem modelu ARX
}

void LoopSystem::onStopRequested()
{
    stopLoop();  // Zatrzymanie pętli
}

void LoopSystem::onStartRequested()
{
    startLoop();  // Wznowienie pętli
}

void LoopSystem::onSaveRequested()
{

}

void LoopSystem::setFileManager(FileManager* fm)
{
    this->fileManager = fm;
}
