#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updatePlot(double value);
    void updatePID(double value);

private:
    double x;
    double xBuffer;
    double y;
    double yBuffer;

    void updateX();
    void updateY();

    Ui::MainWindow *ui;
    QLineSeries* series;
    QLineSeries* series2;
    QChart* chart;
};
#endif // MAINWINDOW_H
