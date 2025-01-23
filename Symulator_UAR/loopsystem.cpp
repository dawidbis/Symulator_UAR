#include "loopsystem.h"

loopsystem::loopsystem(QObject *parent)
    : QObject{parent},
    loopState(false),
    interval(10),
    model({ -0.4 }, { 0.6 }, 1, 0.01),
    regulator(0.5, 5.0, 0.2, 1),
    manager(new FileManager(this,this))
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&loopsystem::symuluj);
    connect(this,&loopsystem::saveFile,manager,&FileManager::saveInstance);
    connect(this,&loopsystem::loadFile,manager,&FileManager::loadInstance);

    generator.ustawParametry(1.0, 2, 0.5, TypSygnalu::PROSTOKATNY);

    interval = 20;
}

loopsystem::~loopsystem()
{
    delete manager;
    delete timer;
}

bool loopsystem::getLoopState(){
    return loopState;
}
double loopsystem::getWartoscARX(){
    return wartoscARX;
}
double loopsystem::getWartoscPID(){
    return wartoscPID;
}
ModelARX& loopsystem::getModel(){
    return model;
}
RegulatorPID& loopsystem::getRegulator(){
    return regulator;
}

Generator& loopsystem::getGenerator()
{
    return generator;
}

void loopsystem::setLoopState(bool state){
    this->loopState=state;
}
void loopsystem::setWartoscARX(double arx){
    this->wartoscARX=arx;
}
void loopsystem::setWartoscPID(double pid){
    this->wartoscPID=pid;
}

void loopsystem::startLoop()
{
    if(!loopState){
        loopState=true;
        timer->start(interval);
    }
}

void loopsystem::stopLoop()
{
    if(loopState){
        loopState=false;
        timer->stop();
    }
}

void loopsystem::emitSave(){
    emit saveFile();
}
void loopsystem::emitLoad(){
    emit loadFile();
}

void loopsystem::symuluj()
{
    wartoscGenerator = generator.symuluj(interval);

    //qDebug() << "Generator: " <<  wartoscGenerator;

    uchyb =  wartoscGenerator - wartoscARX;

    //qDebug() << "Uchyb: " << uchyb;

    wartoscPID = regulator.symuluj(uchyb);

    temp_P = regulator.getWartoscProporcjonalna();
    temp_I = regulator.getWartoscCalkujaca();
    temp_D = regulator.getWartoscRozniczkujaca();

    //qDebug() << "PID: " <<   wartoscPID;

    wartoscARX = model.symuluj(wartoscPID);

    //qDebug() << "ARX: " <<  wartoscARX << "\n";

    dane1 = {wartoscGenerator, wartoscARX};
    emit daneDoWykresu_1("A) Zadana/Rzeczywista", dane1);
    dane2 = {uchyb};
    emit daneDoWykresu_2("C) Uchyb", dane2);
    dane3 = {wartoscPID, temp_P, temp_I, temp_D};
    emit daneDoWykresu_3("B) Składowe PID", dane3);
    dane4 = {wartoscARX};
    emit daneDoWykresu_4("D) Model ARX", dane4);
}

void loopsystem::setGUI(MainWindow* gui)
{
    this->gui = gui;

    connect(this, &loopsystem::daneDoWykresu_1, gui, &MainWindow::addDataToChart1);
    connect(this, &loopsystem::daneDoWykresu_2, gui, &MainWindow::addDataToChart2);
    connect(this, &loopsystem::daneDoWykresu_3, gui, &MainWindow::addDataToChart3);
    connect(this, &loopsystem::daneDoWykresu_4, gui, &MainWindow::addDataToChart4);
}



