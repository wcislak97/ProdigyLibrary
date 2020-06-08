#include "librarypro.h"
#include "ui_librarypro.h"

LibraryPro::LibraryPro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryPro)
{
    ui->setupUi(this);
}

LibraryPro::~LibraryPro()
{
    delete ui;
}


void LibraryPro::on_pushButton_clicked()
{
    QString pesel = ui->lineEdit
}
