//#include "mainwindow.h"

#include <QApplication>

#include <QDebug>
#include "RegulatorPID.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Tworzymy instancję regulatora PID
    RegulatorPID regulator(1.0, 0.5, 0.1);

    // Podłączenie sygnału sygnalIO z klasy RegulatorPID do funkcji lambda
    QObject::connect(&regulator, &RegulatorPID::sygnalIO, [](double wartosc) {
        qDebug() << "Sygnał IO odebrany! Aktualna wartość wyjścia PID:" << wartosc;
    });

    // Symulujemy działanie regulatora
    for (int i = 0; i < 25; ++i) {
        double aktualnaWartosc = 10.0 - i;  // Przykładowa zmiana wartości
        regulator.symuluj(aktualnaWartosc);  // Obliczamy nowe wyjście
    }

    return a.exec();
}
