#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initNazwy()
{
    // Inicjalizacja mapy z nazwami wykresów i nazwami ich serii
    nazwy["A) Zadana/Rzeczywista"] = {"Zadana", "Rzeczywista"};
    nazwy["C) Uchyb"] = {"Uchyb"};
    nazwy["B) Składowe PID"] = {"Sterowanie", "P", "I", "D"};
    nazwy["D) Model ARX"] = {"Objekt"};
}

void MainWindow::init()
{
    QWidget* centralWidget = new QWidget();  // Główny widget dla MainWindow
    QHBoxLayout* mainLayout = new QHBoxLayout();  // Układ główny dla paneli i wykresów

    // Dodajemy panele opcji
    QWidget* panelsWidget = initPanels();
    QWidget* chartsWidget = initCharts();

    QSplitter* mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(panelsWidget);
    mainSplitter->addWidget(chartsWidget);

    // Ustawiamy proporcje rozmiaru paneli i wykresów
    QList<int> sizes;
    sizes << 200 << 800;  // Przykładowy podział: 15% panel, 85% wykresy
    mainSplitter->setSizes(sizes);

    mainLayout->addWidget(mainSplitter);

    // Ustawiamy główny layout w centralnym widgetcie
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    //this->resize(1440, 960);
    this->showMaximized();
}

QWidget* MainWindow::initPanels()
{
    QVBoxLayout* panelLayout = new QVBoxLayout();

    // Przykład vectora z nazwami paneli
    std::vector<QString> panelNames = {"Generator", "Regulator PID", "Model ARX", "Symulacja"};

    int panelIndex = 0; // Służy do określenia, który panel inicjalizujemy

    for (const auto& panelName : panelNames)
    {
        QWidget* panel = new QWidget();
        panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        panel->setStyleSheet("background-color: darkgray; border: 1px solid black;");

        QVBoxLayout* panelContentLayout = new QVBoxLayout();

        QLabel* panelTitle = new QLabel(panelName); // Tytuł panelu
        panelTitle->setAlignment(Qt::AlignCenter); // Wyśrodkowanie tekstu
        panelTitle->setStyleSheet("font-weight: bold; font-size: 14px;"); // Styl tytułu
        panelContentLayout->addWidget(panelTitle); // Dodanie tytułu do układu panelu

        // Inicjalizacja odpowiedniego panelu na podstawie nazwy
        if (panelIndex == 0 && panelName == "Generator") {
            panelContentLayout->addLayout(initGeneratorPanel());
        } else if (panelIndex == 1 && panelName == "Regulator PID") {
            panelContentLayout->addLayout(initPIDPanel());
        }
        else if (panelIndex == 2 && panelName == "Model ARX") {
            panelContentLayout->addLayout(initARXPanel());
        }
        else if (panelIndex == 3 && panelName == "Symulacja") {
            panelContentLayout->addLayout(initSimulationPanel());
        }

        panelContentLayout->addStretch(); // Dodanie rozciągania, aby elementy były wyrównane
        panel->setLayout(panelContentLayout);
        panelLayout->addWidget(panel);

        panelIndex++;
    }

    // Tworzymy widget zawierający panele
    QWidget* panelsWidget = new QWidget();
    panelsWidget->setLayout(panelLayout);
    panelsWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    return panelsWidget;
}

