#ifndef IO_H
#define IO_H

#include <QObject>

class IO : public QObject
{
    Q_OBJECT  // Makro Qt wymagane do obsługi sygnałów i slotów

public:
    explicit IO(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~IO() {}

    // Metoda czysto wirtualna, implementowana przez klasy pochodne
    virtual double symuluj(double aktualnaWartosc) = 0;

signals:
    void sygnalIO(double wyjscie);  // Przykładowy sygnał dla klas pochodnych
};

#endif // IO_H
