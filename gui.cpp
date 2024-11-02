#include "gui.h"

GUI::GUI(int argc, char *argv[])
    : a(argc, argv)
{
    w.show();
}

QApplication& GUI::getQApplication()
{
    return a;
}
