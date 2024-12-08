#include "loopsystem.h"

loopsystem::loopsystem(QObject *parent)
    : QObject{parent},
    loopState(false),
    model(),
    regulator(0.0,0.0,0.0,0.0),
    manager(new FileManager(this,this))
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&loopsystem::executeLoop);
    connect(this,&loopsystem::saveFile,&manager,&FileManager::saveInstance);
    connect(this,&loopsystem::loadFile,&manager,&FileManager::loadInstance);
}

loopsystem::~loopsystem(){
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

void loopsystem::startLoop()
{
    if(!loopState){
        loopState=true;
        timer->start(100);
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
    saveFile();
}
void loopsystem::emitLoad(){
    loadFile();
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


void loopsystem::executeLoop()
{
    static double wejsciePID =0.0;
    wartoscPID = regulator.symuluj(wejsciePID);
    wartoscARX = model.symuluj(wartoscPID);
    wejsciePID=wartoscARX;

}




