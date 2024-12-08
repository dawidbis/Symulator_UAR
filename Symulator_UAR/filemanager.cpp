#include "filemanager.h"
#include "loopsystem.h"


FileManager::FileManager(QObject *parent,loopsystem* loopSystemLS)
{
    loopSystem=loopSystemLS;
}

void FileManager::debugWypiszPlik()
{
    this->
}

void FileManager::saveInstance() {
    if (!loopSystem) {
        qWarning() << "LoopSystem pointer is null. Cannot save instance.";
        return;
    }

    QFile file("loopSystemInstance.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing: " << file.errorString();
        return;
    }

    QTextStream out(&file);

    // Zapis danych z sekcji LoopSystem
    out << "LoopSystem Data:\n";
    out << "loopState: " << (loopSystem->getLoopState() ? "true" : "false") << "\n";
    out << "wartoscARX: " << loopSystem->getWartoscARX() << "\n";
    out << "wartoscPID: " << loopSystem->getWartoscPID() << "\n\n";

    // Zapis danych z modelu ARX
    const ModelARX& model = loopSystem->getModel();  // Pobierz model przez akcesor
    out << "ARX Data:\n";
    out << "m_yi: " << model.getMYi() << "\n";

    out << "m_A: ";
    for (const auto& value : model.getMA()) {
        out << value << " ";
    }
    out << "\n";

    out << "m_B: ";
    for (const auto& value : model.getMB()) {
        out << value << " ";
    }
    out << "\n";

    out << "m_opoznienieBufor: ";
    for (const auto& value : model.getOpoznienieBufor()) {
        out << value << " ";
    }
    out << "\n";

    out << "m_buforWej: ";
    for (const auto& value : model.getBuforWej()) {
        out << value << " ";
    }
    out << "\n";

    out << "m_buforWyj: ";
    for (const auto& value : model.getBuforWyj()) {
        out << value << " ";
    }
    out << "\n";

    out << "m_k: " << model.getMK() << "\n";
    out << "m_i: " << model.getMI() << "\n";
    out << "m_zi: " << model.getMZi() << "\n\n";

    // Zapis danych z regulatora PID
    RegulatorPID& regulator = loopSystem->getRegulator();  // Pobierz regulator przez akcesor
    out << "PID Data:\n";
    out << "kP: " << regulator.getWartoscProporcjonalna() << "\n";
    out << "tI: " << regulator.getWartoscCalkujaca() << "\n";
    out << "tD: " << regulator.getWartoscRozniczkujaca() << "\n";
    out << "maxUchyby: " << regulator.getMaxUchyby() << "\n";
    out << "sumaUchybow: " << regulator.getSumaUchybow() << "\n";
    out << "uchybPoprzedni: " << regulator.getUchybPoprzedni() << "\n";
    out << "antiWindupWlaczony: " << (regulator.isAntiWindupWlaczony() ? "true" : "false") << "\n";

    file.close();
    qDebug() << "LoopSystem instance saved to loopSystemInstance.txt";
}


void FileManager::loadInstance()
{

}

