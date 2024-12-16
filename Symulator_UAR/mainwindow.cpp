#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    series = new QLineSeries();
    series2 = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->createDefaultAxes();
    chart->axes((Qt::Vertical)).first()->setRange(-2,2);
    chart->axes((Qt::Horizontal)).first()->setRange(0,100);
    chart->setVisible(true);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setVisible(true);

    setCentralWidget(chartView);

    x = 0;
    xBuffer = 100;
    y = 0;
    yBuffer = 1.0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlot(double value)
{
    x += 1;

    if((x + 1) >= xBuffer)
    {
        updateX();
    }

    series->append(x,value);
}

void MainWindow::updateX()
{
    chart->axes((Qt::Horizontal)).first()->setRange(xBuffer,xBuffer + 100);

    xBuffer += 100;
}

void MainWindow::updateY()
{
    chart->axes((Qt::Vertical)).first()->setRange(-1.0,yBuffer + 0.5);

    yBuffer += 0.5;
}

void MainWindow::updatePID(double value)
{
    if((value + 0.5) >= yBuffer)
    {
        updateY();
    }

    series2->append(x, value);
}