QVBoxLayout* MainWindow::initGeneratorPanel()
{
    QVBoxLayout* generatorLayout = new QVBoxLayout();

    // Grupa przycisków radiowych do zmiany typu sygnału
    QButtonGroup* signalTypeGroup = new QButtonGroup(this);
    sin = new QRadioButton("Sinusoidalny");
    prost = new QRadioButton("Prostokątny");
    jedn = new QRadioButton("Trójkątny");

    prost->click();

    signalTypeGroup->addButton(sin);
    signalTypeGroup->addButton(prost);
    signalTypeGroup->addButton(jedn);

    generatorLayout->addWidget(sin);
    generatorLayout->addWidget(prost);
    generatorLayout->addWidget(jedn);

    // Pola wejściowe do parametrów sygnału
    QFormLayout* paramForm = new QFormLayout();

    auto createInputRow = [](QDoubleSpinBox** spinBoxPtr) -> QWidget* {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setRange(0, 100);
        spinBox->setDecimals(3);
        spinBox->setSingleStep(0.1);
        spinBox->setValue(1);

        *spinBoxPtr = spinBox;

        QWidget* rowWidget = new QWidget();
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->addWidget(spinBox);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        return rowWidget;
    };

    // Amplituda
    paramForm->addRow("Amplituda:", createInputRow(&amplitudaSpinBox));

    // Okres
    paramForm->addRow("Okres:", createInputRow(&okresSpinBox));

    // Częstotliwość
    paramForm->addRow("Częstotliwość:", createInputRow(&czestotliwoscSpinBox));

    generatorLayout->addLayout(paramForm);

    // Przycisk zatwierdzający
    QPushButton* confirmButton = new QPushButton("Zatwierdź parametry");
    confirmButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    confirmButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    generatorLayout->addWidget(confirmButton);

    // Połączenie przycisku z metodą ustawiającą parametry
    connect(confirmButton, &QPushButton::clicked, this, &MainWindow::onConfirmButtonClicked);

    okresSpinBox->setValue(2);

    return generatorLayout;
}

QVBoxLayout* MainWindow::initPIDPanel()
{
    QVBoxLayout* pidLayout = new QVBoxLayout();

    // Pola wejściowe do nastaw P, I, D
    QFormLayout* pidForm = new QFormLayout();

    auto createInputRow = [](QDoubleSpinBox** spinBoxPtr) -> QWidget* {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setRange(0, 100);
        spinBox->setDecimals(3);
        spinBox->setSingleStep(0.1);
        spinBox->setValue(1);

        *spinBoxPtr = spinBox;

        QWidget* rowWidget = new QWidget();
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->addWidget(spinBox);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        return rowWidget;
    };

    // Parametry P, I, D
    pidForm->addRow("Nastawa P:", createInputRow(&nastawaPSpinBox));
    pidForm->addRow("Nastawa I:", createInputRow(&nastawaISpinBox));
    pidForm->addRow("Nastawa D:", createInputRow(&nastawaDSpinBox));

    pidLayout->addLayout(pidForm);

    // Anti-Windup
    QCheckBox* antiWindupCheckBox = new QCheckBox("Anti-Windup");
    pidLayout->addWidget(antiWindupCheckBox);

    antiWindupCheckBox->setCheckState(Qt::Checked);

    connect(antiWindupCheckBox, &QCheckBox::stateChanged, this, &MainWindow::onAntiWindupToggled);

    QFormLayout* antiWindupForm = new QFormLayout();
    antiWindupForm->addRow("Min:", createInputRow(&antiWindupMinSpinBox));
    antiWindupForm->addRow("Max:", createInputRow(&antiWindupMaxSpinBox));
    pidLayout->addLayout(antiWindupForm);

    // Przycisk resetujący pamięć różniczkującą
    QPushButton* resetDerivativeButton = new QPushButton("Reset pamięci różniczkującej");
    resetDerivativeButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    pidLayout->addWidget(resetDerivativeButton);
    connect(resetDerivativeButton, &QPushButton::clicked, this, &MainWindow::onResetDerivativeMemory);

    // Przycisk resetujący pamięć całkującą
    QPushButton* resetIntegralButton = new QPushButton("Reset pamięci całkującej");
    resetIntegralButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    pidLayout->addWidget(resetIntegralButton);
    connect(resetIntegralButton, &QPushButton::clicked, this, &MainWindow::onResetIntegralMemory);

    // Przycisk zatwierdzający
    QPushButton* confirmButton = new QPushButton("Zatwierdź parametry");
    confirmButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    confirmButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    pidLayout->addWidget(confirmButton);

    connect(confirmButton, &QPushButton::clicked, this, &MainWindow::onConfirmPIDParameters);

    nastawaPSpinBox->setValue(0.5);
    nastawaISpinBox->setValue(5);
    nastawaDSpinBox->setValue(0.2);
    antiWindupMinSpinBox->setRange(-100, 100);
    antiWindupMinSpinBox->setValue(-1.0);

    return pidLayout;
}

