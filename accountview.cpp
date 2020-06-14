#include "accountview.h"
#include "ui_accountview.h"
#include "homeview.h"
#include "ui_homeview.h"
#include "dbconnection.h"
#include "loginview.h"
#include "ui_loginview.h"
#include "librarypro.h"
#include <QtDebug>

accountview::accountview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::accountview)
{
    ui->setupUi(this);
}

accountview::~accountview()
{
    delete ui;
}

void accountview::on_pushButton_home_search_a_book_2_clicked()
{
    qDebug() << "Home page";
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showHomeView();
}

void accountview::on_pushButton_change_password_clicked()
{
    int count=0;
    QString pesel=ui->lineEdit_pesel_p->text();
    QString old_pass=ui->lineEdit_old_pass->text();
    QString new_pass=ui->lineEdit_new_pass->text();
    QString new_pass_confirm=ui->lineEdit_new_pass_confirm->text();

    if(new_pass==new_pass_confirm)
{

    DBConnection conn;
    conn.connOpen();

    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
    query.bindValue(":pesel",pesel);
    query.bindValue(":password",old_pass);

    if(query.exec())
    {
        while(query.next())
        {
            count++;
            qDebug()<<"PESEL and password correct";
        }
        if(count>1)
            qDebug()<<"Something went wrong...";
        if(count<1)
            qDebug()<<"Incorrect PESEL or password.";
    }
    conn.connClose();


if(count==1){
    conn.connOpen();
    QSqlQuery qry;


    qry.prepare("UPDATE users SET password=:password WHERE PESEL=:pesel");
    qry.bindValue(":pesel",pesel);
    qry.bindValue(":password",new_pass);

    if(!qry.exec()){
    qDebug()<<"Query error: "<<qry.lastError();
    }

    conn.connClose();

}
conn.connClose();

}else qDebug()<<"Passwords do not match";

}


void accountview::on_pushButton_see_books_clicked()
{
    int count=0;
    QString pesel_b=ui->lineEdit_pesel_b->text();
    QString pass_b=ui->lineEdit_password_b->text();

    DBConnection conn;
    conn.connOpen();

    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
    query.bindValue(":pesel",pesel_b);
    query.bindValue(":password",pass_b);

    if(query.exec())
    {
        while(query.next())
        {
            count++;
            qDebug()<<"PESEL and password correct";
        }
        if(count>1)
            qDebug()<<"Something went wrong...";
        if(count<1)
            qDebug()<<"Incorrect PESEL or password.";
    }
    conn.connClose();

    if(count==1){
        conn.connOpen();

        QSqlQuery qry;
        qDebug()<<qry.prepare("SELECT books.title AS 'Title', books.auFName AS 'First Name', books.auLName AS 'Last Name' "
                              "FROM books LEFT JOIN reservedBooks ON reservedBooks.BookID=books.BookID "
                              "LEFT JOIN users ON users.PESEL=reservedBooks.PESEL WHERE users.PESEL=:pesel");
        qry.bindValue(":pesel",pesel_b);

        if(!qry.exec()){
            qDebug()<<"Query error: "<<qry.lastError();
        }

        QSqlQueryModel *modal =new QSqlQueryModel();
        modal->setQuery(qry);
        qDebug()<<modal->rowCount();
        ui->tableView_2->setModel(modal);
        conn.connClose();
    }
    conn.connClose();
}
