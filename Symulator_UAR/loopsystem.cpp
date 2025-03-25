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

    uchyb =  wartoscGenerator - wartoscARX;

    wartoscPID = regulator.symuluj(uchyb);

    temp_P = regulator.getWartoscProporcjonalna();
    temp_I = regulator.getWartoscCalkujaca();
    temp_D = regulator.getWartoscRozniczkujaca();

    wartoscARX = model.symuluj(wartoscPID);

}

void loopsystem::setGUI(MainWindow* gui)
{
    this->gui = gui;

}



