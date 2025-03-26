#include "filemanager.h"

FileManager::FileManager(QObject *parent)
    : QObject{parent}
{}

void FileManager::setLoop(LoopSystem *loop)
{
    this->loop = loop;
}

void FileManager::saveInstance(QString filePath)
{
    qDebug() << "Saving instance to file: " << filePath;

    if (!loop) {
        qWarning() << "LoopSystem pointer is null.";
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for writing: " << file.errorString();
        return;
    }

    QTextStream out(&file);

    // Save ARX Model data
    ARX_Model& model = loop->getObject();
    out << "ARX Model Coefficients A: ";
    for (const auto& value : model.getCoefficientsA()) {
        out << value << " ";
    }
    out << "\n";

    out << "ARX Model Coefficients B: ";
    for (const auto& value : model.getCoefficientsB()) {
        out << value << " ";
    }
    out << "\n";

    out << "ARX Model Delay Buffer: ";
    for (const auto& value : model.getDelayBuffer()) {
        out << value << " ";
    }
    out << "\n";

    out << "ARX Model Input Buffer: ";
    for (const auto& value : model.getInputBuffer()) {
        out << value << " ";
    }
    out << "\n";

    out << "ARX Model Output Buffer: ";
    for (const auto& value : model.getOutputBuffer()) {
        out << value << " ";
    }
    out << "\n";

    out << "ARX Model Delay: " << model.getDelay() << "\n";
    out << "ARX Model Step Index: " << model.getStepIndex() << "\n";
    out << "ARX Model Standard Deviation: " << model.getStandardDeviation() << "\n";

    // Save PID Regulator data
    PID_Regulator& regulator = loop->getRegulator();
    out << "PID Regulator kP: " << regulator.getKP() << "\n";
    out << "PID Regulator tI: " << regulator.getTI() << "\n";
    out << "PID Regulator tD: " << regulator.getTD() << "\n";
    out << "PID Regulator Min Value: " << regulator.getMinValue() << "\n";
    out << "PID Regulator Max Value: " << regulator.getMaxValue() << "\n";
    out << "PID Regulator Deviation Sum: " << regulator.getDeviationSum() << "\n";
    out << "PID Regulator Last Deviation: " << regulator.getLastDeviation() << "\n";
    out << "PID Regulator Anti-Windup ON: " << (regulator.isAntiWindupON() ? "true" : "false") << "\n";
    out << "PID Regulator Alternate Integral: " <<(regulator.isAltIntegralON() ? "true" : "false")<<"\n";

    // Save Generator data
    Generator& generator = loop->getGenerator();
    out << "Generator SignalType: " << static_cast<int>(generator.getSignalType()) << "\n";
    out << "Generator Amplitude: " << generator.getAmplitude() << "\n";
    out << "Generator Period: " << generator.getPeriod() << "\n";
    out << "Generator Frequency: " << generator.getFrequency() << "\n";
    out << "Generator Time Passed: " << generator.getTimePassed() << "\n";
    out << "Generator Signal Fill: " << generator.getSignalFill() << "\n";
    out << "Generator Constant Component: " << generator.getConstComponent() << "\n";

    file.close();
    qDebug() << "Data saved to " + filePath;
}

