#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr);

    bool zapisz(const QString &sciezka, const QString &dane);  // Zapisuje dane do pliku
    QString wczytaj(const QString &sciezka);                   // Wczytuje dane z pliku

public slots:
    void zapiszSlot(const QString &sciezka, const QString &dane);  // Publiczny slot do wywołania zapisu z GUI

protected slots:
    void sprawdzStan();  // Sprawdza stan wewnętrzny obiektu (np. czy bufor nie jest pusty)

private slots:
    void wyczyscBufor();  // Prywatny slot do wewnętrznego czyszczenia bufora

signals:
    void zapisZakonczony(bool sukces);  // Sygnał informujący o zakończeniu zapisu
    void bladPliku(const QString &komunikat);  // Sygnał informujący o błędzie operacji na pliku

private:
    QString bufor;  // Bufor, w którym przechowywane są dane do zapisania
};

#endif // FILEMANAGER_H
