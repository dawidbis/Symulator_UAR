#include "gui.h"
#include "ui_gui.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    initCharts();

    interval = 0.02; // poczatkowo

    this->resize({1530,800});

    qApp->setStyleSheet(R"(
    QWidget {
        background-color: rgb(30, 30, 30); /* Ciemne tło */
        color: white; /* Biały tekst */
    }

    QMainWindow {
        background-color: rgb(20, 20, 20);
    }

    QLabel {
        color: white;
    }

    /* ZIELONY TEKST DLA OKREŚLONYCH LABELI */
    #label, #label_2, #label_3, #label_8, #label_B, #label_Z {
        color: rgb(0, 255, 0); /* Jasnozielony */
        font-weight: bold;
        border: 1px solid rgb(0, 128, 0);
        font-size: 12pt;
    }

    #setRegulator, #setModel, #setLoop, #setGenerator
    {
        background-color:  rgb(0, 128, 0);
    }

    #setRegulator:hover, #setModel:hover, #setLoop:hover, #setGenerator:hover
    {
        background-color:  rgb(0, 255, 0);
    }

    #line{
        background-color:  rgb(0, 128, 0);
    }

    QLineEdit {
        background-color: rgb(50, 50, 50);
        border: 1px solid white;
        color: white;
    }

    QDoubleSpinBox, QSpinBox {
        background-color: rgb(50, 50, 50);
        border: 1px solid white;
        color: white;
    }

    QComboBox {
        background-color: rgb(50, 50, 50);
        border: 1px solid white;
        color: white;
    }

    QMessageBox {
        background-color: rgb(40, 40, 40);
        color: white;
    }

    QChartView {
        background: rgb(0, 0, 0);
    }
)");
}

GUI::~GUI()
{
    delete ui;
}

void GUI::updateGeneratorSerie(double value)
{
    Chart& chart = charts["Zadana/Rzeczywista"];
    appendData(chart, 0, value);
    incrementXAxis(chart);
}

void GUI::updatePIDSeries(double uP, double uI, double uD, double output)
{
    Chart& chart = charts["Sterowanie"];
    appendData(chart, 0, output);
    incrementXAxis(chart);

    Chart& chart2 = charts["Składowe PID"];
    appendData(chart2, 0, uP);
    appendData(chart2, 1, uI);
    appendData(chart2, 2, uD);
    incrementXAxis(chart2);
}

void GUI::updateObjectSerie(double value)
{
    Chart& chart = charts["Zadana/Rzeczywista"];
    appendData(chart, 1, value);
    //incrementXAxis(chart);
}

void GUI::updateDeviationSerie(double value)
{
    Chart& chart = charts["Uchyb"];
    appendData(chart, 0, value);
    incrementXAxis(chart);
}

void GUI::initCharts() {
    charts.clear();

    // Funkcja pomocnicza do tworzenia wykresu
    auto createChart = [this](const QString& chartTitle, int numSeries, const QString& layoutName) {
        Chart chart;
        for (int i = 0; i < numSeries; ++i) {
            chart.series.push_back(new QLineSeries());
        }

        chart.chart = new QChart();
        chart.view = new QChartView(chart.chart);

        for (auto series : chart.series) {
            chart.chart->addSeries(series);
        }

        QLineSeries* staticLine = new QLineSeries();
        staticLine->append(-10, 0);
        staticLine->append(3600, 0);
        QPen pen(Qt::red);
        pen.setStyle(Qt::DashLine);
        staticLine->setPen(pen);
        chart.series.push_back(staticLine);
        chart.chart->addSeries(staticLine);

        chart.chart->createDefaultAxes();
        chart.chart->setTitle(chartTitle);
        chart.chart->axes(Qt::Horizontal).first()->setRange(-10, 0);

        // Ustawienie nazw osi w zależności od tytułu wykresu:
        if (chartTitle == "Zadana/Rzeczywista")
            configureChart(chart.chart, "Czas (s)", "Wartość sygnału");
        else if (chartTitle == "Składowe PID")
            configureChart(chart.chart, "Czas (s)", "Wartości PID");
        else if (chartTitle == "Sterowanie")
            configureChart(chart.chart, "Czas (s)", "Sygnał sterowania");
        else if (chartTitle == "Uchyb")
            configureChart(chart.chart, "Czas (s)", "Uchyb");

        if (layoutName == "Zadana/Rzeczywista") {
            ui->horizontalLayout_4->addWidget(chart.view);
        } else {
            ui->horizontalLayout_3->addWidget(chart.view);
        }

        charts[chartTitle] = chart;
    };

    createChart("Zadana/Rzeczywista", 2, "Zadana/Rzeczywista");
    createChart("Składowe PID", 3, "Składowe PID");
    createChart("Sterowanie", 1, "Sterowanie");
    createChart("Uchyb", 1, "Uchyb");

    charts["Składowe PID"].series[1]->setVisible(false);
    charts["Składowe PID"].series[2]->setVisible(false);
}

