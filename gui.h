#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QMessageBox>
#include <QFileDialog>
#include "SignalType.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GUI;
}
QT_END_NAMESPACE

struct Chart {
    std::vector<QLineSeries*> series;
    QChart* chart;
    QChartView* view;
    double x, minX, maxX, minY, maxY;
};

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

public slots:
    void updateGeneratorSerie(double value);

    void updatePIDSeries(double uP, double uI, double uD, double output);

    void updateObjectSerie(double value);

    void updateDeviationSerie(double value);

    void updateGUIControls(SignalType s, double a, double per, double f, double p, double i,
                           double d, bool win, double min, double max, int k, std::vector<double> ca, std::vector<double> cb,
                           double z, double sf, double cc);

signals:
    void newGeneratorParameters(SignalType signalType, double amplitude, double period, double frequency, double signalFill, double constComponent);
    void newPIDParameters(double kP, double tI, double tD, double minValue, double maxValue, bool antiWindupON,bool altIntegralON);
    void newModelParameters(std::vector<double> coefficientsA, std::vector<double> coefficientsB, double disturbance, int delay);
    void startStop();
    void setLoop(double interval);
    void resetIntegral();
    void resetDeriative();
    void resetGeneratorTime();
    void saveSimulation(QString filePath);
    void loadSimulation(QString filePath);

private slots:
    void on_setGenerator_clicked();
    void on_setRegulator_clicked();
    void on_setModel_clicked();
    void on_startStop_clicked();
    void on_reset_clicked();
    void on_setLoop_clicked();
    void on_reset_Integral_clicked();
    void on_reset_Derative_clicked();
    void on_show_uP_clicked();
    void on_show_uI_clicked();
    void on_show_uD_clicked();
    void on_save_clicked();
    void on_load_clicked();


private:
    Ui::GUI *ui;
    Dialog *m_window;

    // funkcje do samych wykresów ;D
    void initCharts();
    void configureChart(QChart* chart,const QString xLabel,const QString yLabel);
    void appendData(Chart& chart, int seriesIndex, double value);
    void updateXAxisRange(Chart& chart);
    void removeExcessPoints(QLineSeries* series, int maxPoints);
    void incrementXAxis(Chart& chart);
    void adjustYAxisRange(Chart& chart);

    std::vector<double> convertToVector(const QString& input);

    double interval;

    std::map<QString, Chart> charts;
};
#endif // GUI_H
