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

void manageBooksView::on_pushButton_your_account_clicked()
{
    qDebug() << "Your Account";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminAccountView();
}

void manageBooksView::on_pushButton_home_page_clicked()
{
    qDebug() << "Home page";
    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showAdminHomePage();
}

void manageBooksView::on_pushButton_return_book_clicked()
{
    int quantity=0;
    int count=0;
    QString pesel=ui->lineEdit_pesel_3->text();
    QString bookid=ui->lineEdit_book_id->text();

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
            qDebug()<<"Incorrect PESEL";
    }
    conn.connClose();


    if(count==1)
    {
  //      qDebug()<<"1st function";
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

    //    qDebug()<<"2nd function";
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
            if (ifExists==1) count=3;
            else qDebug()<<"User doesn't have this book!";
        }
        conn.connClose();

     if(count==3){
    //     qDebug()<<"3rd function";
         conn.connOpen();
            QSqlQuery qry2;

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
        conn.connClose();

    }
    conn.connClose();

    if(count==4){
        conn.connOpen();
        QSqlQuery qry1;
    //qDebug()<<"4th function";
        qry1.prepare("DELETE FROM reservedBooks WHERE PESEL=:pesel AND BookID=:bookid");
        qry1.bindValue(":bookid",bookid);
        qry1.bindValue(":pesel",pesel);

        if(!qry1.exec()){
        qDebug()<<"Query error: "<<qry1.lastError();
        }
        else count=5;
        conn.connClose();

    }
    conn.connClose();

    if(count==5){
    //qDebug()<<"5th function";

        conn.connOpen();
        QSqlQuery qry3;
        quantity++;

        qry3.prepare("UPDATE books SET Quantity=:quantity WHERE BookID=:bookid");
        qry3.bindValue(":quantity",quantity);
        qry3.bindValue(":bookid",bookid);

        if(!qry3.exec()){
        qDebug()<<"Query error: "<<qry3.lastError();
        }
        else qDebug()<<"Book returned";
        conn.connClose();
    }
    conn.connClose();


}

void manageBooksView::on_pushButton_remove_book_clicked()
{
    DBConnection conn;
    conn.connOpen();

    QString bookid=ui->lineEdit_book_id_rem->text();
    QString quantity=ui->lineEdit_quantity->text();
    int count=0;
    int quant=0;
    int tbremoved=0;
    int quantity_int=quantity.toInt();

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
        if(count>2)
            qDebug()<<"Something went wrong...";
        if(count<1)
            qDebug()<<"Incorrect BookID";
    }
    conn.connClose();

    if(count==1)
    {
           conn.connOpen();
           QSqlQuery qry2;

           qry2.prepare("SELECT Quantity FROM books WHERE BookID=:bookid");
           qry2.bindValue(":bookid",bookid);
           qry2.exec();
           while (qry2.next())
           {
               quant = qry2.value(0).toInt();
               qDebug()<<"Quantity of books in db: "<<quant;
           }
           conn.connClose();

           tbremoved=quant-quantity_int;

        if (tbremoved<0)
           {
               qDebug()<<"There are not enough books in the storage";
           }
           else count=2;
        conn.connClose();
    }
    conn.connClose();

    if(count==2)
    {
        if(tbremoved==0)
        {
        conn.connOpen();
        QSqlQuery qry3;

        qry3.prepare("DELETE FROM books WHERE BookID=:bookid");
        qry3.bindValue(":quant",quant);
        qry3.bindValue(":bookid",bookid);

        if(!qry3.exec()){
        qDebug()<<"Query error: "<<qry3.lastError();
        }
        else qDebug()<<"Book/s removed";

        conn.connClose();
        }
        else if (tbremoved>0)
        {
            conn.connClose();
            conn.connOpen();
            QSqlQuery qry3;

            qry3.prepare("UPDATE books SET Quantity=:tbremoved WHERE BookID=:bookid");
            qry3.bindValue(":tbremoved",tbremoved);
            qry3.bindValue(":bookid",bookid);

            qry3.exec();
            while (qry3.next())
            {
            qDebug()<<qry3.value(0).toInt();
            }
            conn.connClose();
        }
    }
}

//dont mind me that's a happy little accident
//void manageBooksView::on_pushButton_remove_book_2_clicked(){}

void manageBooksView::on_pushButton_add_book_clicked()
{
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
   qDebug()<<"query 1";
   qry1.prepare("SELECT COUNT(*) FROM books WHERE Title=:title and auFName=:author_f_name and auLName=:author_l_name");
   qry1.bindValue(":title",title);
   qry1.bindValue(":author_f_name",author_f_name);
   qry1.bindValue(":author_l_name",author_l_name);
   qry1.exec();
   while (qry1.next())
   {
       ifExists = qry1.value(0).toInt();
       qDebug()<<"ifExist value= "<<ifExists;
       if (ifExists==0){
           count=1;
       }
       else qDebug()<<"This book already exists in the database!";

   }
   conn.connClose();
}
   if(count==1){

       conn.connOpen();

       QSqlQuery qry2;
       qDebug()<<"query 2";

   qry2.prepare("INSERT INTO books(title, auFName, auLName, Quantity) "
                "values(:title,:author_f_name,:author_l_name,:quantity)");
   qry2.bindValue(":title",title);
   qry2.bindValue(":author_f_name",author_f_name);
   qry2.bindValue(":author_l_name",author_l_name);
   qry2.bindValue(":quantity",quantity);

   if(!qry2.exec()){
   qDebug()<<"Query error: "<<qry2.lastError();
   }
   else qDebug()<<"Book added to the database";

   }

   conn.connClose();
}
