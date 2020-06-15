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

void LoginView::on_pushButton_register_clicked()
{
    qDebug() << "register clicked";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showRegisterView();
}

void LoginView::on_pushButton_login_clicked()
{
        QString pesel = ui->lineEdit_pesel->text();
        QString password = ui->lineEdit_password->text();

        DBConnection conn;


        qDebug()<<"I am before query";


        conn.connOpen();
        qDebug()<<"I should already open the database";
        QSqlQuery query;
        query.prepare("select * from users where pesel='"+pesel+"' and password='"+password+"'");
        if(query.exec())
        {
            qDebug()<<"I should already definitely open the database";

            int count=0;
            while(query.next())
            {
                count++;
            }
            if(count==1)
            {
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

