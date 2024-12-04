#include "FileManager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{
}

// Implementacja metody zapisu danych do pliku
bool FileManager::zapisz(const QString &sciezka, const QString &dane)
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit bladPliku("Nie można otworzyć pliku do zapisu: " + sciezka);
        return false;
    }

    QTextStream out(&plik);
    out << dane;
    plik.close();
    emit zapisZakonczony(true);  // Emitujemy sygnał o zakończeniu zapisu
    return true;
}

// Implementacja metody odczytu danych z pliku
QString FileManager::wczytaj(const QString &sciezka)
{
    QFile plik(sciezka);
    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text)) {
        emit bladPliku("Nie można otworzyć pliku do odczytu: " + sciezka);
        return QString();
    }

    QTextStream in(&plik);
    QString dane = in.readAll();
    plik.close();
    return dane;
}

// Publiczny slot wywołujący zapis danych do pliku
void FileManager::zapiszSlot(const QString &sciezka, const QString &dane)
{
    bufor = dane;  // Zapisujemy dane do bufora przed zapisem
    if (!zapisz(sciezka, dane)) {
        emit zapisZakonczony(false);
    } else {
        wyczyscBufor();  // Po udanym zapisie czyścimy bufor
    }
}

// Protected slot: Sprawdza, czy bufor jest pusty
void FileManager::sprawdzStan()
{
    if (bufor.isEmpty()) {
        qDebug() << "Bufor jest pusty.";
    } else {
        qDebug() << "Bufor zawiera dane do zapisania.";
    }
}

// Prywatny slot: Wewnętrzna funkcja do czyszczenia bufora
void FileManager::wyczyscBufor()
{
    bufor.clear();
    qDebug() << "Bufor został wyczyszczony.";
}
