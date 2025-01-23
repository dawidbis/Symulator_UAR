#ifndef LOOPSYSTEM_H
#define LOOPSYSTEM_H

#pragma once
#include "regulatorpid.h"
#include "modelarx.h"
#include "filemanager.h"
#include "generator.h"
#include "mainwindow.h"
#include <QObject>
#include <QTimer>

class MainWindow;

class loopsystem : public QObject
{
    Q_OBJECT
public:
    explicit loopsystem(QObject *parent = nullptr);

    void startLoop();
    void stopLoop();

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

    void setGUI(MainWindow* gui);
signals:
    void daneDoWykresu_1(const QString& wykresName, const std::vector<double>& dane);
    void daneDoWykresu_2(const QString& wykresName, const std::vector<double>& dane);
    void daneDoWykresu_3(const QString& wykresName, const std::vector<double>& dane);
    void daneDoWykresu_4(const QString& wykresName, const std::vector<double>& dane);
    void saveFile();
    void loadFile();

public slots:
    void symuluj();

private:
    bool loopState;
    double wartoscARX;
    double wartoscPID;
    double wartoscGenerator;
    double uchyb;
    double interval;

    double temp_P, temp_I, temp_D;

    std::vector<double> dane1;
    std::vector<double> dane2;
    std::vector<double> dane3;
    std::vector<double> dane4;

    ModelARX model;
    RegulatorPID regulator;
    Generator generator;
    QTimer* timer;
    FileManager* manager;
    MainWindow* gui;
};

#endif // LOOPSYSTEM_H
