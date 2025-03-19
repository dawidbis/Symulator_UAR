#include "arx_model.h"
#include "qdebug.h"

ARX_Model::ARX_Model(const std::vector<double>& coefficientsA, const std::vector<double>& coefficientsB, int delay, double standardDeviation, QObject *parent)
    : QObject{parent}, currentOutput(0.0), coefficientsA(coefficientsA), coefficientsB(coefficientsB), stepIndex(0), standardDeviation(standardDeviation), disturbance(0.0)
{
    if (delay < 1) {
        this->delay = 1;
    } else {
        this->delay = delay;
    }

    inputBuffer.assign(coefficientsB.size() - 1, 0.0);
    outputBuffer.assign(coefficientsA.size(), 0.0);
    delayBuffer.assign(this->delay, 0.0);
}

ARX_Model::~ARX_Model() {}

double ARX_Model::simulate(double input)
{
    delayBuffer.push_front(input);
    double delayedInput = delayBuffer.back();
    delayBuffer.pop_back();

    inputBuffer.push_front(delayedInput);

    double partA = std::inner_product(coefficientsB.begin(), coefficientsB.end(), inputBuffer.begin(), 0.0);
    double partB = std::inner_product(coefficientsA.begin(), coefficientsA.end(), outputBuffer.begin(), 0.0);

    inputBuffer.pop_back();

    currentOutput = (partA - partB) + generateDisturbance();

    outputBuffer.push_front(currentOutput);
    outputBuffer.pop_back();

    stepIndex++;

    emit sendObjectValueToChart(currentOutput);

    return currentOutput;
}


void ARX_Model::setModelParameters(std::vector<double> coefficientsA, std::vector<double> coefficientsB, double disturbance, int delay)
{
    this->coefficientsA = coefficientsA;
    this->coefficientsB = coefficientsB;
    this->standardDeviation = disturbance;
    this->delay = delay;
    changeDelayBuffer();
    updateBuffers();
}

void ARX_Model::changeDelayBuffer()
{
    if (this->delay > delayBuffer.size()) {
        double lastValue = delayBuffer.empty() ? 0.0 : delayBuffer.back();
        delayBuffer.insert(delayBuffer.begin(), this->delay - delayBuffer.size(), lastValue);
    } else if (this->delay < delayBuffer.size()) {
        delayBuffer.erase(delayBuffer.begin(), delayBuffer.begin() + (delayBuffer.size() - this->delay));
    }
}

void ARX_Model::updateBuffers()
{
    size_t newInputBufferSize = coefficientsB.size() - 1;
    size_t newOutputBufferSize = coefficientsA.size();

    if (inputBuffer.size() < newInputBufferSize) {
        double lastInputValue = inputBuffer.empty() ? 0.0 : inputBuffer.back();
        inputBuffer.resize(newInputBufferSize, lastInputValue);
    } else if (inputBuffer.size() > newInputBufferSize) {
        inputBuffer.resize(newInputBufferSize);
    }

    if (outputBuffer.size() < newOutputBufferSize) {
        double lastOutputValue = outputBuffer.empty() ? 0.0 : outputBuffer.back();
        outputBuffer.resize(newOutputBufferSize, lastOutputValue);
    } else if (outputBuffer.size() > newOutputBufferSize) {
        outputBuffer.resize(newOutputBufferSize);
    }
}

double ARX_Model::generateDisturbance()
{
    // ***** Generowanie zakłócenia *****
    double mean = 0.0;
    std::random_device randomDevice;
    std::mt19937 randomGenerator;
    randomGenerator.seed(randomDevice());
    std::normal_distribution<double> gaussianDistribution(mean, standardDeviation);
    return gaussianDistribution(randomGenerator);
}
