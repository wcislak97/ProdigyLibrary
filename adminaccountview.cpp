#include "adminaccountview.h"
#include "librarypro.h"
#include "ui_adminaccountview.h"
#include "dbconnection.h"

adminaccountview::adminaccountview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminaccountview)
{
    ui->setupUi(this);
}

adminaccountview::~adminaccountview()
{
    delete ui;
}

//method taking us to AdminHomePage
void adminaccountview::on_pushButton_home_search_a_book_2_clicked()
{
    qDebug() << "AdminHomePage";
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminHomePage();
}

//method taking us to ManageBooksView
void adminaccountview::on_pushButton_manage_books_clicked()
{
    qDebug() << "ManageBooksView";
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showManageBooks();
}

//method showing books that are borrowed under given PESEL
void adminaccountview::on_pushButton_see_books_clicked()
{
    //variables declaration
    int count=0;
    QString pesel_b=ui->lineEdit_pesel_b->text();
    QString pass_b=ui->lineEdit_password_b->text();

    //opening connection to DB
    DBConnection conn;
    conn.connOpen();
    QSqlQuery query;

    //SQL Query to check if PESEL and password are matching records in DB
    query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
    query.bindValue(":pesel",pesel_b);
    query.bindValue(":password",pass_b);

    //Query execution
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
    //closing connection with DB
    conn.connClose();

    //if previous query was successful count=1 and this below query will execute
    if(count==1){

        //opening connetion with database
        conn.connOpen();
        QSqlQuery qry;

        //SQL Query joining all 3 tables, this is what will be displayed on screen
        //after query is executed and data is given to UI
        qDebug()<<qry.prepare("SELECT books.title AS 'Title', books.auFName AS 'First Name', books.auLName AS 'Last Name' "
                              "FROM books LEFT JOIN reservedBooks ON reservedBooks.BookID=books.BookID "
                              "LEFT JOIN users ON users.PESEL=reservedBooks.PESEL WHERE users.PESEL=:pesel");
        qry.bindValue(":pesel",pesel_b);

        //query execution
        if(!qry.exec()){
            //if query unsuccessful qDebug will show its last error
            qDebug()<<"Query error: "<<qry.lastError();
        }
        //block to show data in UI in tableView_2
        QSqlQueryModel *modal =new QSqlQueryModel();
        modal->setQuery(qry);
        qDebug()<<modal->rowCount();
        ui->tableView_2->setModel(modal);
    }
    //closing connection with DB
    conn.connClose();
}

//method changing password for given PESEL
void adminaccountview::on_pushButton_change_password_clicked()
{
    //variables declaration
    int count=0;
    QString pesel=ui->lineEdit_pesel_p->text();
    QString old_pass=ui->lineEdit_old_pass->text();
    QString new_pass=ui->lineEdit_new_pass->text();
    QString new_pass_confirm=ui->lineEdit_new_pass_confirm->text();

    //function to confirm if passwords provided by user are matching
    if(new_pass==new_pass_confirm)
{

    //variables declaration and opening connection to DB
    DBConnection conn;
    conn.connOpen();
    QSqlQuery query;

    //SQL Query to check if old password and PESEL given by user match the ones in DB
    query.prepare("SELECT * FROM users WHERE PESEL=:pesel AND password=:password");
    query.bindValue(":pesel",pesel);
    query.bindValue(":password",old_pass);

    //Query execution
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
    //closing connection with DB
    conn.connClose();

//if previous query was successful count=1 and this below query will execute
if(count==1){
    //variables declaration and opening connection to DB
    conn.connOpen();
    QSqlQuery qry;

    //SQL Query to update password in the DB to the new one
    qry.prepare("UPDATE users SET password=:password WHERE PESEL=:pesel");
    qry.bindValue(":pesel",pesel);
    qry.bindValue(":password",new_pass);

    //Query execution
    if(!qry.exec()){
        //if execution is unsuccessful qDebug will throw its error
    qDebug()<<"Query error: "<<qry.lastError();
    }
}
//closing connection with DB
conn.connClose();
//throw if first if checking if both new passwords are matching
}else qDebug()<<"Passwords do not match";
}
