#include "modelarx.h"
#include <numeric>
#include <random>

// Konstruktor klasy ModelARX
ModelARX::ModelARX(const std::vector<double>& A, const std::vector<double>& B, int k, double stdev)
    : IO(), m_yi(0.0), m_A(A), m_B(B), m_i(0), m_stdev(stdev), m_zi(0.0)
{
    if (k < 1) {
        m_k = 1;  // Ustawiamy minimalne opóźnienie
    }
    else {
        m_k = k;
    }
    m_buforWej.assign((m_B.size()-1), 0.0);
    m_buforWyj.assign(m_A.size(), 0.0);
    m_opoznienieBufor.assign(m_k, 0.0);
}


// Destruktor wirtualny
ModelARX::~ModelARX()
{
    // Możesz dodać tutaj jakiekolwiek czyszczenie zasobów, jeśli jest to konieczne
}

// Implementacja funkcji symuluj
double ModelARX::symuluj(double ui)
{
    // Obsługa opóźnienia transportowego
    m_opoznienieBufor.push_front(ui);
    double ui_opoznione = m_opoznienieBufor.back();
    m_opoznienieBufor.pop_back();

    // Aktualizacja buforu wejsciowego
    m_buforWej.push_front(ui_opoznione); // Dodaj opóźnione u do końca

    // Obliczenie czescA i czescB
    double czescA = std::inner_product(m_B.begin(), m_B.end(), m_buforWej.begin(), 0.0);
    double czescB = std::inner_product(m_A.begin(), m_A.end(), m_buforWyj.begin(), 0.0);

    m_buforWej.pop_back();             // Usuń najstarszy element

    // Obliczenie wyniku wyjścia
    m_yi = (czescA - czescB) + generujZi();

    m_buforWyj.push_front(m_yi);         // Dodaj aktualne wyjście do bufora
    m_buforWyj.pop_back();             // Usuń najstarszy element

    // Inkrementacja numeru kroku
    m_i++;

    return m_yi;
}

// Generowanie zakłócenia
double ModelARX::generujZi()
{
    double mean = 0.0;
    std::random_device srng;
    std::mt19937 rng;
    rng.seed(srng());
    std::normal_distribution<double> gausDist(mean, m_stdev);
    return gausDist(rng);
}

// Akcesory
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

std::deque<double> ModelARX::getBuforWyj() const {
    return m_buforWyj;
}

int ModelARX::getMK() const {
    return m_k;
}

int ModelARX::getMI() const {
    return m_i;
}

double ModelARX::getMStdev() const {
    return m_stdev;
}

double ModelARX::getMZi() const {
    return m_zi;
}

// Settery
void ModelARX::setMYi(double yi) {
    m_yi = yi;
}

void ModelARX::setMA(const std::vector<double>& A) {
    m_A = A;
}

void ModelARX::setA_at(int index, double wartosc) {
    if (index >= 0 && index < m_A.size()) {
        m_A[index] = wartosc;  // Zmiana współczynnika A na nową wartość
    }
}

void ModelARX::setMB(const std::vector<double>& B) {
    m_B = B;
}

void ModelARX::setB_at(int index, double wartosc) {
    if (index >= 0 && index < m_B.size()) {
        m_B[index] = wartosc;  // Zmiana współczynnika B na nową wartość
    }
}

void ModelARX::setOpoznienieBufor(const std::deque<double>& opoznienieBufor) {
    m_opoznienieBufor = opoznienieBufor;
}

void ModelARX::setBuforWej(const std::deque<double>& buforWej) {
    m_buforWej = buforWej;
}

void ModelARX::setBuforWyj(const std::deque<double>& buforWyj) {
    m_buforWyj = buforWyj;
}

void ModelARX::setMK(int k) {
    m_k = k;
}

void ModelARX::setMI(int i) {
    m_i = i;
}

void ModelARX::setMStdev(double stdev)
{
    m_stdev = stdev;
}

void ModelARX::setMZi(double zi) {
    m_zi = zi;
}
