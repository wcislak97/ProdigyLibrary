#include "adminhomepage.h"
#include "ui_adminhomepage.h"
#include "accountview.h"
#include "ui_accountview.h"
#include "homeview.h"
#include "ui_homeview.h"
#include "dbconnection.h"
#include "loginview.h"
#include "ui_loginview.h"
#include "librarypro.h"


adminHomePage::adminHomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminHomePage)
{
    ui->setupUi(this);
}

adminHomePage::~adminHomePage()
{
    delete ui;
}

//method taking us to AdminAccountView
void adminHomePage::on_pushButton_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminAccountView();
}

//method taking us to LoginView - logging user out of the system
void adminHomePage::on_pushButton_logout_clicked()
{
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showLoginView();
}

//method taking us to ManageBooksView
void adminHomePage::on_pushButton_manage_books_clicked()
{
    qDebug() << "Manage books";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showManageBooks();
}

void adminHomePage::on_actual_search_button_clicked()
{
    //here it repeats the code from HomeView::on_actual_search_button_clicked but idk how to make that one work and this works
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
    ui->tableView_3->setModel(modal);  //only difference is here tableView->tableView_3
    conn.connClose();
}

//method that is booking a book for given PESEL and BookID
void adminHomePage::on_bookIt_button_4_clicked()
{
    //variables declaration
    int count=0;
    int quant=0;
    QString pesel=ui->lineEdit_pesel_4->text();
    QString bookid=ui->lineEdit_bookID_4->text();

    //variables declaration and opening connection to DB
    DBConnection conn;
    conn.connOpen();
    QSqlQuery query;

    //SQL Query to check if given PESEL exists in table users
    query.prepare("SELECT * FROM users WHERE PESEL=:pesel");
    query.bindValue(":pesel",pesel);

    //Query execution
    if(query.exec())
    {
        while(query.next())
        {
            count++;
        }
        if(count>1)
            qDebug()<<"Something went wrong...";
        if(count<1)
            qDebug()<<"Incorrect PESEL.";
    }
    //Closing connection with DB
    conn.connClose();

    //if previous query was successful count=1 and this below query will execute
    if(count==1)
    {
    //opening connection to DB
    conn.connOpen();
    QSqlQuery qry;

    //SQL Query to check if BookID exists in the database
    qry.prepare("SELECT * FROM books WHERE BookID=:bookid");
    qry.bindValue(":bookid",bookid);

    //Query execution
    if(qry.exec())
    {
        while(qry.next())
        {
            count=2;
        }
        if(count>3)
            qDebug()<<"Something went wrong...";
        if(count<2)
            qDebug()<<"Incorrect BookID";
    }
    conn.connClose();
    }
    conn.connClose();
    //closing connection with DB


    //if previous query was successful count=2 and this below query will execute
    if(count==2){

        //variables declaration and opening connection to DB
        int ifExists;
        conn.connOpen();
        QSqlQuery qry1;

        //SQL Query to check if someone already has this book
        //Logic is query provides amount of rows for this bookid and pesel from reservedBooks table
        //if ifExists=0 it means that person doesnt have a book and we can set count to 3
        qry1.prepare("SELECT COUNT(*) FROM reservedBooks WHERE BookID=:bookid and PESEL=:pesel");
        qry1.bindValue(":bookid",bookid);
        qry1.bindValue(":pesel",pesel);

        //Query execution
        qry1.exec();
        while (qry1.next())
        {
            ifExists = qry1.value(0).toInt();
            qDebug()<<"ifExist value= "<<ifExists;
            if (ifExists==0) {count=3; qDebug()<<"Counting rows";}
            else qDebug()<<"They already have this book!";
        }
        conn.connClose();

    }
    conn.connClose();
    //Closing connection with DB

    //if previous query was successful count=3 and this below query will execute
    if(count==3)
    {
        //opening connection to DB
        conn.connOpen();
        QSqlQuery qry2;

        //SQL Query to check if Quantity of given BookID is higher than 0 if yes count is set to 4
        qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
        qry2.bindValue(":bookid",bookid);

        //Query execution
        qry2.exec();
        while (qry2.next())
        {
            quant = qry2.value(0).toInt();
            qDebug()<<quant;
            if (quant>0) count=4;
            else qDebug()<<"WE DONT HAVE ENOUGH BOOKS!";
        }
        conn.connClose();

    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=4 and this below query will execute
    if(count==4)
    {
    //opening connection to DB
    conn.connOpen();
    QSqlQuery qry1;

    //SQL Query to create new record with PESEL and BookID in reservedBooks
    qry1.prepare("INSERT INTO reservedBooks (BookID,PESEL) values(:bookid,:pesel)");
    qry1.bindValue(":bookid",bookid);
    qry1.bindValue(":pesel",pesel);

    //Query execution
    if(!qry1.exec()){
    qDebug()<<"Query error: "<<qry1.lastError();
    }

    conn.connClose();

    count=5;

    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=5 and this below query will execute
    if(count==5){
        //opening connection to DB
        conn.connOpen();
        QSqlQuery qry3;
        quant--;

        //SQL Query to update quantity for given BookID
        qry3.prepare("UPDATE books SET Quantity=:quant WHERE BookID=:bookid");
        qry3.bindValue(":quant",quant);
        qry3.bindValue(":bookid",bookid);

        //Query execution
        qry3.exec();
        while (qry3.next())
        {
        qDebug()<<qry3.value(0).toInt();
        qDebug()<<"Book reserved";
        }
        conn.connClose();
    }
    conn.connClose();
    //closing connection with DB

}
