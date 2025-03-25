#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

struct DialogData
{
    int delay; QString inputA; QString inputB; double disturbance;
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(DialogData &outData,QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void on_finished(int);

private:
    Ui::Dialog *ui;
    DialogData *m_outData;
};

#endif // DIALOG_H
