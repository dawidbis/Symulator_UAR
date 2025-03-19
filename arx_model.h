#ifndef ARX_MODEL_H
#define ARX_MODEL_H

#include "io.h"
#include <QObject>
#include <deque>
#include <random>

class ARX_Model : public QObject, public IO
{
    Q_OBJECT
public:
    explicit ARX_Model(const std::vector<double>& coefficientsA, const std::vector<double>& coefficientsB, int delay, double standardDeviation, QObject *parent = nullptr);

    virtual ~ARX_Model();

    double simulate(double input) override;

    const std::vector<double>& getCoefficientsA() const { return coefficientsA; }
    const std::vector<double>& getCoefficientsB() const { return coefficientsB; }
    const std::deque<double>& getDelayBuffer() const { return delayBuffer; }
    const std::deque<double>& getInputBuffer() const { return inputBuffer; }
    const std::deque<double>& getOutputBuffer() const { return outputBuffer; }
    int getDelay() const { return delay; }
    int getStepIndex() const { return stepIndex; }
    double getStandardDeviation() const { return standardDeviation; }
public slots:
    void setModelParameters(std::vector<double> coefficientsA, std::vector<double> coefficientsB, double disturbance, int delay);

signals:
    void sendObjectValueToChart(double value);

private:
    void init();
    void changeDelayBuffer();
    void updateBuffers();

    double currentOutput;
    std::vector<double> coefficientsA;
    std::vector<double> coefficientsB;
    std::deque<double> delayBuffer;
    std::deque<double> inputBuffer;
    std::deque<double> outputBuffer;
    int delay;
    int stepIndex;
    double standardDeviation;
    double disturbance;

    double generateDisturbance();

};
#endif // ARX_MODEL_H
