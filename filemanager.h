#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#pragma once

#include <QObject>
#include <QDebug>
#include <QFile>
#include "loopsystem.h"

class LoopSystem;

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    void setLoop(LoopSystem* loop);
public slots:
    void saveInstance(QString filePath);
    void loadInstance(QString filePath);

signals:

private:
    LoopSystem* loop;
};

#endif // FILEMANAGER_H
