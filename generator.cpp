#include "generator.h"


Generator::Generator(SignalType signalType, double amplitude, double period, double frequency, double signalFill, QObject* parent)
    : QObject(parent), // Call the QObject base class constructor
    signalType(signalType),
    amplitude(amplitude),
    period(period),
    frequency(frequency),
    timePassed(0.0),
    signalFill(signalFill) {}

Generator::~Generator()
{

}

double Generator::simulate(double input)
{
    updateTime(input);

    switch(signalType){
    case SignalType::JUMP_UNIT:
        output = jumpUnit(); break;
    case SignalType::SINUSOIDAL:
        output = sinusoidal(); break;
    case SignalType:: RECTANGULAR :
        output = rectangular(); break;
    default:
        output = 0.0;
    }

    emit sendDataToChart(output);

    return output;
}

void Generator::resetGeneratorTime()
{
    this->timePassed = 0.0;
}

void Generator::setGeneratorParameters( SignalType signalType, double amplitude, double period, double frequency, double signalFill)
{
    this->signalType = signalType;
    this->amplitude = amplitude;
    this->period = period;
    this->frequency = frequency;
    this->signalFill = signalFill;
}

double Generator::jumpUnit()
{
    if (timePassed < period)
        return 0.0;
    else
        return amplitude;
}

double Generator::sinusoidal()
{
     return amplitude * std::sin(2 * M_PI * frequency * timePassed);
}

double Generator::rectangular()
{
    double phase = fmod(timePassed, period);

    double threshold = signalFill * period;

    return (phase < threshold) ? amplitude : -amplitude;
}

void Generator::updateTime(double dt)
{
    timePassed += (dt/1000.0);
}
