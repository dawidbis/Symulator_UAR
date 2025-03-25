#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(DialogData &outData, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog), m_outData(&outData)
{
    ui->setupUi(this);
    connect(this,SIGNAL(finished(int)),this,SLOT(on_finished(int)));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_finished(int arg)
{
    Q_UNUSED(arg);

    if(m_outData != nullptr)
    {
        m_outData->delay=ui->delay->value();
        m_outData->inputA=ui->lineEdit->text();
        m_outData->inputB=ui->lineEdit_2->text();
        m_outData->disturbance=ui->doubleSpinBox->value();
    }
    deleteLater();
}
