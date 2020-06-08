#include "registration.h"
#include "ui_registration.h"
#include <QMainWindow>
Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_back_clicked()
{
    QObject *p = this;
    p = p->parent();

    QMainWindow *main_window = qobject_cast<QMainWindow *>(p);
       main_window->show();
       hide();
}
