#ifndef REGULATORPID_H
#define REGULATORPID_H

#include "io.h"
#include <QObject>

class RegulatorPID : public IO
{
    Q_OBJECT

public:
    explicit RegulatorPID(double Kp = 0.0, double Ki = 0.0, double Kd = 0.0, QObject *parent = nullptr);

    double symuluj(double aktualnaWartosc) override;
signals:
    void wartoscProporcjonalna(double wartoscP);  // Wartość P
    void wartoscCalkujaca(double wartoscI);       // Wartość I
    void wartoscRozniczkujaca(double wartoscD);   // Wartość D

private:
    double Kp;  // Wzmocnienie proporcjonalne
    double Ki;  // Wzmocnienie całkujące
    double Kd;  // Wzmocnienie różniczkujące

    double poprzedniUchyb;
    double sumaUchybu;
    double poprzedniaWartosc;
};

#endif // REGULATORPID_H
