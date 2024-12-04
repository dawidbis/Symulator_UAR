#ifndef MODELARX_H
#define MODELARX_H

#include "io.h"
#include <QObject>

class ModelARX : public IO
{
    Q_OBJECT
public:
    explicit ModelARX(QObject *parent = nullptr);
    virtual ~ModelARX();  // Wirtualny destruktor

    double symuluj(double aktualnaWartosc) override;
};

#endif // MODELARX_H