QVBoxLayout* MainWindow::initARXPanel()
{
    QVBoxLayout* arxLayout = new QVBoxLayout();

    // Tytuł panelu

    // Formularz do ustawiania współczynników A i B oraz zakłócenia
    QFormLayout* paramForm = new QFormLayout();

    auto createInputRow = [](QDoubleSpinBox** spinBoxPtr) -> QWidget* {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setRange(-100, 100);
        spinBox->setDecimals(3);
        spinBox->setSingleStep(0.1);
        spinBox->setValue(0);

        *spinBoxPtr = spinBox;

        QWidget* rowWidget = new QWidget();
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->addWidget(spinBox);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        return rowWidget;
    };

    // Współczynnik A
    paramForm->addRow("Współczynnik A:", createInputRow(&aCoefficientSpinBox));

    // Współczynnik B
    paramForm->addRow("Współczynnik B:", createInputRow(&bCoefficientSpinBox));

    // Zakłócenie
    paramForm->addRow("Zakłócenie:", createInputRow(&disturbanceSpinBox));

    arxLayout->addLayout(paramForm);

    // Przycisk zatwierdzający
    QPushButton* confirmButton = new QPushButton("Zatwierdź parametry");
    confirmButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    confirmButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    arxLayout->addWidget(confirmButton);

    // Połączenie przycisku z metodą ustawiającą parametry
    connect(confirmButton, &QPushButton::clicked, this, &MainWindow::onConfirmARXParameters);

    disturbanceSpinBox->setValue(0.01);
    aCoefficientSpinBox->setValue(-0.4);
    bCoefficientSpinBox->setValue(0.6);
    disturbanceSpinBox->setSingleStep(0.01);

    return arxLayout;
}

QVBoxLayout* MainWindow::initSimulationPanel()
{
    QVBoxLayout* simulationLayout = new QVBoxLayout();

    // Panel ustawienia czasu interwału symulacji
    QFormLayout* simulationForm = new QFormLayout();

    auto createIntervalInputRow = [](QDoubleSpinBox** spinBoxPtr) -> QWidget* {
        QDoubleSpinBox* spinBox = new QDoubleSpinBox();
        spinBox->setRange(0.1, 1000);  // Zakres od 0.1 do 1000 sek.
        spinBox->setDecimals(2);  // Dwie liczby po przecinku
        spinBox->setSingleStep(0.1);
        spinBox->setValue(1.0);  // Wartość początkowa 1.0 sekundy

        *spinBoxPtr = spinBox;

        QWidget* rowWidget = new QWidget();
        QHBoxLayout* rowLayout = new QHBoxLayout(rowWidget);
        rowLayout->addWidget(spinBox);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        return rowWidget;
    };

    simulationForm->addRow("Czas interwału (s):", createIntervalInputRow(&intervalSpinBox));
    simulationLayout->addLayout(simulationForm);

    // Przycisk START/STOP
    QPushButton* startStopButton = new QPushButton("STOP");
    startStopButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightgreen; }"
        );
    simulationLayout->addWidget(startStopButton);
    connect(startStopButton, &QPushButton::clicked, this, &MainWindow::onStartStopSimulation);

    // Przycisk RESET
    QPushButton* resetButton = new QPushButton("RESET");
    resetButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightcoral; }"
        );
    simulationLayout->addWidget(resetButton);
    //connect(resetButton, &QPushButton::clicked, this, &MainWindow::onResetSimulation);

    // Przycisk do zapisu symulacji
    QPushButton* saveButton = new QPushButton("Zapisz symulację");
    saveButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    simulationLayout->addWidget(saveButton);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveSimulation);


    // Przycisk do odczytu symulacji
    QPushButton* loadButton = new QPushButton("Wczytaj symulację");
    loadButton->setStyleSheet(
        "QPushButton:pressed { background-color: lightblue; }"
        );
    simulationLayout->addWidget(loadButton);
     connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadSimulation);

    // Ustawienia początkowe
    intervalSpinBox->setValue(1.0);

    startStopButton->setText("STOP");
    startStopButton->setStyleSheet(
        "QPushButton:pressed { background-color: red; }"
        );

    return simulationLayout;
}


