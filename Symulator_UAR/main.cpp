//#include "mainwindow.h" <-- wylaczenie GUI

#include <QApplication>
#include <QDebug>
#include "loopsystem.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Tworzymy obiekt LoopSystem
    LoopSystem loopSystem;

    // Uruchamiamy pętlę sprzężenia zwrotnego
    loopSystem.startLoop();

    // Uruchamiamy główną pętlę aplikacji
    return a.exec();
}
