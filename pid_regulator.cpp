#include "pid_regulator.h"
#include <QDebug>

PID_Regulator::PID_Regulator(double kP, double tI , double tD, double minValue , double maxValue, bool antiWindupON , QObject *parent)
    : QObject{parent},
    kP(kP),
    tI(tI),
    tD(tD),
    minValue(minValue),
    maxValue(maxValue),
    antiWindupON(antiWindupON),
    altIntegralON(false)
{}

PID_Regulator::~PID_Regulator()
{

}

double PID_Regulator::simulate(double input)
{
    emit sendDevationValue(input);

    // ***** Obliczanie części proporcjonalnej *****
    uP = kP * input;

    // ***** Obliczanie części całkującej *****
    uI = 0.0;
    if (tI != 0.0) {
        double newDeviationSum = deviationSum + input;
        double maxDeviationSum = maxValue * tI;
        double minDeviationSum = minValue * tI;
        if(altIntegralON){
            newDeviationSum = deviationSum+(input/tI);
            maxDeviationSum = maxValue;
            minDeviationSum = minValue;
        }

        if (antiWindupON) {
            if (output >= maxValue && input > 0) {
                newDeviationSum = deviationSum;
            } else if (output <= minValue && input < 0) {
                newDeviationSum = deviationSum;
            } else {
                if (newDeviationSum > maxDeviationSum) {
                    newDeviationSum = maxDeviationSum;
                } else if (newDeviationSum < minDeviationSum) {
                    newDeviationSum = minDeviationSum;
                }
            }
        }
        if(!altIntegralON){
            deviationSum = newDeviationSum;
            uI = deviationSum / tI;
        }
        else{
            deviationSum = newDeviationSum;
            uI = deviationSum;
        }
    }

    // ***** Obliczanie części różniczkującej *****
    uD = 0.0;
    if (tD != 0.0) {
        uD = (input - lastDeviation) * tD;
    }

    output = uP + uI + uD;

    if (output > maxValue) {
        output = maxValue;
    } else if (output < minValue) {
        output = minValue;
    }

    lastDeviation = input;

    emit sendPIDValues(uP, uI, uD, output);

    return output;
}

void PID_Regulator::resetIntegralMemory()
{
    this->deviationSum = 0.0;
}

void PID_Regulator::resetDeriativeMemory()
{
    this->lastDeviation = 0.0;
}

void PID_Regulator::setPIDParameters(double kP, double tI, double tD, double minValue, double maxValue, bool antiWindupON,bool altIntegralON)
{
    this->kP = kP;
    this->tI = tI;
    this->tD = tD;
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->antiWindupON = antiWindupON;
    this->altIntegralON = altIntegralON;
}
