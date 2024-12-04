#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// komentarz 310378
// przykladowe dzialania klasy FileManager wygenerowane przez kolegę ChatGPT
// dobry przykład do naśladowania :)
// jak widać zawiera np. sloty które będzie można wywołać w GUI po wciśnięciu jakiegoś przycisku (wskaźnik do klasy FileManager w GUI -> a więc dostęp do publicznych slotów)
// w klasie FileManager będzie wskaźnik do modelu ARX i PID więc te funkcje są przekombinowae przez czat i nie bedziemy używać Qstring bufor np.
// zamiast tego będziemy pobierać dane dzięki wskaźnikowi do tychże klas i w slocie (w funkcji) pobierać te dane do zapisu :)
// sloty i signaly będą niezbędne w tym projekcie i jest to funkcjonalność backendowa więc niech to tutaj będzie

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
