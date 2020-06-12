#include "registration.h"
#include "ui_registration.h"
#include "librarypro.h"
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

void Registration::on_pushButton_register_clicked()
{
    DBConnection conn;

   QString pesel = ui->lineEdit_pesel->text();
    QString password = ui->lineEdit_password->text();
    QString first_name =ui->lineEdit_first_name->text();
    QString last_name =ui->lineEdit_last_name->text();
    QString phone_number =ui->lineEdit_phone_number->text();
    QString street_and_number =ui->lineEdit_street_and_number->text();
    QString city =ui->lineEdit_city->text();
    QString country =ui->lineEdit_country->text();


    if(!(conn.connOpen()))
    {
        qDebug()<<"Failed to open database!";
        //return;
    }
    QSqlQuery qry;
    qry.prepare("INSERT INTO users(PESEL, password, firstName, lastName, phoneNo, streetNo, city, country) "
                "values(:pesel,:password,:first_name,:last_name,:phone_number,:street_and_number,:city,:country)");
    qry.bindValue(":pesel",pesel);
    qry.bindValue(":password",password);
    qry.bindValue(":first_name",first_name);
    qry.bindValue(":last_name",last_name);
    qry.bindValue(":phone_number",phone_number);
    qry.bindValue(":street_and_number",street_and_number);
    qry.bindValue(":city",city);
    qry.bindValue(":country",country);

    qDebug()<<qry.exec();
    conn.connClose();

}
