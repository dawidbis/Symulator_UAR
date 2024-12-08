#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include <vector>
#include <deque>

class loopsystem;

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr,loopsystem* loopSystem=nullptr);
public slots:
    void saveInstance();
    void loadInstance();

protected slots:


private slots:


signals:


private:
    //Do obsługi instancji dodalem
    loopsystem* loopSystem;
    //ARX
    double m_yiFM;
    std::vector<double> m_AFM;
    std::vector<double> m_BFM;
    std::deque<double> m_opoznienieBuforFM;
    std::deque<double> m_buforWejFM;
    std::deque<double> m_buforWyjFM;
    int m_kFM;
    int m_iFM;
    double m_ziFM;
    //PID
    double kPFM;
    double tIFM;
    double tDFM;
    double maxUchybyFM;
    double sumaUchybowFM;
    double uchybPoprzedniFM;
    bool antiWindupWlaczonyFM;
    //LoopSystem
    bool loopState;
    double wartoscARX;
    double wartoscPID;



};

#endif // FILEMANAGER_H
