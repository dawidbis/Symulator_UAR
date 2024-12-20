#include "filemanager.h"
#include "loopsystem.h"


FileManager::FileManager(QObject *parent,loopsystem* loopSystemLS)
{
    loopSystem=loopSystemLS;
}



void FileManager::saveInstance() {
    if (!loopSystem) {
        qWarning() << "LoopSystem nie istnieje.";
        return;
    }

    QFile file("loopSystemInstance.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie udalo sie otworzyc pliku: " << file.errorString();
        return;
    }

    QTextStream out(&file);


    out << "LoopSystem Data:\n";
    out << "loopState: " << (loopSystem->getLoopState() ? "true" : "false") << "\n";
    out << "wartoscARX: " << loopSystem->getWartoscARX() << "\n";
    out << "wartoscPID: " << loopSystem->getWartoscPID() << "\n\n";


    const ModelARX& model = loopSystem->getModel();
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


    RegulatorPID& regulator = loopSystem->getRegulator();
    out << "PID Data:\n";
    out << "kP: " << regulator.getWartoscProporcjonalna() << "\n";
    out << "tI: " << regulator.getWartoscCalkujaca() << "\n";
    out << "tD: " << regulator.getWartoscRozniczkujaca() << "\n";
    out << "maxUchyby: " << regulator.getMaxUchyby() << "\n";
    out << "sumaUchybow: " << regulator.getSumaUchybow() << "\n";
    out << "uchybPoprzedni: " << regulator.getUchybPoprzedni() << "\n";
    out << "antiWindupWlaczony: " << (regulator.isAntiWindupWlaczony() ? "true" : "false") << "\n";

    file.close();
    qDebug() << "LoopSystem zapisany do loopSystemInstance.txt";
}


void FileManager::loadInstance()
{
    if (!loopSystem) {
        qWarning() << "LoopSystem nie istnieje.";
        return;
    }

    QFile file("loopSystemInstance.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie udalo sie otworzyc pliku: " << file.errorString();
        return;
    }

    QTextStream in(&file);

    QString line;
    while (!in.atEnd()) {
        line = in.readLine();

        if (line.startsWith("loopState:")) {
            QString value = line.split(":").last().trimmed();
            loopSystem->setLoopState(value == "true");
        } else if (line.startsWith("wartoscARX:")) {
            loopSystem->setWartoscARX(line.split(":").last().toDouble());
        } else if (line.startsWith("wartoscPID:")) {
            loopSystem->setWartoscPID(line.split(":").last().toDouble());
        } else if (line.startsWith("m_yi:")) {
            loopSystem->getModel().setMYi(line.split(":").last().toDouble());
        } else if (line.startsWith("m_A:")) {
            QStringList values = line.split(":").last().trimmed().split(" ");
            std::vector<double> m_A;
            for (const QString& val : values) {
                m_A.push_back(val.toDouble());
            }
            loopSystem->getModel().setMA(m_A);
        } else if (line.startsWith("m_B:")) {
            QStringList values = line.split(":").last().trimmed().split(" ");
            std::vector<double> m_B;
            for (const QString& val : values) {
                m_B.push_back(val.toDouble());
            }
            loopSystem->getModel().setMB(m_B);
        } else if (line.startsWith("m_opoznienieBufor:")) {
            QStringList values = line.split(":").last().trimmed().split(" ");
            std::deque<double> opoznienieBufor;
            for (const QString& val : values) {
                opoznienieBufor.push_back(val.toDouble());
            }
            loopSystem->getModel().setOpoznienieBufor(opoznienieBufor);
        } else if (line.startsWith("m_buforWej:")) {
            QStringList values = line.split(":").last().trimmed().split(" ");
            std::deque<double> buforWej;
            for (const QString& val : values) {
                buforWej.push_back(val.toDouble());
            }
            loopSystem->getModel().setBuforWej(buforWej);
        } else if (line.startsWith("m_buforWyj:")) {
            QStringList values = line.split(":").last().trimmed().split(" ");
            std::deque<double> buforWyj;
            for (const QString& val : values) {
                buforWyj.push_back(val.toDouble());
            }
            loopSystem->getModel().setBuforWyj(buforWyj);
        } else if (line.startsWith("m_k:")) {
            loopSystem->getModel().setMK(line.split(":").last().toInt());
        } else if (line.startsWith("m_i:")) {
            loopSystem->getModel().setMI(line.split(":").last().toInt());
        } else if (line.startsWith("m_zi:")) {
            loopSystem->getModel().setMZi(line.split(":").last().toDouble());
        } else if (line.startsWith("kP:")) {
            loopSystem->getRegulator().ustawKp(line.split(":").last().toDouble());
        } else if (line.startsWith("tI:")) {
            loopSystem->getRegulator().ustawKi(line.split(":").last().toDouble());
        } else if (line.startsWith("tD:")) {
            loopSystem->getRegulator().ustawKd(line.split(":").last().toDouble());
        } else if (line.startsWith("maxUchyby:")) {
            loopSystem->getRegulator().ustawAntiWindup(line.split(":").last().toDouble());
        } else if (line.startsWith("sumaUchybow:")) {
            loopSystem->getRegulator().setSumaUchybow(line.split(":").last().toDouble());
        } else if (line.startsWith("uchybPoprzedni:")) {
            loopSystem->getRegulator().setUchybPoprzedni(line.split(":").last().toDouble());
        } else if (line.startsWith("antiWindupWlaczony:")) {
            QString value = line.split(":").last().trimmed();
            loopSystem->getRegulator().wlaczAntiWindup(value == "true");
        }
    }

    file.close();
    qDebug() << "LoopSystem wczytany z loopSystemInstance.txt";
}

