#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#include "regulatorpid.h"
#include "modelarx.h"
#include "filemanager.h"
#include "generator.h"
#include <QObject>
#include <QTimer>

class loopsystem : public QObject
{
    Q_OBJECT
public:
    explicit loopsystem(QObject *parent = nullptr);

    void startLoop();
    void stopLoop();

    void emitSignals();
    void emitSave();
    void emitLoad();

    bool getLoopState();
    double getWartoscARX();
    double getWartoscPID();
    double getInterval();

    ModelARX& getModel();
    RegulatorPID& getRegulator();
    Generator& getGenerator();

    ~loopsystem();

    void setLoopState(bool state);
    void setWartoscARX(double arx);
    void setWartoscPID(double pid);
    void setInterval(double interv);
signals:
    void emitP(double value);
    void emitI(double value);
    void emitD(double value);
    void emitARX(double value);
    void saveFile();
    void loadFile();

public slots:
    void symuluj();

private:
    bool loopState;
    double wartoscARX;
    double wartoscPID;
    double uchyb;
    double interval;

    ModelARX model;
    RegulatorPID regulator;
    Generator generator;
    QTimer* timer;
    FileManager* manager;

};

#endif // LOOPSYSTEM_H
