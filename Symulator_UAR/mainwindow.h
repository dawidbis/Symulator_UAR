#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "loopsystem.h"

class loopsystem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setLoop(loopsystem* loop);
    void setManager(FileManager* manager);
public slots:

private:
    loopsystem* loop;
    FileManager* manager;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
