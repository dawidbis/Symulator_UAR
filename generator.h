#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include "IO.h"
#include "SignalType.h"

class Generator : public QObject, public IO
{
    Q_OBJECT

public:
    explicit Generator(SignalType signalType = SignalType::RECTANGULAR, double amplitude = 1.0, double period = 2.0, double frequency = 1.0, QObject* parent = nullptr);

    virtual ~Generator();

    double simulate(double input) override;

    void resetGeneratorTime();

    SignalType& getSignalType(){return signalType;}
    double& getAmplitude(){return amplitude;}
    double& getPeriod(){return period;}
    double& getFrequency(){return frequency;}
    double& getTimePassed(){return timePassed;}

    void setTimePassed(double timePassed){this->timePassed = timePassed;}
public slots:
    void setGeneratorParameters(SignalType signalType, double amplitude, double period, double frequency);

signals:
    void sendDataToChart(double value);

private:
    SignalType signalType;
    double amplitude;
    double period;
    double frequency;
    double timePassed;
    double output;

    double jumpUnit();
    double sinusoidal();
    double rectangular();

    void updateTime(double dt);
};

#endif // GENERATOR_H
