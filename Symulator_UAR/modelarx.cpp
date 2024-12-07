#include "modelarx.h"

// Konstruktor klasy ModelARX
ModelARX::ModelARX()
    : IO()
{
}

// Destruktor wirtualny
ModelARX::~ModelARX()
{
    // Możesz dodać tutaj jakiekolwiek czyszczenie zasobów, jeśli jest to konieczne
}

// Implementacja funkcji symuluj
double ModelARX::symuluj(double aktualnaWartosc)
{
    // Przykładowa implementacja
    return aktualnaWartosc * 1.0;  // Wstaw swoją logikę
}

double ModelARX::getMYi() const {
    return m_yi;
}

std::vector<double> ModelARX::getMA() const {
    return m_A;
}

std::vector<double> ModelARX::getMB() const {
    return m_B;
}

std::deque<double> ModelARX::getOpoznienieBufor() const {
    return m_opoznienieBufor;
}

std::deque<double> ModelARX::getBuforWej() const {
    return m_buforWej;
}

std::deque<double>ModelARX:: getBuforWyj() const {
    return m_buforWyj;
}

int ModelARX::getMK() const {
    return m_k;
}

int ModelARX::getMI() const {
    return m_i;
}

double ModelARX::getMZi() const {
    return m_zi;
}
