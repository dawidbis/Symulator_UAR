#ifndef IO_H
#define IO_H

class IO
{
public:
    IO();
    virtual ~IO();

    virtual double simulate(double input) = 0;

    friend class FileManager;
private:


};

#endif // IO_H
