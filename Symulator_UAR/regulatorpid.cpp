#include "RegulatorPID.h"
#include <QDebug>

// Konstruktor klasy RegulatorPID
RegulatorPID::RegulatorPID(double Kp, double Ki, double Kd, double maxUchyby)
    : IO(),
    kP(Kp),
    tI(Ki),
    tD(Kd),
    maxUchyby(maxUchyby),
    sumaUchybow(0.0),
    uchybPoprzedni(0.0),
    antiWindupWlaczony(false)  // Domyślnie filtr anti-windup jest włączony
{
}

double RegulatorPID::symuluj(double wejscie)
{
    double wyjscie = 0.0;

    // Obliczanie części proporcjonalnej
    double uP = kP * wejscie;

    // Obliczanie części całkującej
    double uI = 0.0;
    if (tI != 0.0) {
        sumaUchybow += wejscie;
        uI = sumaUchybow / tI;

        // Jeśli anti-windup jest włączony, stosujemy maksymalny uchyb
        if (antiWindupWlaczony) {
            if (uI > maxUchyby) uI = maxUchyby;
            else if (uI < -maxUchyby) uI = -maxUchyby;
        }
    }

    // Obliczanie części różniczkującej
    double uD = 0.0;
    if (tD != 0.0) {
        uD = (wejscie - uchybPoprzedni) * tD;
    }

    // Całkowite wyjście regulatora
    wyjscie = uP + uI + uD;

    // Przechowywanie bieżącego uchybu
    uchybPoprzedni = wejscie;

    return wyjscie;
}

void RegulatorPID::ustawKp(double nowaWartosc)
{
    this->kP = nowaWartosc;
}

void RegulatorPID::ustawKi(double nowaWartosc)
{
    this->tI = nowaWartosc;
}

void RegulatorPID::ustawKd(double nowaWartosc)
{
    this->tD = nowaWartosc;
}

void RegulatorPID::ustawAntiWindup(double nowaWartosc)
{
    this->maxUchyby = nowaWartosc;
}

void RegulatorPID::wlaczAntiWindup(bool wlaczony)
{
    this->antiWindupWlaczony = wlaczony;
}

double RegulatorPID::getWartoscProporcjonalna()
{
    return this->kP;
}

double RegulatorPID::getWartoscCalkujaca()
{
    return this->tI;
}

double RegulatorPID::getWartoscRozniczkujaca()
{
    return this->tD;
}
