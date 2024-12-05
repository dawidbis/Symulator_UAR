#ifndef IO_H
#define IO_H

class IO
{
public:
    explicit IO();
    virtual ~IO() {};

    // Metoda czysto wirtualna, implementowana przez klasy pochodne
    virtual double symuluj(double aktualnaWartosc) = 0;
};

#endif // IO_H
