#include "simulator.h"

Simulator::Simulator(int argc, char *argv[])
    : m_gui(argc, argv)
{

}

void Simulator::run(){

}

GUI& Simulator::getGUI()
{
    return m_gui;
}
