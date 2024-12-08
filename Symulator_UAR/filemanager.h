#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDataStream>
#include <vector>
#include <deque>

class loopsystem;

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr,loopsystem* loopSystem=nullptr);
public slots:
    void saveInstance();
    void loadInstance();

protected slots:


private slots:


signals:


private:   
    loopsystem* loopSystem;
};

#endif // FILEMANAGER_H
