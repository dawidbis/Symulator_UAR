#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#include "regulatorpid.h"
#include "modelarx.h"
#include "filemanager.h"
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

    void setFileManager(FileManager* fm);    //

public slots:
    void executeLoop();       // Funkcja cyklicznie wywoływana przez timer
    void onStopRequested();   // Zatrzymuje pętlę symulacji
    void onStartRequested();  // Wznawia pętlę symulacji
    void onSaveRequested();   // Zapisuje dane symulacji do pliku

signals:
    void emitPIDOutput(double pidOutput);            // Sygnał emitujący wyjście regulatora PID
    void emitPIDProportional(double proportional);   // P
    void emitPIDIntegral(double integral);           // I
    void emitPIDDeriative(double derivative);        // D
    void emitModelOutput(double modelOutput);        // Sygnał emitujący wyjście modelu ARX

private:
    RegulatorPID regulator;   // Instancja regulatora PID
    ModelARX model;           // Instancja modelu ARX
    FileManager* fileManager; //

    double wyjsciePID ;       //
    double noweWyjscie;       //
    QTimer *timer;            // Timer do cyklicznego wywoływania pętli
    bool isLoopRunning;       // Flaga kontrolująca stan pętli

    void emitSignals();
};

#endif // LOOPSYSTEM_H
