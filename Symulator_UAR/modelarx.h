#ifndef MODELARX_H
#define MODELARX_H

#include "io.h"
#include <vector>
#include <deque>

class ModelARX : public IO
{
public:
    explicit ModelARX();
    virtual ~ModelARX();  // Wirtualny destruktor

    double symuluj(double aktualnaWartosc) override;

    std::vector<double> getMA() const;
    double getMYi() const;
    std::vector<double> getMB() const;
    std::deque<double> getOpoznienieBufor() const;
    std::deque<double> getBuforWej() const;
    std::deque<double> getBuforWyj() const;
    int getMK() const;
    int getMI() const;
    double getMZi() const;
    void setMYi(double yi);
    void setMA(const std::vector<double> &A);
    void setMB(const std::vector<double> &B);
    void setOpoznienieBufor(const std::deque<double> &opoznienieBufor);
    void setBuforWej(const std::deque<double> &buforWej);
    void setBuforWyj(const std::deque<double> &buforWyj);
    void setMK(int k);
    void setMI(int i);
    void setMZi(double zi);
private:
double m_yi=1;
std::vector<double> m_A={1,4,8};
std::vector<double> m_B={2,9,0};
std::deque<double> m_opoznienieBufor={999,2,3};
std::deque<double> m_buforWej={1,1,1};
std::deque<double> m_buforWyj={1,2,5};
int m_k=1;
int m_i=1;
double m_zi=1;
};
#endif // MODELARX_H
