#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#include <QObject>
#include <QTimer>
#include "generator.h"
#include "pid_regulator.h"
#include "arx_model.h"

class LoopSystem : public QObject
{
    Q_OBJECT
public:
    LoopSystem(QObject *parent = nullptr);

    // funkcje pętli sprzężenia zwrotnego
    void startLoop();

    // SETTERY
    void setLoopInterval(double miliseconds);

    // GETTERY
    Generator& getGenerator();
    PID_Regulator &getRegulator();
    ARX_Model& getObject();
    double& getLoopInterval(){return this->loopInterval;}

public slots:
    void executeLoop();

signals:
    void updateGUIControls(SignalType s, double a, double per, double f, double p, double i,
                           double d, bool win, double min, double max, int k, std::vector<double> ca, std::vector<double> cb,
                           double z, double sf, double cc);

private:
    void init();

    // funkcje pętli sprzężenia zwrotnego
    void connectLoopSignals();

    // elementy pętli
    Generator generator;
    PID_Regulator regulator;
    ARX_Model object;

    // wartosci
    double wantedValue;
    double objectValue;
    double deviation;
    double PID_ResponseValue;

    // pola dotyczące samego wykonywania pętli
    bool loopRunning;
    double loopInterval;
    QTimer* loopTimer;
};

#endif // LOOPSYSTEM_H
