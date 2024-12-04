#include "RegulatorPID.h"
#include <QDebug>

// Konstruktor klasy RegulatorPID
RegulatorPID::RegulatorPID(double Kp, double Ki, double Kd, double maxUchyby, QObject *parent)
    : IO(parent),  // Przekazujemy parent do klasy bazowej QObject
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


    emit sygnalIO(wyjscie);
    emit wartoscProporcjonalna(uP);
    emit wartoscCalkujaca(uI);
    emit wartoscRozniczkujaca(uD);

    return wyjscie;
}

// Sloty do ustawiania parametrów regulatora
void RegulatorPID::ustawKp(double nowaWartosc)
{
    kP = nowaWartosc;
}

void RegulatorPID::ustawKi(double nowaWartosc)
{
    tI = nowaWartosc;
}

void RegulatorPID::ustawKd(double nowaWartosc)
{
    tD = nowaWartosc;
}

void RegulatorPID::ustawAntiWindup(double nowaWartosc)
{
    maxUchyby = nowaWartosc;
}

void RegulatorPID::wlaczAntiWindup(bool wlaczony)
{
    antiWindupWlaczony = wlaczony;
}
