#ifndef MODELARX_H
#define MODELARX_H

#include "io.h"
#include <vector>
#include <deque>

class ModelARX : public IO
{
public:
    // Konstruktor
    explicit ModelARX(const std::vector<double>& A, const std::vector<double>& B, int k, double stdev);
    virtual ~ModelARX();  // Wirtualny destruktor
    
    // Metoda symulująca model ARX
     double symuluj(double ui) override;

    // Generowanie zakłócenia
    double generujZi();

    // Akcesory
    double getMYi() const;
    std::vector<double> getMA() const;
    std::vector<double> getMB() const;
    std::deque<double> getOpoznienieBufor() const;
    std::deque<double> getBuforWej() const;
    std::deque<double> getBuforWyj() const;
    int getMK() const;
    int getMI() const;
    double getMStdev() const;
    double getMZi() const;

    // Settery
    void setMYi(double yi);
    void setMA(const std::vector<double>& A);
    void setA_at(int index, double wartosc);
    void setMB(const std::vector<double>& B);
    void setB_at(int index, double wartosc);
    void setOpoznienieBufor(const std::deque<double>& opoznienieBufor);
    void setBuforWej(const std::deque<double>& buforWej);
    void setBuforWyj(const std::deque<double>& buforWyj);
    void setMK(int k);
    void setMI(int i);
    void setMStdev(double stdev);
    void setMZi(double zi);
private:
    double m_yi;                 // Aktualna wartość wyjściowa
    std::vector<double> m_A;     // Współczynniki A
    std::vector<double> m_B;     // Współczynniki B
    std::deque<double> m_opoznienieBufor; // Bufor dla opóźnienia transportowego
    std::deque<double> m_buforWej; // Bufor dla sygnału wejściowego 
    std::deque<double> m_buforWyj; // Bufor dla sygnału wyjściowego
    int m_k;                     // Opóźnienie transportowe (k)
    int m_i;                     // Numer kroku symulacji
    double m_stdev;              // Odchylenie standardowe
    double m_zi;                 // Aktualna wartość zakłócenia
};
#endif // MODELARX_H
