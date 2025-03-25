#include "MainWindow.h"
#include "ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setCentralWidget(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLoop(loopsystem *loop)
{
    this->loop = loop;
}

void MainWindow::setManager(FileManager *manager)
{
    this->manager = manager;
}