void FileManager::loadInstance(QString filePath)
{
    qDebug() << "Loading instance from file: " << filePath;

    if (!loop) {
        qWarning() << "LoopSystem pointer is null.";
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open file for reading: " << file.errorString();
        return;
    }

    QTextStream in(&file);
    QString line;

    std::vector<double> coefficientsA, coefficientsB;
    std::deque<double> delayBuffer, inputBuffer, outputBuffer;
    int delay = 0, stepIndex = 0;
    double standardDeviation = 0.0;
    double kP = 0, tI = 0, tD = 0, minValue = 0, maxValue = 0, deviationSum = 0, lastDeviation = 0;
    bool antiWindupON = false;
    bool altIntegralON = false;

    SignalType signalType = SignalType::RECTANGULAR; // Default value
    double amplitude = 1.0, period = 2.0, frequency = 1.0, timePassed = 0.0, signalFill = 0.5, constantComponent = 0.0;

    while (!in.atEnd()) {
        line = in.readLine();
        QTextStream lineStream(&line);

        if (line.startsWith("ARX Model Coefficients A:")) {
            line.remove("ARX Model Coefficients A:");
            QTextStream lineStream(&line);
            double value;
            while (!lineStream.atEnd()) {
                lineStream >> value;
                if (lineStream.status() != QTextStream::Ok) break;
                coefficientsA.push_back(value);
                qDebug() << QString::number(value) + " TUTAJ";
            }
        }
        else if (line.startsWith("ARX Model Coefficients B:")) {
            line.remove("ARX Model Coefficients B:");
            QTextStream lineStream(&line);
            double value;
            while (!lineStream.atEnd()) {
                lineStream >> value;
                if (lineStream.status() != QTextStream::Ok) break;
                coefficientsB.push_back(value);
                qDebug() << QString::number(value);
            }
        }
        else if (line.startsWith("ARX Model Delay Buffer:")) {
            line.remove("ARX Model Delay Buffer:");
            QTextStream lineStream(&line);
            double value;
            while (!lineStream.atEnd()) {
                lineStream >> value;
                if (lineStream.status() != QTextStream::Ok) break;
                delayBuffer.push_back(value);
                qDebug() << QString::number(value);
            }
        }
        else if (line.startsWith("ARX Model Input Buffer:")) {
            line.remove("ARX Model Input Buffer:");
            QTextStream lineStream(&line);
            double value;
            while (!lineStream.atEnd()) {
                lineStream >> value;
                if (lineStream.status() != QTextStream::Ok) break;
                inputBuffer.push_back(value);
                qDebug() << QString::number(value);
            }
        }
        else if (line.startsWith("ARX Model Output Buffer:")) {
            line.remove("ARX Model Output Buffer:");
            QTextStream lineStream(&line);
            double value;
            while (!lineStream.atEnd()) {
                lineStream >> value;
                if (lineStream.status() != QTextStream::Ok) break;
                outputBuffer.push_back(value);
                qDebug() << QString::number(value);
            }
        }
        else if (line.startsWith("ARX Model Delay:")) {
            line.remove("ARX Model Delay:");
            QTextStream lineStream(&line);
            lineStream >> delay;
            qDebug() << "ARX Model Delay:" << QString::number(delay);
        }
        else if (line.startsWith("ARX Model Step Index:")) {
            line.remove("ARX Model Step Index:");
            QTextStream lineStream(&line);
            lineStream >> stepIndex;
            qDebug() << "ARX Model Step Index:" << QString::number(stepIndex);
        }
        else if (line.startsWith("ARX Model Standard Deviation:")) {
            line.remove("ARX Model Standard Deviation:");
            QTextStream lineStream(&line);
            lineStream >> standardDeviation;
            qDebug() << "ARX Model Standard Deviation:" << QString::number(standardDeviation);
        }
        else if (line.startsWith("PID Regulator kP:")) {
            line.remove("PID Regulator kP:");
            QTextStream lineStream(&line);
            lineStream >> kP;
            qDebug() << "PID Regulator kP:" << QString::number(kP);
        }
        else if (line.startsWith("PID Regulator tI:")) {
            line.remove("PID Regulator tI:");
            QTextStream lineStream(&line);
            lineStream >> tI;
            qDebug() << "PID Regulator tI:" << QString::number(tI);
        }
        else if (line.startsWith("PID Regulator tD:")) {
            line.remove("PID Regulator tD:");
            QTextStream lineStream(&line);
            lineStream >> tD;
            qDebug() << "PID Regulator tD:" << QString::number(tD);
        }
        else if (line.startsWith("PID Regulator Min Value:")) {
            line.remove("PID Regulator Min Value:");
            QTextStream lineStream(&line);
            lineStream >> minValue;
            qDebug() << "PID Regulator Min Value:" << QString::number(minValue);
        }
        else if (line.startsWith("PID Regulator Max Value:")) {
            line.remove("PID Regulator Max Value:");
            QTextStream lineStream(&line);
            lineStream >> maxValue;
            qDebug() << "PID Regulator Max Value:" << QString::number(maxValue);
        }
        else if (line.startsWith("PID Regulator Deviation Sum:")) {
            line.remove("PID Regulator Deviation Sum:");
            QTextStream lineStream(&line);
            lineStream >> deviationSum;
            qDebug() << "PID Regulator Deviation Sum:" << QString::number(deviationSum);
        }
        else if (line.startsWith("PID Regulator Last Deviation:")) {
            line.remove("PID Regulator Last Deviation:");
            QTextStream lineStream(&line);
            lineStream >> lastDeviation;
            qDebug() << "PID Regulator Last Deviation:" << QString::number(lastDeviation);
        }
        else if (line.startsWith("PID Regulator Anti-Windup ON:")) {
            line.remove("PID Regulator Anti-Windup ON:");
            line = line.trimmed().toLower();
            antiWindupON = (line == "true");
            qDebug() << "PID Regulator Anti-Windup ON:" << (antiWindupON ? "true" : "false");
        }
        else if (line.startsWith("PID Regulator Alternate Integral:")) {
            line.remove("PID Regulator Alternate Integral:");
            line = line.trimmed().toLower();
            altIntegralON = (line == "true");
            qDebug() << "PID Regulator Alternate Integral: " << (altIntegralON ? "true" : "false");
        }
        else if (line.startsWith("Generator SignalType:")) {
            line.remove("Generator SignalType:");
            QTextStream lineStream(&line);
            int signalTypeInt;
            lineStream >> signalTypeInt;
            signalType = static_cast<SignalType>(signalTypeInt);
            qDebug() << "Generator SignalType:" << signalTypeInt;
        }
        else if (line.startsWith("Generator Amplitude:")) {
            line.remove("Generator Amplitude:");
            QTextStream lineStream(&line);
            lineStream >> amplitude;
            qDebug() << "Generator Amplitude:" << QString::number(amplitude);
        }
        else if (line.startsWith("Generator Period:")) {
            line.remove("Generator Period:");
            QTextStream lineStream(&line);
            lineStream >> period;
            qDebug() << "Generator Period:" << QString::number(period);
        }
        else if (line.startsWith("Generator Frequency:")) {
            line.remove("Generator Frequency:");
            QTextStream lineStream(&line);
            lineStream >> frequency;
            qDebug() << "Generator Frequency:" << QString::number(frequency);
        }
        else if (line.startsWith("Generator Time Passed:")) {
            line.remove("Generator Time Passed:");
            QTextStream lineStream(&line);
            lineStream >> timePassed;
            qDebug() << "Generator Time Passed:" << QString::number(timePassed);
        }
        else if (line.startsWith("Generator Signal Fill:")) {
            line.remove("Generator Signal Fill:");
            QTextStream lineStream(&line);
            lineStream >> signalFill;
            qDebug() << "Generator Signal Fill:" << QString::number(constantComponent);
        }
        else if (line.startsWith("Generator Constant Component:")) {
            line.remove("Generator Constant Component:");
            QTextStream lineStream(&line);
            lineStream >> constantComponent;
            qDebug() << "Generator Constant Component:" << QString::number(constantComponent);
        }
    }

    file.close();
    qDebug() << "File loaded successfully.";

    ARX_Model& model = loop->getObject();
    model.setModelParameters(coefficientsA, coefficientsB, standardDeviation, delay);

    PID_Regulator& regulator = loop->getRegulator();
    regulator.setPIDParameters(kP, tI, tD, minValue, maxValue, antiWindupON,altIntegralON);

    Generator& generator = loop->getGenerator();
    generator.setGeneratorParameters(signalType, amplitude, period, frequency, signalFill, constantComponent);

    generator.setTimePassed(timePassed);

    qDebug() << "Data applied to LoopSystem.";


    emit loop->updateGUIControls(signalType, amplitude, period, frequency, kP, tI, tD, antiWindupON, minValue, maxValue, delay,
        coefficientsA, coefficientsB, standardDeviation, signalFill, constantComponent);
}
