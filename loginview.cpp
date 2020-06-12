#include "loginview.h"
#include "ui_loginview.h"
#include "librarypro.h"
#include "dbconnection.h"
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


        if(!conn.connOpen())
        {
            qDebug()<<"Failed to open database!";
            //return;
        }

        QSqlQuery query;

        query.prepare("select * from users where pesel='"+pesel+"' and password='"+password+"'");
        if(query.exec())
        {
            int count=0;
            while(query.next())
            {
                count++;
            }
            if(count==1)
            {
                ui->label_login->setText("Logged in correctly.");
                hide();
                //home = new Home(this);
                //home->show();
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

void LoginView::on_pushButton_homeTemp_clicked() {
    qDebug() << "homeTemp clicked";

    QObject *p = this;
    p = p->parent();

    LibraryPro *lp = (LibraryPro*) p;
    lp->showHomeView();
}

