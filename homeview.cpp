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

//method just for qDebug
void HomeView::on_pushButton_home_search_a_book_clicked()
{
   qDebug() << "Search book page opened";
}

//method taking us to LoginView - logging out
void HomeView::on_pushButton_logout_clicked()
{
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showLoginView();
}

//method taking us to AccountView
void HomeView::on_pushButton_home_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAccountView();
}

//method to search for a book based on title/authors first/last name
void HomeView::on_actual_search_button_clicked()
{
    //variables declaration
    QString title="";
    QString first_name="";
    QString last_name="";

    //setting wildcards on variables for search to be flexible
    //search is able to find a book by part of a phrase
    title = "%"+ui->lineEdit_home_title->text()+"%";
    first_name = "%"+ui->lineEdit_home_first_name->text()+"%";
    last_name = "%"+ui->lineEdit_home_last_name->text()+"%";

    //opening connection with DB
    DBConnection conn;
    conn.connOpen();
    QSqlQuery query;

    //SQL Query to select
    query.prepare("SELECT BookID AS 'BookID', title AS 'Title', auFName AS 'First Name', auLName AS 'Last Name' FROM books "
                  "WHERE title LIKE :title AND auFName LIKE :first_name AND auLName LIKE :last_name");
    query.bindValue(":title",title);
    query.bindValue(":first_name",first_name);
    query.bindValue(":last_name",last_name);

    //query execution
    if(!query.exec()){
    qDebug()<<"Query error: "<<query.lastError();
    }
    //block to show data in UI in tableView_2
    QSqlQueryModel *modal =new QSqlQueryModel();
    modal->setQuery(query);
    qDebug()<<modal->rowCount();
    ui->tableView->setModel(modal);
    //closing connection with DB
    conn.connClose();
}

//method booking the book for given pesel and password
void HomeView::on_bookIt_button_clicked()
{
    //variables declaration
int count=0;
int quant=0;
QString pesel=ui->lineEdit_pesel->text();
QString password=ui->lineEdit_password->text();
QString bookid=ui->lineEdit_bookID->text();

//opening connection with DB
DBConnection conn;
conn.connOpen();
QSqlQuery query;

//SQL Query to check if password and PESEL are matching the ones in DB
query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
query.bindValue(":pesel",pesel);
query.bindValue(":password",password);


//query execution
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
//closing connection with DB

//if previous query was successful count=1 and this below query will execute
if(count==1)
{
//opening up connection with DB
conn.connOpen();
QSqlQuery qry;

//SQL Query to check if book exists in DB
qry.prepare("SELECT * FROM books WHERE BookID=:bookid");
qry.bindValue(":bookid",bookid);

//query execution
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
}
conn.connClose();
//closing connection with DB

//if previous query was successful count=2 and this below query will execute
if(count==2){
    //variables declaration and opening up connection with DB
    int ifExists;
    conn.connOpen();
    QSqlQuery qry1;

    //checking there are no duplicates - if this PESEL already has this BookId assigned
    qry1.prepare("SELECT COUNT(*) FROM reservedBooks WHERE BookID=:bookid and PESEL=:pesel");
    qry1.bindValue(":bookid",bookid);
    qry1.bindValue(":pesel",pesel);

    //query execution
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
//closing connection with DB

//if previous query was successful count=3 and this below query will execute
if(count==3)
{
    //Opening connection with DB
    conn.connOpen();
    QSqlQuery qry2;

    //SQL Query to check if there is at least one book of this BookID in the database
    qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
    qry2.bindValue(":bookid",bookid);

    //Query execution
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
//closing connection with DB

//if previous query was successful count=4 and this below query will execute
if(count==4)
{
//opening connection with DB
conn.connOpen();
QSqlQuery qry1;

//SQL Query to insert into database new record in table reservedBooks for the borrowed book
qry1.prepare("INSERT INTO reservedBooks (BookID,PESEL) values(:bookid,:pesel)");
qry1.bindValue(":bookid",bookid);
qry1.bindValue(":pesel",pesel);

//query execution
if(!qry1.exec()){
qDebug()<<"Query error: "<<qry1.lastError();
}

conn.connClose();

count++;

}
conn.connClose();
//closing connection with DB

//if previous query was successful count=5 and this below query will execute
if(count==5){

    //variables declaration and opening up connection with DB
    conn.connOpen();
    QSqlQuery qry3;
    quant--;

    //SQL Query to set quantity of the the borrowed bookId to -1 in comparison to before in DB
    qry3.prepare("UPDATE books SET Quantity=:quant WHERE BookID=:bookid");
    qry3.bindValue(":quant",quant);
    qry3.bindValue(":bookid",bookid);

    //query execution
    qry3.exec();
    while (qry3.next())
    {
    qDebug()<<qry3.value(0).toInt();
    }
    conn.connClose();
}
conn.connClose();
//closing connection with DB
}

