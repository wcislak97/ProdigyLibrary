#include "librarypro.h"
#include "ui_librarypro.h"
#include <fstream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

LibraryPro::LibraryPro(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LibraryPro)
{
    ui->setupUi(this);

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/wcisl/Documents/Qt_Projects/LibraryPro/LibraryPro/prodigy.db");

    if (!mydb.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

LibraryPro::~LibraryPro()
{
    delete ui;
}

std::vector<std::string> readRecordFromFile(std::string file_name, std::string search_term)
{
    std::vector<std::string> record;
    std::ifstream file;
    file.open(file_name);

    bool found_record = false;

    std::string field_one;

    while(getline(file, field_one, ',') && !found_record)
    {
        if(field_one == search_term)
        {
            found_record = true;
            record.push_back(field_one);
        }
    }
    return record;
}

void LibraryPro::on_pushButton_login_clicked()
{
    QString pesel = ui->lineEdit_pesel->text();
    QString password = ui->lineEdit_password->text();

    if(!mydb.isOpen())
    {
        qDebug()<<"Failed to open database!";
        //return;
    }

    QSqlQuery query;
    if(query.exec("select * from users where pesel='"+pesel+"' and password='"+password+"'"))
    {
        int count=0;
        while(query.next())
        {
            count++;
        }
        if(count==1)
            ui->label_login->setText("Logged in correctly.");
        if(count>1)
            ui->label_login->setText("Something went wrong...");
        if(count<1)
            ui->label_login->setText("Incorrect PESEL or password.");
    }

}

void LibraryPro::on_pushButton_register_clicked()
{
    hide();
    registration = new Registration(this);
    registration->show();
}