QWidget* MainWindow::initCharts()
{
    initNazwy();  // Inicjalizujemy mapę z nazwami wykresów i serii

    QGridLayout* chartLayout = new QGridLayout();

    // Inicjalizacja wykresów
    int row = 0;
    int col = 0;

    for (const auto& [nazwaWykresu, serieNazwy] : nazwy)
    {
        // Tworzymy nowy obiekt Wykres
        Wykres* nowyWykres = new Wykres;
        nowyWykres->nazwa = nazwaWykresu;
        nowyWykres->x = 0.0;
        nowyWykres->minX = 0.0;
        nowyWykres->maxX = 10.0;
        nowyWykres->minY = -0.5;
        nowyWykres->maxY = 1.5;
        nowyWykres->currentSeriesIndex = 0;  // Dodajemy indeks bieżącej serii

        // Tworzymy wykres i widok
        nowyWykres->chart = new QChart();
        nowyWykres->view = new QChartView(nowyWykres->chart);

        // Ustawiamy tytuł wykresu
        nowyWykres->chart->setTitle(nazwaWykresu);
        nowyWykres->chart->legend()->setVisible(true);
        nowyWykres->chart->legend()->setAlignment(Qt::AlignBottom);

        // Tworzymy wspólną oś X i Y
        QValueAxis* ośX = new QValueAxis();
        ośX->setRange(nowyWykres->minX, nowyWykres->maxX);
        ośX->setTitleText("CZAS T [s]");
        nowyWykres->chart->addAxis(ośX, Qt::AlignBottom);

        QValueAxis* ośY = new QValueAxis();
        ośY->setRange(nowyWykres->minY, nowyWykres->maxY);
        ośY->setTitleText("Y");
        nowyWykres->chart->addAxis(ośY, Qt::AlignLeft);

        // Dodajemy serie do wykresu
        for (const auto& nazwaSerii : serieNazwy)
        {
            QLineSeries* seria = new QLineSeries();
            seria->setName(nazwaSerii);
            nowyWykres->chart->addSeries(seria);
            nowyWykres->serie.push_back(seria);

            // Podłączamy serie do wspólnych osi
            seria->attachAxis(ośX);
            seria->attachAxis(ośY);

            // Ukrywamy wszystkie serie poza pierwszą
            if (nowyWykres->serie.size() > 1)
                seria->setVisible(false);
        }

        // Dodajemy wykres do mapy wykresów
        wykresy[nazwaWykresu] = nowyWykres;

        // Tworzymy widget dla wykresu
        QWidget* wykresWidget = new QWidget();
        QVBoxLayout* wykresLayout = new QVBoxLayout();
        wykresLayout->addWidget(nowyWykres->view);

        // Dodajemy przyciski do zmiany serii
        QPushButton* prevButton = new QPushButton("Poprzednia seria");
        QPushButton* nextButton = new QPushButton("Następna seria");
        QPushButton* zmienTrybButton = new QPushButton("Zmień tryb wyświetlania");

        connect(prevButton, &QPushButton::clicked, [this, nowyWykres]() {
            changeSeries(nowyWykres, -1);
        });

        connect(nextButton, &QPushButton::clicked, [this, nowyWykres]() {
            changeSeries(nowyWykres, 1);
        });

        connect(zmienTrybButton, &QPushButton::clicked, [this, nowyWykres]() {
            zmienTryb(nowyWykres);
        });

        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(prevButton);
        buttonLayout->addWidget(zmienTrybButton);
        buttonLayout->addWidget(nextButton);
        wykresLayout->addLayout(buttonLayout);

        wykresWidget->setLayout(wykresLayout);

        // Dodajemy wykres do odpowiedniej komórki w układzie siatki
        chartLayout->addWidget(wykresWidget, row, col);

        // Przechodzimy do kolejnej komórki w układzie
        col++;
        if (col == 2)  // Po dwóch kolumnach przechodzimy do nowego wiersza
        {
            col = 0;
            row++;
        }

        // Dodajemy linię odniesienia dla osi X (poziom 0)
        QLineSeries* liniaOdniesienia = new QLineSeries();
        liniaOdniesienia->setPen(QPen(Qt::DashLine)); // Ustawienie przerywanej linii
        liniaOdniesienia->setColor(QColorConstants::Svg::brown);
        liniaOdniesienia->append(-10, 0);  // Punkt startowy na osi X
        liniaOdniesienia->append(3600, 0);  // Punkt końcowy na osi X
        nowyWykres->chart->addSeries(liniaOdniesienia);
        liniaOdniesienia->attachAxis(ośX);
        liniaOdniesienia->attachAxis(ośY);
    }

    QWidget* chartsWidget = new QWidget();
    chartsWidget->setLayout(chartLayout);
    chartsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return chartsWidget;
}

