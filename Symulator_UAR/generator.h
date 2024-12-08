#ifndef GENERATOR_H
#define GENERATOR_H

#include <cmath>

enum class TypSygnalu
{
    SKOK_JEDNOSTKOWY = 0,
    SINUSOIDALNY = 1,
    PROSTOKATNY = 2
};

class Generator
{
public:
    // Konstruktor klasy
    Generator(double amplituda = 1.0, double okres = 1.0, double czestotliwosc = 1.0, TypSygnalu typSygnalu = TypSygnalu::SKOK_JEDNOSTKOWY);

    // Metoda ustawiająca amplitudę, okres i częstotliwość sygnału
    void ustawParametry(double amplituda, double okres, double czestotliwosc, TypSygnalu typSygnalu);

    // Funkcja zwracająca wartość sygnału na podstawie zadanego typu sygnału
    double generujSygnał();

    // Funkcja aktualizująca czas (wywoływana np. w symulacji)
    void zaktualizujCzas(double dt);

private:
    double A;    // Amplituda sygnału
    double T;    // Okres sygnału
    double f;    // Częstotliwość sygnału
    double czas; // Zmienna do śledzenia czasu
    TypSygnalu typ;

    // Generowanie skoku jednostkowego (wartość 0 do czasu T, potem 1)
    double skokJednostkowy();

    // Generowanie sygnału sinusoidalnego
    double sinusoidalny();

    // Generowanie sygnału prostokątnego
    double prostokątny();
};

#endif // GENERATOR_H
