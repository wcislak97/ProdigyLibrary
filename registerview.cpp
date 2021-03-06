#include "registerview.h"
#include "ui_registerview.h"
#include "librarypro.h"
#include "dbconnection.h"

#include <QtDebug>


RegisterView::RegisterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterView)
{
    ui->setupUi(this);
}

RegisterView::~RegisterView()
{
    delete ui;
}

//method taking us back to loginView
void RegisterView::on_pushButton_back_clicked()
{
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showLoginView();
}

//method that allows user to register
//there can be no duplicates in the database for same PESEL as it is set as users table PRIMARY KEY
void RegisterView::on_pushButton_register_clicked()
{
    //variables declaration and opening up connection with DB
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

    //SQL Query to insert all the values given by user to the DB
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
    //closing connection with DB
}