void MainWindow::zmienTryb(Wykres* wykres)
{
    if (wykres->wyswietlWszystkie) {
        // Przejście na tryb wyświetlania jednej serii
        wykres->wyswietlWszystkie = false;

        for (size_t i = 0; i < wykres->serie.size(); ++i) {
            wykres->serie[i]->setVisible(i == wykres->currentSeriesIndex); // Tylko aktualna seria jest widoczna
        }
    } else {
        // Przejście na tryb wyświetlania wszystkich serii
        wykres->wyswietlWszystkie = true;

        for (auto* seria : wykres->serie) {
            seria->setVisible(true); // Wszystkie serie są widoczne
        }
    }
}

void MainWindow::changeSeries(Wykres* wykres, int direction)
{
    // Jeśli wyświetlanie wszystkich serii jest włączone, pomijamy zmianę serii
    if (wykres->wyswietlWszystkie)
        return;

    // Ukrywamy bieżącą serię
    wykres->serie[wykres->currentSeriesIndex]->setVisible(false);

    // Obliczamy nowy indeks
    wykres->currentSeriesIndex += direction;
    if (wykres->currentSeriesIndex < 0)
        wykres->currentSeriesIndex = wykres->serie.size() - 1;
    else if (wykres->currentSeriesIndex >= wykres->serie.size())
        wykres->currentSeriesIndex = 0;

    // Pokazujemy nową serię
    wykres->serie[wykres->currentSeriesIndex]->setVisible(true);
}

void MainWindow::add(const QString& wykresName, const std::vector<double>& dane)
{
    // Sprawdzamy, czy wykres o podanej nazwie istnieje
    if (wykresy.find(wykresName) == wykresy.end()) {
        qDebug() << "Nie znaleziono wykresu o nazwie: " << wykresName;
        return;
    }

    // Pobieramy wykres z mapy
    Wykres* wykres = wykresy[wykresName];

    // Sprawdzamy, czy liczba danych zgadza się z liczbą serii
    if (wykres->serie.size() != dane.size()) {
        qDebug() << "Liczba danych nie pasuje do liczby serii w wykresie!";
        return;
    }

    // Zwiększamy wartość X
    wykres->x += 0.02;

    // Dodajemy dane do odpowiednich serii
    for (size_t i = 0; i < wykres->serie.size(); ++i) {
        QLineSeries* seria = wykres->serie[i];
        double nowaWartosc = dane[i];

        // Sprawdzamy, czy liczba punktów w serii przekroczyła 100
        if (seria->count() >= 500) {
            // Usuwamy najstarszy punkt (pierwszy punkt)
            seria->remove(0);
        }

        // Dodajemy nową wartość do serii
        seria->append(wykres->x, nowaWartosc);
    }

    // Dostosuj zakresy osi X i Y
    updateXAxis(wykres);
    updateYAxis(wykres);
}

