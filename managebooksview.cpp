#include "managebooksview.h"
#include "ui_managebooksview.h"
#include "librarypro.h"
#include "dbconnection.h"

manageBooksView::manageBooksView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::manageBooksView)
{
    ui->setupUi(this);
}

manageBooksView::~manageBooksView()
{
    delete ui;
}

//method taking us to adminAccountView
void manageBooksView::on_pushButton_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminAccountView();
}

//method taking us to adminHomePage
void manageBooksView::on_pushButton_home_page_clicked()
{
    qDebug() << "Home page";
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminHomePage();
}

//method that allows admin to return a book thats given back to them
void manageBooksView::on_pushButton_return_book_clicked()
{
    //variables declaration and opening connection to DB
    int quantity=0;
    int count=0;
    QString pesel=ui->lineEdit_pesel_3->text();
    QString bookid=ui->lineEdit_book_id->text();
    DBConnection conn;
    conn.connOpen();
    QSqlQuery query;

    //sql query to check if pesel is matching pesel in DB
    query.prepare("SELECT * FROM users WHERE PESEL=:pesel");
    query.bindValue(":pesel",pesel);

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
            qDebug()<<"Incorrect PESEL";
    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=1 and this below query will execute
    if(count==1)
    {
    //opening connection with DB
    conn.connOpen();
    QSqlQuery qry;

    //SQL Query to check if book exists in the DB
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
    conn.connClose();
    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=2 and this below query will execute
    if(count==2){

    //opening connection with DB, variables declaration
        int ifExists;
        conn.connOpen();
        QSqlQuery qry1;

        //sql query to check if record for given pesel and bookid exists in reservedBooks - if it was borrowed
        qry1.prepare("SELECT COUNT(*) FROM reservedBooks WHERE BookID=:bookid and PESEL=:pesel");
        qry1.bindValue(":bookid",bookid);
        qry1.bindValue(":pesel",pesel);

        //query execution
        qry1.exec();
        while (qry1.next())
        {
            ifExists = qry1.value(0).toInt();
            qDebug()<<"ifExist value= "<<ifExists;
            if (ifExists==1) count=3;
            else qDebug()<<"User doesn't have this book!";
        }
        conn.connClose();
        //closing connection with DB

      //if previous query was successful count=3 and this below query will execute
     if(count==3){
      //opening connection with DB
         conn.connOpen();
            QSqlQuery qry2;

            //sql query to check how many books of this bookid are currently in the database
            //assigning this value to variable quantity
            qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
            qry2.bindValue(":bookid",bookid);
            qry2.exec();
            while (qry2.next())
            {
                quantity = qry2.value(0).toInt();
                qDebug()<<quantity;
                count=4;
            }
            conn.connClose();

        }
    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=4 and this below query will execute
    if(count==4){
        //opening connection with DB
        conn.connOpen();
        QSqlQuery qry1;

        //query to remove record from reservedBooks from the DB for given pesel and bookid
        //there are no duplicates so it's safe cause we prevented that by checking during book reservation
        //if person has book like that already assigned
        qry1.prepare("DELETE FROM reservedBooks WHERE PESEL=:pesel AND BookID=:bookid");
        qry1.bindValue(":bookid",bookid);
        qry1.bindValue(":pesel",pesel);

        //query execution
        if(!qry1.exec()){
        qDebug()<<"Query error: "<<qry1.lastError();
        }
        else count=5;
        conn.connClose();

    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=5 and this below query will execute
    if(count==5){

    //opening up connection with DB
        conn.connOpen();
        QSqlQuery qry3;
        quantity++;

        //updating amount of books in DB to +1 to what it was before returning the book
        qry3.prepare("UPDATE books SET Quantity=:quantity WHERE BookID=:bookid");
        qry3.bindValue(":quantity",quantity);
        qry3.bindValue(":bookid",bookid);

        //query execution
        if(!qry3.exec()){
        qDebug()<<"Query error: "<<qry3.lastError();
        }
        else qDebug()<<"Book returned";
        conn.connClose();
    }
    conn.connClose();
    //closing connection with DB

}

//method to remove given by admin amount of books from DB
//if amount is higher equal to the one in DB its removing whole record
//if amount is lesser than the one in the database its updating quantity to new value
void manageBooksView::on_pushButton_remove_book_clicked()
{
    //opening connection with DB and variables declaration
    DBConnection conn;
    QString bookid=ui->lineEdit_book_id_rem->text();
    QString quantity=ui->lineEdit_quantity->text();
    int count=0;
    int quant=0;
    int tbremoved=0;
    int quantity_int=quantity.toInt();
    conn.connOpen();
    QSqlQuery qry;

    //query to check if bookid is in the DB
    qry.prepare("SELECT * FROM books WHERE BookID=:bookid");
    qry.bindValue(":bookid",bookid);

    //query execution
    if(qry.exec())
    {
        while(qry.next())
        {
            count++;
        }
        if(count>2)
            qDebug()<<"Something went wrong...";
        if(count<1)
            qDebug()<<"Incorrect BookID";
    }
    conn.connClose();
//closing connection with DB

    //if previous query was successful count=1 and this below query will execute
    if(count==1)
    {
            //opening up connection with DB
           conn.connOpen();
           QSqlQuery qry2;

           //checking quantity of this bookid in DB
           qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
           qry2.bindValue(":bookid",bookid);

           //query execution
           qry2.exec();
           while (qry2.next())
           {
               quant = qry2.value(0).toInt();
               qDebug()<<"Quantity of books in db: "<<quant;
           }
           conn.connClose();
           //closing connection with DB

           //setting up value of books that are supposed to stay in DB
           tbremoved=quant-quantity_int;

           //if amount of books that are supposed to stay in DB less than zero throws a qDebug
        if (tbremoved<0)
           {
               qDebug()<<"There are not enough books in the storage";
           }
           else count=2;
        conn.connClose();
    }
    conn.connClose();
    //closing connection with DB

    //if previous query was successful count=2 and this below query will execute
    if(count==2)
    {
        //if amount of books to that are supposed to stay in DB is zero removing record from DB
        if(tbremoved==0)
        {
        //opening up connection with DB
        conn.connOpen();
        QSqlQuery qry3;

        //SQL Query to delete the record
        qry3.prepare("DELETE FROM books WHERE BookID=:bookid");
        qry3.bindValue(":quant",quant);
        qry3.bindValue(":bookid",bookid);

        //query execution
        if(!qry3.exec()){
        qDebug()<<"Query error: "<<qry3.lastError();
        }
        else qDebug()<<"Book/s removed";

        //closing connection with DB
        conn.connClose();
        }
        else if (tbremoved>0) //if amount of books that are supposed to stay in DB is higher than zero updating record
        {
            //opening up connection with DB and closing previous in case of a bug
            conn.connClose();
            conn.connOpen();
            QSqlQuery qry3;

            //SQL query to update amount of books to the tbremoved value
            qry3.prepare("UPDATE books SET Quantity=:tbremoved WHERE BookID=:bookid");
            qry3.bindValue(":tbremoved",tbremoved);
            qry3.bindValue(":bookid",bookid);

            //query execution
            qry3.exec();
            while (qry3.next())
            {
            qDebug()<<qry3.value(0).toInt();
            }
            conn.connClose();
            //closing connection with DB
        }
    }
}

//method that allows admin to add a book if they provide 4 needed values
void manageBooksView::on_pushButton_add_book_clicked()
{
   //Declaring variables and opening up connection with DB
   QString title=ui->lineEdit_book_title->text();
   QString author_f_name=ui->lineEdit_author_first_name->text();
   QString author_l_name=ui->lineEdit_author_last_name->text();
   QString quantity=ui->lineEdit_quantity_add->text();
   DBConnection conn;
   conn.connOpen();
   int count=0;
   int ifExists;

if(title!=NULL){
   QSqlQuery qry1;

   //SQL Query to check if book with this title and author already is in the database
   qry1.prepare("SELECT COUNT(*) FROM books WHERE Title=:title and auFName=:author_f_name and auLName=:author_l_name");
   qry1.bindValue(":title",title);
   qry1.bindValue(":author_f_name",author_f_name);
   qry1.bindValue(":author_l_name",author_l_name);

   //query execution
   qry1.exec();
   while (qry1.next())
   {
       ifExists = qry1.value(0).toInt();
       qDebug()<<"ifExist value= "<<ifExists;
       if (ifExists==0){
           count=1; //if query is ok sets count to 1
       }
       else qDebug()<<"This book already exists in the database!";

   }
   conn.connClose();
   //closing connection with DB
}

   //if previous query was successful count=1 and this below query will execute
   if(count==1){
       //opening up connection with DB
       conn.connOpen();
       QSqlQuery qry2;

       //SQL Query to insert the book to table books, BookID is created automatically as primary key
   qry2.prepare("INSERT INTO books(title, auFName, auLName, Quantity) "
                "values(:title,:author_f_name,:author_l_name,:quantity)");
   qry2.bindValue(":title",title);
   qry2.bindValue(":author_f_name",author_f_name);
   qry2.bindValue(":author_l_name",author_l_name);
   qry2.bindValue(":quantity",quantity);

   //query execution
   if(!qry2.exec()){
   qDebug()<<"Query error: "<<qry2.lastError();
   }
   else qDebug()<<"Book added to the database";

   }

   conn.connClose();
   //closing connection with DB
}
