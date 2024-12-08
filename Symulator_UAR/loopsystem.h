#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#include "regulatorpid.h"
#include "modelarx.h"
#include "filemanager.h"
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
    ModelARX& getModel();
    RegulatorPID& getRegulator();
    ~loopsystem();
signals:
    void emitP(double value);
    void emitI(double value);
    void emitD(double value);
    void emitARX(double value);
    void saveFile();
    void loadFile();

public slots:
    void executeLoop();
private:
    bool loopState;
    double wartoscARX;
    double wartoscPID;
    ModelARX model;
    RegulatorPID regulator;
    QTimer* timer;
    FileManager* manager;

};

#endif // LOOPSYSTEM_H