void MainWindow::addDataToChart1(const QString& wykresName, const std::vector<double>& dane)
{
    add(wykresName, dane);
}

void MainWindow::addDataToChart2(const QString& wykresName, const std::vector<double>& dane)
{
    add(wykresName, dane);
}
void MainWindow::addDataToChart3(const QString& wykresName, const std::vector<double>& dane)
{
    add(wykresName, dane);
}
void MainWindow::addDataToChart4(const QString& wykresName, const std::vector<double>& dane)
{
    add(wykresName, dane);
}

void MainWindow::updateXAxis(Wykres* wykres)
{
    double minX = wykres->x - 10.0; // Ustawiamy minimalny zakres X na aktualną wartość X minus 10
    double maxX = wykres->x;      // Ustawiamy maksymalny zakres X na bieżącą wartość X

    // Iterujemy po wszystkich seriach i sprawdzamy zakres X
    for (const auto& seria : wykres->serie) {
        for (const QPointF& punkt : seria->points()) {
            minX = std::min(minX, punkt.x());
            maxX = std::max(maxX, punkt.x());
        }
    }

    // Jeśli zakres X przekroczył ustaloną długość, przesuwamy go w lewo
    if (maxX - minX > 10.0) {
        minX = maxX - 10.0; // Przesuwamy zakres w lewo
    }

    // Ustawiamy nowy zakres osi X
    wykres->minX = minX;
    wykres->maxX = maxX;

    auto osX = dynamic_cast<QValueAxis*>(wykres->chart->axes(Qt::Horizontal).first());
    if (osX) {
        osX->setRange(wykres->minX, wykres->maxX); // Ustawiamy zakres na osi X
    }
}

void MainWindow::updateYAxis(Wykres* wykres)
{
    double minY = std::numeric_limits<double>::max();  // Początkowo ustawiamy minimalną wartość na bardzo dużą
    double maxY = std::numeric_limits<double>::lowest(); // Początkowo ustawiamy maksymalną wartość na bardzo małą

    // Iterujemy po wszystkich seriach i sprawdzamy zakres Y
    for (const auto& seria : wykres->serie) {
        for (const QPointF& punkt : seria->points()) {
            minY = std::min(minY, punkt.y());
            maxY = std::max(maxY, punkt.y());
        }
    }

    // Obliczamy nowe zakresy osi Y z marginesem
    double newMinY = minY - 0.25;  // Dodajemy margines dolny
    double newMaxY = maxY + 0.25;  // Dodajemy margines górny

    // Zaokrąglamy do najbliższych wielokrotności 0.05
    newMinY = std::floor(newMinY * 20) / 20.0; // Zaokrąglenie w dół do 0.05
    newMaxY = std::ceil(newMaxY * 20) / 20.0;  // Zaokrąglenie w górę do 0.05

    // Sprawdzamy, czy zakres osi Y powinien się zmienić
    if (std::abs(newMinY - wykres->minY) > 0.25 || std::abs(newMaxY - wykres->maxY) > 0.25 ) {
        wykres->minY = newMinY;
        wykres->maxY = newMaxY;

        // Aktualizujemy zakres osi Y, jeśli zmiany są wystarczająco duże
        auto osY = dynamic_cast<QValueAxis*>(wykres->chart->axes(Qt::Vertical).first());
        if (osY) {
            osY->setRange(wykres->minY, wykres->maxY);
        }
    }
}

void MainWindow::setLoop(loopsystem* loop)
{
    this->loop = loop;
}