void GUI::configureChart(QChart* chart,const QString xLabel,const QString yLabel) {
    chart->setBackgroundBrush(QBrush(Qt::black));
    chart->setTitleBrush(QBrush(Qt::white));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(30, 30, 30));
    palette.setColor(QPalette::WindowText, Qt::white);
    palette.setColor(QPalette::Button, QColor(45, 45, 45));
    chart->setPalette(palette);

    chart->legend()->setVisible(false);

    auto axesX = chart->axes(Qt::Horizontal);
    auto axesY = chart->axes(Qt::Vertical);

    for (auto axis : axesX) {
        axis->setTitleText(xLabel);
        axis->setTitleBrush(QBrush(Qt::white));
        axis->setLabelsBrush(QBrush(Qt::white));
    }

    for (auto axis : axesY) {
        axis->setTitleText(yLabel);
        axis->setTitleBrush(QBrush(Qt::white));
        axis->setLabelsBrush(QBrush(Qt::white));
    }
}

void GUI::incrementXAxis(Chart& chart) {
    chart.x += interval;
    updateXAxisRange(chart);
}

void GUI::adjustYAxisRange(Chart& chart) {
    auto axisY = chart.chart->axes(Qt::Vertical).first();
    axisY->setRange(chart.minY, chart.maxY);
}

void GUI::appendData(Chart& chart, int seriesIndex, double value) {
    chart.series[seriesIndex]->append(chart.x, value);

    removeExcessPoints(chart.series[seriesIndex], 500);

    if (value > chart.maxY) {
        chart.maxY = value;
    }
    if (value < chart.minY) {
        chart.minY = value;
    }

    adjustYAxisRange(chart);
}

void GUI::updateXAxisRange(Chart& chart) {
    const double baseInterval = 0.02; // Minimalny interwał
    const double visibleRangeWidth = 500 * interval; // Dynamiczny zakres na podstawie interwału
    auto axisX = chart.chart->axes(Qt::Horizontal).first();

    if (chart.x > chart.maxX) {
        chart.maxX = chart.x;
    }

    chart.minX = chart.maxX - visibleRangeWidth;
    axisX->setRange(chart.minX, chart.maxX);
}

void GUI::removeExcessPoints(QLineSeries* series, int maxPoints) {
    while (series->count() > maxPoints) {
        series->removePoints(0, 1);
    }
}

void GUI::on_setGenerator_clicked()
{
    bool sin = ui->sinusoidal->isChecked();
    bool rec = ui->rectangular->isChecked();
    bool jum = ui->jumpUnit->isChecked();

    SignalType type;

    if(sin){ type = SignalType::SINUSOIDAL;}
    else if(rec) {type = SignalType::RECTANGULAR;}
    else {type = SignalType::JUMP_UNIT;}

    emit newGeneratorParameters(type, ui->amplitude->value(), ui->period->value(), ui->frequency->value(), ui->doubleSpinBox->value(), ui->doubleSpinBox_2->value());
}


void GUI::on_setRegulator_clicked()
{
    emit newPIDParameters(ui->kP_value->value(), ui->tI_value->value(), ui->tD_value->value(), ui->min_value->value(), ui->max_value->value(), ui->antiWindupON->isChecked(),ui->altIntegralCheck->isChecked());
}


std::vector<double> GUI::convertToVector(const QString& input) {
    std::vector<double> result;
    QStringList elements = input.split(',');

    for (const QString& element : elements) {
        bool ok;
        double value = element.trimmed().toDouble(&ok);
        if (ok) {
            result.push_back(value);
        } else {
            QMessageBox::warning(nullptr, "Błąd konwersji", "Nieprawidłowy format liczby: " + element);
            return {};
        }
    }

    return result;
}

