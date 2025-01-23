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
    antiWindupWlaczony(true)  // Domyślnie filtr anti-windup jest włączony
{
}

double RegulatorPID::symuluj(double wejscie)
{
    double wyjscie = 0.0;

    // Obliczanie części proporcjonalnej
    uP = kP * wejscie;

    // Obliczanie części całkującej
    uI = 0.0;
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
    uD = 0.0;
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

void RegulatorPID::setMaxUchyby(double maxUchyby) {
    this->maxUchyby = maxUchyby;
}

void RegulatorPID::setSumaUchybow(double sumaUchybow) {
    this->sumaUchybow = sumaUchybow;
}

void RegulatorPID::setUchybPoprzedni(double uchybPoprzedni) {
    this->uchybPoprzedni = uchybPoprzedni;
}

void RegulatorPID::wlaczAntiWindup(bool wlaczony)
{
    this->antiWindupWlaczony = wlaczony;
}

double RegulatorPID::getWartoscProporcjonalna()
{
    return uP;
}

double RegulatorPID::getWartoscCalkujaca()
{
    return uI;
}

double RegulatorPID::getWartoscRozniczkujaca()
{
    return uD;
}
double RegulatorPID::getMaxUchyby() const {
    return maxUchyby;
}

double RegulatorPID::getSumaUchybow() const {
    return sumaUchybow;
}

double RegulatorPID::getUchybPoprzedni() const {
    return uchybPoprzedni;
}

bool RegulatorPID::isAntiWindupWlaczony() const {
    return antiWindupWlaczony;
}
