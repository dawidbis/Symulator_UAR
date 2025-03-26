#ifndef PID_REGULATOR_H
#define PID_REGULATOR_H

#pragma once

#include <QObject>
#include "io.h"

class PID_Regulator : public QObject, public IO
{
    Q_OBJECT
public:
    explicit PID_Regulator(double kP = 0.2, double tI = 3.0, double tD = 0.2, double minValue = -1.0, double maxValue = 1.0 ,bool antiWindupON = true, QObject *parent = nullptr);

    virtual ~PID_Regulator();

    double simulate(double input) override;

    void resetIntegralMemory();
    void resetDeriativeMemory();

    // Gettery
    double getKP() const { return kP; }
    double getTI() const { return tI; }
    double getTD() const { return tD; }
    double getMinValue() const { return minValue; }
    double getMaxValue() const { return maxValue; }
    double getDeviationSum() const { return deviationSum; }
    double getLastDeviation() const { return lastDeviation; }
    bool isAntiWindupON() const { return antiWindupON; }
    bool isAltIntegralON() const {return altIntegralON;}
public slots:
    void setPIDParameters(double kP, double tI, double tD, double minValue, double maxValue, bool antiWindupON,bool altIntegralON);

signals:
    void sendPIDValues(double uP, double uI, double uD, double output);
    void sendDevationValue(double value);

private:
    double kP, tI, tD; // parametry
    double uP, uI, uD; // wartości
    double output;
    double minValue, maxValue;
    double deviationSum;
    double lastDeviation;

    bool antiWindupON;
    bool altIntegralON;
};

#endif // PID_REGULATOR_H
