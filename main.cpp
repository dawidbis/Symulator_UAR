#include "simulator.h"

int main(int argc, char *argv[])
{

    Simulator simulator(argc, argv);
    simulator.run();

    return simulator.getGUI().getQApplication().exec();
}
