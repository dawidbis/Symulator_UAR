#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#include "regulatorpid.h"
#include "modelarx.h"
#include <QObject>
#include <QTimer>

class LoopSystem : public QObject
{
    Q_OBJECT

public:
    explicit LoopSystem(QObject *parent = nullptr);
    ~LoopSystem();

    void startLoop();         // Rozpoczyna pętlę ujemnego sprzężenia zwrotnego
    void stopLoop();          // Zatrzymuje pętlę

public slots:
    void executeLoop();       // Funkcja cyklicznie wywoływana przez timer

private:
    RegulatorPID regulator;   // Instancja regulatora PID
    ModelARX model;           // Instancja modelu ARX
    QTimer *timer;            // Timer do cyklicznego wywoływania pętli
    bool isLoopRunning;       // Flaga kontrolująca stan pętli
};

#endif // LOOPSYSTEM_H
