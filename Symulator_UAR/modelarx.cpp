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
double ModelARX::getARX(){
    return 0.0;
}
