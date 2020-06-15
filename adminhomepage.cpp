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


void adminHomePage::on_pushButton_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminAccountView();
}

void adminHomePage::on_pushButton_manage_books_clicked()
{
    qDebug() << "Manage books";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showManageBooks();
}

void adminHomePage::on_bookIt_button_3_clicked()
{
    int count=0;
    int quant=0;
    QString pesel=ui->lineEdit_pesel_3->text();
    QString bookid=ui->lineEdit_bookID_3->text();

    DBConnection conn;
    conn.connOpen();

    QSqlQuery query;

    query.prepare("SELECT * FROM users WHERE PESEL=:pesel");
    query.bindValue(":pesel",pesel);
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
            if (ifExists==0) {count=3; qDebug()<<"Counting rows";}
            else qDebug()<<"They already have this book!";
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
            if (quant>0) count=4;
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

    count=5;

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
        qDebug()<<"Book reserved";
        }
        conn.connClose();
    }
    conn.connClose();


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
