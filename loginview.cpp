#include "loginview.h"
#include "ui_loginview.h"
#include "librarypro.h"
#include "dbconnection.h"
#include "adminhomepage.h"
#include "managebooksview.h"
#include <QtDebug>

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

//method to take us to registration page
void LoginView::on_pushButton_register_clicked()
{
    qDebug() << "register clicked";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showRegisterView();
}

//method to login user to the system
//it is recongizing if user is admin and if password is correct it is taking admin to admin page
//there is different UI that normal user is taken to - normal user is just person who is using library
void LoginView::on_pushButton_login_clicked()
{
    //variables declaration
        QString pesel = ui->lineEdit_pesel->text();
        QString password = ui->lineEdit_password->text();

    //opening up connection with DB
        DBConnection conn;
        conn.connOpen();
        QSqlQuery query;

        //SQL Query to check if given pesel and password are matching the ones in DB
        query.prepare("select * from users where pesel='"+pesel+"' and password='"+password+"'");

        //Query execution
        if(query.exec())
        {
            //count declaration
            int count=0;
            while(query.next())
            {
                count++;
            }
            if(count==1)
            {
                //if person is admin its taken to admin UI
                if(pesel=="admin"){
                ui->label_login->setText("Logged in as admin.");
                hide();
                qDebug() << "Logged in as admin user";
                QObject *p = this;
                p = p->parent();

                LibraryPro *lp = (LibraryPro*) p;
                lp->showAdminHomePage();

                }
                else{
                    //if person is normal user its taken to normal user UI
                ui->label_login->setText("Logged in.");
                hide();
                //home = new Home(this);
                //home->show();
                qDebug() << "Logged in.";
                QObject *p = this;
                p = p->parent();

                LibraryPro *lp = (LibraryPro*) p;
                lp->showHomeView();
                }
            }
            if(count==1)
                ui->label_login->setText("Logged in correctly.");
            if(count>1)
                ui->label_login->setText("Something went wrong...");
            if(count<1)
                ui->label_login->setText("Incorrect PESEL or password.");
        }
        conn.connClose();

}

