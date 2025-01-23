#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QChartView>
#include <QLineSeries>
#include <QChart>
#include <QValueAxis>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QSplitter>
#include <QLineEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDoubleSpinBox>
#include <vector>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>
#include "loopsystem.h"

class loopsystem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Wykres {
    QString nazwa;                            // Nazwa wykresu
    std::vector<QLineSeries*> serie;          // Wektory przechowujące serie
    QChart* chart;                            // Wskaźnik na obiekt QChart
    QChartView* view;                         // Wskaźnik na widok QChartView
    double x, minX, maxX, minY, maxY;         // Zakresy osi X i Y
    int currentSeriesIndex = 0;               // Indeks aktualnie widocznej serii
    bool wyswietlWszystkie = false;           // Flaga: true = wszystkie serie, false = jedna seria
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setLoop(loopsystem* loop);
    void setManager(FileManager* manager);
    void changeSeries(Wykres* wykres, int direction);
    void zmienTryb(Wykres* wykres);
public slots:
    void addDataToChart1(const QString& wykresName, const std::vector<double>& dane);
    void addDataToChart2(const QString& wykresName, const std::vector<double>& dane);
    void addDataToChart3(const QString& wykresName, const std::vector<double>& dane);
    void addDataToChart4(const QString& wykresName, const std::vector<double>& dane);
    void onConfirmButtonClicked();
    void onResetDerivativeMemory();
    void onResetIntegralMemory();
    void onConfirmPIDParameters();
    void onAntiWindupToggled(int state);
    void onConfirmARXParameters();
    void onStartStopSimulation();
    void onSaveSimulation();
    void onLoadSimulation();

private:
    // GENERATOR
    QDoubleSpinBox* amplitudaSpinBox;
    QDoubleSpinBox* okresSpinBox;
    QDoubleSpinBox* czestotliwoscSpinBox;
    QRadioButton* sin;
    QRadioButton* prost;
    QRadioButton* jedn;
    // PID
    QDoubleSpinBox* nastawaPSpinBox;
    QDoubleSpinBox* nastawaISpinBox;
    QDoubleSpinBox* nastawaDSpinBox;
    QDoubleSpinBox* antiWindupMinSpinBox;
    QDoubleSpinBox* antiWindupMaxSpinBox;
    // ARX
    QDoubleSpinBox* aCoefficientSpinBox;
    QDoubleSpinBox* bCoefficientSpinBox;
    QDoubleSpinBox* disturbanceSpinBox;
    // SIMULATION
    QDoubleSpinBox* intervalSpinBox;
    QPushButton* startStopButton;
    QPushButton* resetButton;
    QPushButton* saveButton;
    QPushButton* loadButton;

    void initNazwy();
    void init();
    QWidget* initPanels();
    QWidget* initCharts();
    void updateYAxis(Wykres* wykres);
    void updateXAxis(Wykres* wykres);

    std::map<QString, std::vector<QString>> nazwy;

    std::map<QString, Wykres*> wykresy;

    void add(const QString& wykresName, const std::vector<double>& dane);
    QVBoxLayout* initGeneratorPanel();
    QVBoxLayout*initPIDPanel();
    QVBoxLayout* initARXPanel();
    QVBoxLayout* initSimulationPanel();

    double interval;

    loopsystem* loop;
    FileManager* manager;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
