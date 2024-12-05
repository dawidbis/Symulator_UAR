#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class FileManager : public QObject
{
    Q_OBJECT

public:
    explicit FileManager(QObject *parent = nullptr);

public slots:


protected slots:


private slots:


signals:


private:

};

#endif // FILEMANAGER_H
