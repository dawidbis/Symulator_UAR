#include "generator.h"

// Konstruktor klasy Generator
Generator::Generator(double amplituda, double okres, double czestotliwosc, TypSygnalu typSygnalu)
    : IO(), A(amplituda), T(okres), f(czestotliwosc), czas(0.0), typ(typSygnalu)
{
}

// Ustawienie parametrów sygnału (amplituda, okres, częstotliwość)
void Generator::ustawParametry(double amplituda, double okres, double czestotliwosc, TypSygnalu typSygnalu)
{
    A = amplituda;
    T = okres;
    f = czestotliwosc;
    typ = typSygnalu;
}

// Generowanie odpowiedniego sygnału w zależności od typu
double Generator::symuluj(double dt)
{
    zaktualizujCzas(dt);

    switch (typ)
    {
    case TypSygnalu::SKOK_JEDNOSTKOWY:
        return skokJednostkowy(); break;
    case TypSygnalu::SINUSOIDALNY:
        return sinusoidalny(); break;
    case TypSygnalu::PROSTOKATNY:
        return prostokątny(); break;
    default:
        return 0.0;
    }
}

// Generowanie skoku jednostkowego (wartość 0 do czasu T, potem 1)
double Generator::skokJednostkowy()
{
    if (czas < T)
        return 0.0;
    else
        return A;
}

// Generowanie sygnału sinusoidalnego
double Generator::sinusoidalny()
{
    return A * std::sin(2 * M_PI * f * czas);  // f = częstotliwość w Hz
}

// Generowanie sygnału prostokątnego
double Generator::prostokątny()
{
    return (static_cast<int>(czas / T) % 2 == 0) ? A : 0.0;
}

// Zaktualizowanie czasu o dt (wywoływane w każdej iteracji symulacji)
void Generator::zaktualizujCzas(double dt)
{
    czas += dt;
}
