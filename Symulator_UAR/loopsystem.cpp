#include "loopsystem.h"

loopsystem::loopsystem(QObject *parent)
    : QObject{parent},
    loopState(false),
    model(),
    regulator(0.0,0.0,0.0,0.0),
    manager(nullptr)
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&loopsystem::executeLoop);
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

void loopsystem::saveFile()
{

}

void loopsystem::emitSignals()
{
    emitP(this->regulator.getWartoscProporcjonalna());
    emitI(this->regulator.getWartoscCalkujaca());
    emitD(this->regulator.getWartoscRozniczkujaca());
    emitARX(this->model.getARX());
}

void loopsystem::setFileManager(FileManager &newManager)
{
    manager=newManager;
    connect(this,&loopsystem::emitP,manager,&FileManager::setP);
    connect(this,&loopsystem::emitI,manager,&FileManager::setI);
    connect(this,&loopsystem::emitD,manager,&FileManager::setD);
    connect(this,&loopsystem::emitARX,manager,&FileManager::setARX);
}

void loopsystem::executeLoop()
{
    static double wejsciePID =0.0;
    wartoscPID = regulator.symuluj(wejsciePID);
    wartoscARX = model.symuluj(wartoscPID);
    if(manager!=nullptr)
        emitSygnals();
    wejsciePID=wartoscARX;

}

void loopsystem::onSaveFile()
{

}


