#include "loopsystem.h"

loopsystem::loopsystem(QObject *parent)
    : QObject{parent},
    loopState(false),
    interval(1000),
    model({ -0.4 }, { 0.6 }, 1, 0.0),
    regulator(0.5, 5.0, 0.2, 1.0),
    manager(new FileManager(this,this))
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&loopsystem::symuluj);
    connect(this,&loopsystem::saveFile,manager,&FileManager::saveInstance);
    connect(this,&loopsystem::loadFile,manager,&FileManager::loadInstance);

    generator.ustawParametry(1, 1, 0.1, TypSygnalu::PROSTOKATNY);

    interval = 50;
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

/*void loopsystem::emitSignals()
{
    double P =this->regulator.getWartoscProporcjonalna();
    double I = this->regulator.getWartoscCalkujaca();
    double D = this->regulator.getWartoscRozniczkujaca();
    double ARX = this->model.getARX();
   emit emitP(P);
   emit emitI(I);
   emit emitD(D);
   emit emitARX(ARX);
}*/

void loopsystem::symuluj()
{
    wartoscGenerator = generator.symuluj(interval);

    qDebug() << "Wartosc" << wartoscPID;

    uchyb =  wartoscGenerator; //- wartoscARX;

    wartoscPID = regulator.symuluj(uchyb);

    //wartoscARX = model.symuluj(wartoscPID);

    emit emitGenerator(wartoscGenerator);
    emit emitPID(wartoscPID);
}

void loopsystem::setGUI(MainWindow* gui)
{
    this->gui = gui;

    connect(this, &loopsystem::emitGenerator, gui, &MainWindow::updatePlot);
    connect(this, &loopsystem::emitPID, gui, &MainWindow::updatePID);
}