void MainWindow::onConfirmButtonClicked()
{
    // Pobranie wartości z SpinBoxów
    double amplituda = amplitudaSpinBox->value();
    double okres = okresSpinBox->value();
    double czestotliwosc = czestotliwoscSpinBox->value();

    // Sprawdzenie, który przycisk jest zaznaczony
    TypSygnalu typSygnalu = TypSygnalu::PROSTOKATNY;

    if (sin->isChecked()) {
        typSygnalu = TypSygnalu::SINUSOIDALNY;
    } else if (prost->isChecked()) {
        typSygnalu = TypSygnalu::PROSTOKATNY;
    } else if (jedn->isChecked()) {
        typSygnalu = TypSygnalu::SKOK_JEDNOSTKOWY;
    }

    // Przekazanie parametrów do generatora
    loop->getGenerator().ustawParametry(amplituda, okres, czestotliwosc, typSygnalu);
}

void MainWindow::onResetDerivativeMemory() {
    // Resetowanie pamięci różniczkującej
    // Dodaj logikę resetowania tutaj
    RegulatorPID* regulator =  &loop->getRegulator();

    regulator->setUchybPoprzedni(0.0);
}

void MainWindow::onResetIntegralMemory() {
    // Resetowanie pamięci całkującej
    // Dodaj logikę resetowania tutaj
    RegulatorPID* regulator =  &loop->getRegulator();

    regulator->setSumaUchybow(0.0);
}

void MainWindow::onAntiWindupToggled(int state) {
    if (state == Qt::Checked) {
        loop->getRegulator().wlaczAntiWindup(true);
    } else {
        loop->getRegulator().wlaczAntiWindup(false);
    }
}

void MainWindow::onConfirmPIDParameters() {
    // Zatwierdzenie zmienionych parametrów PID
    // Pobierz wartości z spinboxów i zastosuj je
    double p = nastawaPSpinBox->value();
    double i = nastawaISpinBox->value();
    double d = nastawaDSpinBox->value();
    double max = antiWindupMaxSpinBox->value();

    RegulatorPID* regulator =  &loop->getRegulator();

    regulator->ustawKp(p);
    regulator->ustawKi(i);
    regulator->ustawKd(d);

    regulator->setMaxUchyby(max);
}

void MainWindow::onConfirmARXParameters()
{
    double a = aCoefficientSpinBox->value();
    double b = bCoefficientSpinBox->value();
    double z = disturbanceSpinBox->value();

    std::vector<double> vec_a; vec_a.push_back(a);
    std::vector<double> vec_b; vec_a.push_back(b);

    ModelARX* arx = &loop->getModel();

    arx->setMA(vec_a);
    arx->setMB(vec_b);
    arx->setMStdev(z);

}

void  MainWindow::onStartStopSimulation()
{
    if(loop->getLoopState()){
        loop->stopLoop();
        loop->setLoopState(false);
        //startStopButton->setText("START");
    }
    else{
        loop->startLoop();
        loop->setLoopState(true);
        //startStopButton->setText("STOP");

    }
}

void MainWindow::onSaveSimulation() {
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Zapisz symulację",
        "",
        "Pliki symulacji (*.txt);;Wszystkie pliki (*.*)"
        );

    if (!fileName.isEmpty()) {
        // Możesz tu dodać wywołanie backendu do zapisu, np.:
        // simulationBackend.saveSimulation(fileName);

        QMessageBox::information(this, "Zapis symulacji", "Symulacja została zapisana: " + fileName);
        manager->saveInstance();
    }
}

void MainWindow::onLoadSimulation() {
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Wczytaj symulację",
        "",
        "Pliki symulacji (*.txt);;Wszystkie pliki (*.*)"
        );

    if (!fileName.isEmpty()) {
        // Możesz tu dodać wywołanie backendu do odczytu, np.:
        // simulationBackend.loadSimulation(fileName);

        QMessageBox::information(this, "Wczytanie symulacji", "Symulacja została wczytana: " + fileName);
        manager->loadInstance();
    }
}

void MainWindow::setManager(FileManager* manager)
{
    this->manager = manager;
}
