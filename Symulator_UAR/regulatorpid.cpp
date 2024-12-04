#include "RegulatorPID.h"
#include <QDebug>

// Konstruktor klasy RegulatorPID
RegulatorPID::RegulatorPID(double Kp, double Ki, double Kd, QObject *parent)
    : IO(parent),  // Przekazujemy parent do klasy bazowej QObject
    Kp(Kp),
    Ki(Ki),
    Kd(Kd),
    poprzedniUchyb(0.0),
    sumaUchybu(0.0),
    poprzedniaWartosc(0.0)
{
}

// Implementacja metody symuluj – oblicza nowe wyjście PID
double RegulatorPID::symuluj(double aktualnaWartosc)
{
    // Obliczamy uchyb (różnicę między poprzednią wartością a aktualną)
    double uchyb = poprzedniaWartosc - aktualnaWartosc;

    // Obliczamy składniki regulatora PID
    double P = Kp * uchyb;                    // Składnik proporcjonalny
    double I = Ki * sumaUchybu;               // Składnik całkujący
    double D = Kd * (uchyb - poprzedniUchyb); // Składnik różniczkujący

    // Sumaryczne wyjście regulatora PID
    double wyjscie = P + I + D;

    // Emitowanie sygnałów informujących o poszczególnych wartościach
    emit wartoscProporcjonalna(P);            // Sygnał o wartości proporcjonalnej
    emit wartoscCalkujaca(I);                 // Sygnał o wartości całkującej
    emit wartoscRozniczkujaca(D);             // Sygnał o wartości różniczkującej
    emit sygnalIO(wyjscie);                   // Sygnał o zmianie wyjścia

    // Aktualizacja stanu regulatora
    poprzedniUchyb = uchyb;                   // Zapamiętujemy bieżący uchyb jako poprzedni
    sumaUchybu += uchyb;                      // Sumujemy uchyb dla składnika całkującego
    poprzedniaWartosc = aktualnaWartosc;      // Aktualizujemy poprzednią wartość procesu

    // Zwracamy nową wartość wyjścia regulatora PID
    return wyjscie;
}
