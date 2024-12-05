#ifndef REGULATORPID_H
#define REGULATORPID_H

#include "io.h"

class RegulatorPID : public IO
{

public:
    explicit RegulatorPID(double Kp = 0.0, double Ki = 0.0, double Kd = 0.0, double maxUchyby = 0.0);

    double symuluj(double aktualnaWartosc) override;

    void ustawKp(double nowaWartosc);             // Ustawienie wzmocnienia proporcjonalnego
    void ustawKi(double nowaWartosc);             // Ustawienie wzmocnienia całkującego
    void ustawKd(double nowaWartosc);             // Ustawienie wzmocnienia różniczkującego
    void ustawAntiWindup(double nowaWartosc);     // Ustawienie wartości max dla anti-windup
    void wlaczAntiWindup(bool wlaczony);          // Włączenie lub wyłączenie filtra anti-windup

    double getWartoscProporcjonalna();  // Wartość P
    double getWartoscCalkujaca();       // Wartość I
    double getWartoscRozniczkujaca();   // Wartość D

private:
    double kP;                  // Wzmocnienie proporcjonalne
    double tI;                  // Wzmocnienie całkujące
    double tD;                  // Wzmocnienie różniczkujące
    double maxUchyby;           // Maksymalna wartość uchybu (do anti-windup)
    double sumaUchybow;         // Suma uchybów
    double uchybPoprzedni;      // Poprzedni uchyb
    bool antiWindupWlaczony;    // Flaga włączająca/wyłączająca anti-windup
};

#endif // REGULATORPID_H