void GUI::on_setModel_clicked()
{
    DialogData data;

    m_window=new Dialog(data, nullptr);
    int result=m_window->exec();

    if(result)
        ui->status->setText("OK");
    else
        ui->status->setText("FAIL");

    std::vector<double> coefficientsA = convertToVector(data.inputA);
    std::vector<double> coefficientsB = convertToVector(data.inputB);

    if (coefficientsA.size()<3 || coefficientsB.size()<3) {
        QMessageBox::information(nullptr,"Za mało współczynników","Podano mniej niż 3 współczynniki");
        return;
    }

    emit newModelParameters(coefficientsA, coefficientsB, data.disturbance, data.delay);
}


void GUI::on_startStop_clicked()
{
    emit startStop();
}


void GUI::on_reset_clicked()
{
    emit resetGeneratorTime();
    emit resetDeriative();
    emit resetIntegral();

    for (auto& [key, chart] : charts) {
        for (size_t i = 0; i < chart.series.size() - 1; ++i) {
            chart.series[i]->clear();
        }

        // Resetowanie zakresu osi X
        chart.minX = 0; chart.minY = 0;
        chart.maxX = 10; chart.maxY = 0;
        chart.x = 0;
        chart.chart->axisX()->setRange(chart.minX, chart.maxX);
    }
}


void GUI::on_setLoop_clicked()
{
    interval = ui->interval->value();

    emit setLoop(ui->interval->value() * 1000);
}


void GUI::on_reset_Integral_clicked()
{
    emit resetIntegral();
}


void GUI::on_reset_Derative_clicked()
{
    emit resetDeriative();
}


void GUI::on_show_uP_clicked()
{
    charts["Składowe PID"].series[0]->setVisible(true);
    charts["Składowe PID"].series[1]->setVisible(false);
    charts["Składowe PID"].series[2]->setVisible(false);
}


void GUI::on_show_uI_clicked()
{
    charts["Składowe PID"].series[0]->setVisible(false);
    charts["Składowe PID"].series[1]->setVisible(true);
    charts["Składowe PID"].series[2]->setVisible(false);
}


void GUI::on_show_uD_clicked()
{
    charts["Składowe PID"].series[0]->setVisible(false);
    charts["Składowe PID"].series[1]->setVisible(false);
    charts["Składowe PID"].series[2]->setVisible(true);
}


void GUI::on_save_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Zapisz plik"), "", tr("Pliki tekstowe (*.txt);;Wszystkie pliki (*)"));

    if (!filePath.isEmpty()) {

        emit saveSimulation(filePath);
    }
}


void GUI::on_load_clicked()
{
    emit startStop();

    QString filePath = QFileDialog::getOpenFileName(this, tr("Wczytaj plik"), "", tr("Pliki tekstowe (*.txt);;Wszystkie pliki (*)"));

    if (!filePath.isEmpty()) {
        emit loadSimulation(filePath);
    }

    emit startStop();
}

void GUI::updateGUIControls(SignalType s, double a, double per, double f, double p, double i, double d, bool win, double min, double max, int k, std::vector<double> ca, std::vector<double> cb, double z, double sf, double cc)
{
    switch(s){
    case SignalType::JUMP_UNIT: ui->jumpUnit->setChecked(true); break;
    case SignalType::SINUSOIDAL: ui->sinusoidal->setChecked(true); break;
    case SignalType::RECTANGULAR: ui->rectangular->setChecked(true); break;
    }

    ui->amplitude->setValue(a);
    ui->period->setValue(per);
    ui->frequency->setValue(f);
    ui->kP_value->setValue(p);
    ui->tD_value->setValue(d);
    ui->tI_value->setValue(i);
    ui->min_value->setValue(min);
    ui->max_value->setValue(max);
    ui->doubleSpinBox->setValue(sf);
    ui->doubleSpinBox_2->setValue(cc);

    switch(win){
    case true: ui->antiWindupON->setChecked(true);  break;
    case false:  ui->antiWindupON->setChecked(false) ;break;
    }
}

