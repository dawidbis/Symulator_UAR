#ifndef MODELARX_H
#define MODELARX_H

#include "io.h"

class ModelARX : public IO
{
public:
    explicit ModelARX();
    virtual ~ModelARX();  // Wirtualny destruktor

    double symuluj(double aktualnaWartosc) override;
};

#endif // MODELARX_H
