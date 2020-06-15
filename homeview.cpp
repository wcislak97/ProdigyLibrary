#include "homeview.h"
#include "ui_homeview.h"
#include "dbconnection.h"
#include "loginview.h"
#include "ui_loginview.h"
#include "librarypro.h"
#include <QtDebug>

HomeView::HomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeView)
{
    ui->setupUi(this);
}

HomeView::~HomeView()
{
    delete ui;
}

void HomeView::on_pushButton_home_search_a_book_clicked()
{
   qDebug() << "Search book page opened";
}

void HomeView::on_pushButton_home_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAccountView();
}

void HomeView::on_actual_search_button_clicked()
{
    qDebug() << "Searching for a book";

    QString title="";
    QString first_name="";
    QString last_name="";

    title = "%"+ui->lineEdit_home_title->text()+"%";
    first_name = "%"+ui->lineEdit_home_first_name->text()+"%";
    last_name = "%"+ui->lineEdit_home_last_name->text()+"%";


    DBConnection conn;
    conn.connOpen();

    QSqlQuery query;
    query.prepare("SELECT BookID AS 'BookID', title AS 'Title', auFName AS 'First Name', auLName AS 'Last Name' FROM books WHERE title LIKE :title AND auFName LIKE :first_name AND auLName LIKE :last_name");
    query.bindValue(":title",title);
    query.bindValue(":first_name",first_name);
    query.bindValue(":last_name",last_name);

    if(!query.exec()){
    qDebug()<<"Query error: "<<query.lastError();
    }

    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->tableView->setModel(modal);
    conn.connClose();
}

void HomeView::on_bookIt_button_clicked()
{
int count=0;
int quant=0;
QString pesel=ui->lineEdit_pesel->text();
QString password=ui->lineEdit_password->text();
QString bookid=ui->lineEdit_bookID->text();

DBConnection conn;
conn.connOpen();

QSqlQuery query;

query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
query.bindValue(":pesel",pesel);
query.bindValue(":password",password);

if(query.exec())
{
    while(query.next())
    {
        count++;
    }
    if(count>1)
        qDebug()<<"Something went wrong...";
    if(count<1)
        qDebug()<<"Incorrect PESEL or password.";
}
conn.connClose();


if(count==1)
{
conn.connOpen();
QSqlQuery qry;
qry.prepare("SELECT * FROM books WHERE BookID=:bookid");
qry.bindValue(":bookid",bookid);
if(qry.exec())
{
    while(qry.next())
    {
        count++;
    }
    if(count>3)
        qDebug()<<"Something went wrong...";
    if(count<2)
        qDebug()<<"Incorrect BookID";
}
conn.connClose();
}
conn.connClose();

if(count==2){
    int ifExists;
    conn.connOpen();
    QSqlQuery qry1;

    qry1.prepare("SELECT COUNT(*) FROM reservedBooks WHERE BookID=:bookid and PESEL=:pesel");
    qry1.bindValue(":bookid",bookid);
    qry1.bindValue(":pesel",pesel);
    qry1.exec();
    while (qry1.next())
    {
        ifExists = qry1.value(0).toInt();
        qDebug()<<"ifExist value= "<<ifExists;
        if (ifExists==0) count++;
        else qDebug()<<"You already have this book!";
    }
    conn.connClose();

}
conn.connClose();

if(count==3)
{   conn.connOpen();
    QSqlQuery qry2;

    qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
    qry2.bindValue(":bookid",bookid);
    qry2.exec();
    while (qry2.next())
    {
        quant = qry2.value(0).toInt();
        qDebug()<<quant;
        if (quant>0) count++;
        else qDebug()<<"WE DONT HAVE ENOUGH BOOKS!";
    }
    conn.connClose();

}
conn.connClose();

if(count==4)
{
conn.connOpen();
QSqlQuery qry1;
qry1.prepare("INSERT INTO reservedBooks (BookID,PESEL,Quantity) values(:bookid,:pesel,:1)");
qry1.bindValue(":bookid",bookid);
qry1.bindValue(":pesel",pesel);

if(!qry1.exec()){
qDebug()<<"Query error: "<<qry1.lastError();
}

conn.connClose();

count++;

}
conn.connClose();

if(count==5){
    conn.connOpen();
    QSqlQuery qry3;
    quant--;

    qry3.prepare("UPDATE books SET Quantity=:quant WHERE BookID=:bookid");
    qry3.bindValue(":quant",quant);
    qry3.bindValue(":bookid",bookid);

    qry3.exec();
    while (qry3.next())
    {
    qDebug()<<qry3.value(0).toInt();
    }
    conn.connClose();
}
conn.connClose();


}

void HomeView::on_pushButton_logout_clicked()
{

}
