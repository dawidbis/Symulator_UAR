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

void ModelARX::setMYi(double yi) {
    this->m_yi = yi;
}

void ModelARX::setMA(const std::vector<double>& A) {
    this->m_A = A;
}

void ModelARX::setMB(const std::vector<double>& B) {
    this->m_B = B;
}

void ModelARX::setOpoznienieBufor(const std::deque<double>& opoznienieBufor) {
    this->m_opoznienieBufor = opoznienieBufor;
}

void ModelARX::setBuforWej(const std::deque<double>& buforWej) {
    this->m_buforWej = buforWej;
}

void ModelARX::setBuforWyj(const std::deque<double>& buforWyj) {
    this->m_buforWyj = buforWyj;
}

void ModelARX::setMK(int k) {
    this->m_k = k;
}

void ModelARX::setMI(int i) {
    this->m_i = i;
}

void ModelARX::setMZi(double zi) {
    this->m_zi = zi;
}
